/*
Copyright (C) 2013 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
Thanks to 2013 Łukasz Piesiewicz <wookesh [at] gmail [dot] com>

This file is part of The Chronicles Of Andaria Project.

	The Chronicles of Andaria Project is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	The Chronicles of Andaria Project is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with The Chronicles Of Andaria.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "GameMaster.h"

GameMaster::GameMaster(GameCycle *gameCycle)
	: gameCycle_(gameCycle)
{
	itemModel_ = new ItemModel(nullptr);
	itemModel_->insertRows(0, 2);
}

void GameMaster::beginGame()
{
	waresInCities_.clear();
	questsInCities_.clear();

	for (int city : board_->cities()) {
		waresInCities_.insert(city, QList <const Item *>());
		questsInCities_.insert(city, QList <Quest *>());
	}

	newWeek();
}

void GameMaster::movePlayer(int index)
{
	currentPlayer_ = players_->at(index);
	currentQuest_ = nullptr;

	qDebug() << "Mistrz gry obsluguje gracza: " << currentPlayer_->name();

	//regeneracja
	int healthAfterRegen = currentPlayer_->currentHealth() + currentPlayer_->regeneration();
	currentPlayer_->setHealthCurrent(qMin(currentPlayer_->maxHealth(), healthAfterRegen));

	playerWindow_->displayPlayer(currentPlayer_);
	determinePossibleActions();
	actionPanel_->displayActions(possibleActions_);
}

void GameMaster::determinePossibleActions()
{
	possibleActions_.clear();
	Coordinates playerPosition = currentPlayer_->position();
	Field *field = board_->showField(playerPosition);

	//===== QUESTS =====
	for (Quest *q : *currentPlayer_->quests())
		if (playerPosition == q->targetField()) {
			QString description = QString("Wykonaj zadanie:\n") + q->title();
			possibleActions_.push_back(qMakePair(q->id() * (-1), description));
		}

	//===== ACTIONS IN CITY =====
	if (field->hasCity()) {
		possibleActions_.push_back(qMakePair((int)Market, ActionString[Market]));
		possibleActions_.push_back(qMakePair((int)Tavern, ActionString[Tavern]));
		possibleActions_.push_back(qMakePair((int)Healer, ActionString[Healer]));
	}

	//===== ACTIONS ON FIELDS WITH ENEMIES =====
	if (field->hasEnemy() && !currentPlayer_->hasFoughtRecently()) {
		possibleActions_.push_back(qMakePair((int)EnemyEasy, ActionString[EnemyEasy]));
		//grupy przeciwnikow sÄ numerowane od 1.
		int enemyGroup = (currentPlayer_->level() + 1) / 2;
		if (enemyGroup + 1 <= EnemyGroupCount)
			possibleActions_.push_back(qMakePair((int)EnemyHard, ActionString[EnemyHard]));
	}

	//===== PVP ACTIONS =====
	QList <int> otherPlayersInThisField;
	for(int i = 0; i < players_->size(); ++i) {
		Player *g = players_->at(i);
		if (g->isActive() && g->color() != currentPlayer_->color() && g->position() == playerPosition && !field->hasCity())
			otherPlayersInThisField.push_back(i);
	}

	for (int i : otherPlayersInThisField) {
		QString description = QString::fromUtf8("Walcz z graczem ") + players_->at(i)->name();
		possibleActions_.push_back(qMakePair(PVPActions + i, description));
	}

	possibleActions_.push_back(qMakePair((int)EndTurn, ActionString[EndTurn]));
}

void GameMaster::doAction(int action)
{
	int fieldIndex = board_->coordinatesToIndex(currentPlayer_->position());

	if (action >= PVPActions) {
		startFight(action);
		return;
	}

	switch ((Action)action) {
	case EndTurn:
		currentPlayer_->setHasFoughtRecently(false);
		gameCycle_->endTurn();
		break;
	case EnemyEasy:
	case EnemyHard:
		startFight(action);
		break;
	case Market:
		board_->disablePlayerMove();
// 		marketWindow_ = new MarketWindow(currentPlayer_, playerWindow_, waresInCities_[fieldIndex]); //NOTE CFiend moze lepiej nie alokowac na stercie
// 		marketWindow_->setWindowModality(Qt::ApplicationModal);
// 		marketWindow_->setAttribute(Qt::WA_DeleteOnClose);
// 		marketWindow_->show();
		marketViewWindow_ = new MarketViewWindow(itemModel_);
		marketViewWindow_->setWindowModality(Qt::ApplicationModal);
		marketViewWindow_->setAttribute(Qt::WA_DeleteOnClose);
		marketViewWindow_->show();
		break;
	case Tavern:
		board_->disablePlayerMove();
		tavernWindow_ = new TavernWindow(currentPlayer_, board_, this, playerWindow_, &questsInCities_[fieldIndex]); //NOTE CFiend moze lepiej nie alokowac na stercie
		tavernWindow_->setWindowModality(Qt::ApplicationModal);
		tavernWindow_->setAttribute(Qt::WA_DeleteOnClose);
		tavernWindow_->show();
		break;
	case Healer:
		board_->disablePlayerMove();
		healerWindow_ = new HealerWindow(currentPlayer_, playerWindow_); //NOTE CFiend moze lepiej nie alokowac na stercie
		healerWindow_->setWindowModality(Qt::ApplicationModal);
		healerWindow_->setAttribute(Qt::WA_DeleteOnClose);
		healerWindow_->show();
		break;
	default:
		qDebug() << QString::fromUtf8("BÅÄdna opcja");
	}
}

void GameMaster::newWeek()
{
	qDebug() << "New week has begun.";
	for (QList <const Item *> &i : waresInCities_)
		generateWaresForMarket(i);

	for (int city : questsInCities_.keys()) {
		Field *field = board_->showField(board_->indexToCoordinates(city));
		generateQuestsForTavern(questsInCities_[city], field->fraction(), true);
	}
	qDebug() << "Wylosowano zadania";
}

void GameMaster::selectedAction(int action)
{
	if (board_->isMoveInProgress())
		return;

	if (action >= 0)
		doAction(action);
	else
		doQuest(action * -1);
}

void GameMaster::moveExecuted()
{
	currentPlayer_->setHasFoughtRecently(false);
	determinePossibleActions();
	actionPanel_->displayActions(possibleActions_);
}

void GameMaster::updateBoard()
{
	//TODO: use signals
	board_->updateReachableFields();
}

void GameMaster::generateQuests()
{
	Coordinates coordinates = currentPlayer_->position();
	int fieldIndex = board_->coordinatesToIndex(coordinates);
	Field *field = board_->showField(coordinates);
	generateQuestsForTavern(questsInCities_[fieldIndex], field->fraction(), false);
}

void GameMaster::startFight(int enemyType)
{
	int enemyLvlEasy = (currentPlayer_->level() + 1 ) / 2;
	Enemy* enemy = nullptr;


	if (enemyType >= PVPActions)
	{
		//TODO wyznaczenie przeciwnika do pvp
	} else {
		switch((Action)enemyType) {
		case EnemyEasy:
			enemy = generateEnemy(enemyLvlEasy);
			currentPlayer_->setHasFoughtRecently(true);
			break;
		case EnemyHard:
			enemy = generateEnemy(enemyLvlEasy + 1);
			currentPlayer_->setHasFoughtRecently(true);
			break;
		case QuestEnemy:
			enemy = currentQuest_->enemies()->front();
		default:
			qDebug() << QString::fromUtf8("BÅÄdna opcja");
		}
	}

	if (enemy == nullptr)
		return;

	fightWindow_ = new FightWindow(currentPlayer_, enemy, this); //NOTE CFiend moze lepiej nie alokowac na stercie
	fightWindow_->setWindowModality(Qt::ApplicationModal);
	fightWindow_->setAttribute(Qt::WA_DeleteOnClose);
	fightWindow_->beginFight();
}

void GameMaster::endFight(Enemy *enemy, FightResult result)
{
	switch (result) {
	case FightResult::Lose:
		gameCycle_->removeCurrentPlayer();
		gameCycle_->endTurn();
		break;
	case FightResult::Win:
		if (currentQuest_ != nullptr) {
			currentQuest_->enemies()->removeFirst();
			if (currentQuest_->enemies()->isEmpty()) {
				if(currentQuest_->isReturnRequired()) {
					currentQuest_->setIsPartiallyCompleted(true);
					currentQuest_->setTargetField(currentQuest_->employerField());
				} else {
					Prize *prize = mergePrizes(enemy->prize(), currentQuest_->prize());
					grantPrize(currentPlayer_, prize, true);
					delete prize;
					currentPlayer_->removeQuest(currentQuest_->id());
					currentQuest_ = nullptr;
					break;
				}
			}
		}
		grantPrize(currentPlayer_, enemy->prize(), true);
		break;
	case FightResult::Retreat:
		gameCycle_->endTurn();
		break;
	}
}

Enemy * GameMaster::generateEnemy(int enemyGroup)
{
	int idx = qrand() % enemyGroups_[enemyGroup]->size();
	return enemies_[enemyGroups_[enemyGroup]->at(idx)];
}

void GameMaster::generateQuestsForTavern(QList <Quest *> &dest, int fraction, bool overwritePrevious)
{
	if (overwritePrevious)
		dest.clear();

	while (dest.size() < QuestsInTavernCount) {
		//WARNING inappropriate way of drawing quests
		int idx = qrand() % quests_.size() + 1;
		bool fractionOk = quests_[idx]->fraction() == fraction || quests_[idx]->fraction() == -1;
		if (!dest.contains(quests_[idx]) && fractionOk)
			dest.push_back(quests_[idx]);
	}
}

void GameMaster::generateWaresForMarket(QList <const Item *> &dest)
{
	dest.clear();
	for (int i = 0; i < ItemCountInMarket; ++i) {
		//WARNING inappropriate way of drawing items
		int idx = qrand() % items_.size() + 1;
		//TODO: zmiana sposobu zarzÄdzania miksturami
		if (items_[idx]->type() == Item::Type::Potion || dest.contains(items_[idx]))
			--i;
		else
			dest.append(items_[idx]);
	}
}

void GameMaster::setBoard(Board *board)
{
	this->board_ = board;
}

Board * GameMaster::board()
{
	return board_;
}

void GameMaster::setActionPanel(ActionPanel *actionPanel)
{
	this->actionPanel_ = actionPanel;
}

void GameMaster::setPlayerWindow(PlayerWindow *playerWindow)
{
	this->playerWindow_ = playerWindow;
}

void GameMaster::setPlayers(QList <Player *> *players)
{
	this->players_ = players;
}
