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

#include "Core/GameMaster.h"
#include <qtextcodec.h>

GameMaster::GameMaster(GameCycle *gameCycle)
	: gameCycle_(gameCycle)
{
	itemModel_ = new ItemModel(nullptr);
	itemModel_->insertRows(0, 2);
}

/**
 * @brief GameMaster::rozpocznij		ZbiÃ³r operacji wykonywanych na poczÄtku rozgrywki
 */
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

/**
 * @brief GameMaster::ruszGracza Wykonuje wymagane Operations dla momentu, gdy rozpoczyna siÄ tura kolejnego gracza
 * @param gracz aktualny gracz
 */
void GameMaster::movePlayer(int index)
{
	currentPlayer_ = players_->at(index);
	currentQuest_ = nullptr;

	qDebug() << "Mistrz gry obsluguje gracza: " << currentPlayer_->name();

	//regeneracja
	int healthAfterRegen = currentPlayer_->healthCurrent() + currentPlayer_->regeneration();
	currentPlayer_->setHealthCurrent(qMin(currentPlayer_->healthMax(), healthAfterRegen));

	playerWindow_->displayPlayer(currentPlayer_);
	determinePossibleActions();
	actionPanel_->displayActions(possibleActions_);
}

/**
 * @brief GameMaster::ustalMozliweDzialania	Ustala moÅ¼liwe do wykonania zadania przez aktualnego gracza w danym momencie
 */
void GameMaster::determinePossibleActions()
{
	possibleActions_.clear();
	FieldId playerPosition = currentPlayer_->position();
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

/**
 * @brief GameMaster::wybranoAkcje	JeÅ¼eli ta metoda zostaÅa wywoÅana,
 *					to grafika zgÅasza klikniÄcie na przycisk
 * @param name		opcja, ktÃ³ra zostaÅa wybrana
 */
void GameMaster::doAction(int action)
{
	int fieldIndex = board_->fieldIdToIndex(currentPlayer_->position());

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

/**
 * @brief GameMaster::wykonajQuest	Wykonuje zadanie o podanym id.
 *					DziaÅanie jest uzaleÅ¼nione od stopnia wykonania zadania.
 *					Metoda zakÅada, Å¼e zadanie o podany
 * @param gracz		dane gracza, wykonujÄcego zadanie
 * @param id		id zadania
 */
void GameMaster::doQuest(int questId)
{
	currentPlayer_->setHasFoughtRecently(false);
	int questIndex = 0;
	while (currentPlayer_->quest(questIndex)->id() != questId)
		++questIndex;

	Quest *quest = currentPlayer_->quest(questIndex);
	switch (quest->type()) {
	case przynies:
		if (quest->isPartiallyCompleted()) {
			grantPrize(currentPlayer_, quest->prize(), false);
			currentPlayer_->removeQuest(questId);
			determinePossibleActions();
			actionPanel_->displayActions(possibleActions_);
		} else {
			quest->setIsPartiallyCompleted(true);
			quest->setTargetField(quest->employerField());
			gameCycle_->endTurn();
		}
		break;
	case odnajdz: {
		if (quest->isPartiallyCompleted()) {
			grantPrize(currentPlayer_, quest->prize(), false);
			currentPlayer_->removeQuest(questId);
			determinePossibleActions();
			actionPanel_->displayActions(possibleActions_);
			break;
		}
		int chance = BAZOWA_SZANSA_NA_ODNALEZIENIE + currentPlayer_->perception() * BONUS_Z_PERCEPCJI;
		bool success = qrand() % 100 < chance;
		QMessageBox::information(
			gameCycle_->mainWindow(),
			quest->title(),
			success ?
			QString::fromUtf8("UdaÅo Ci siÄ wykonaÄ zadanie.") :
			QString::fromUtf8("Niestety, nie udaÅo Ci siÄ wykonaÄ zadania.")
		);

		if (success)  {
			if (quest->isReturnRequired()) {
				quest->setIsPartiallyCompleted(true);
				quest->setTargetField(quest->employerField());
			} else {
				grantPrize(currentPlayer_, quest->prize(), true);
				currentPlayer_->removeQuest(questId);
			}
		}
		gameCycle_->endTurn();
		break;
	}
	case pokonaj:
		if (quest->isPartiallyCompleted()) {
			grantPrize(currentPlayer_, quest->prize(), false);
			currentPlayer_->removeQuest(questId);
			determinePossibleActions();
			actionPanel_->displayActions(possibleActions_);
		} else {
			currentQuest_ = quest;
			startFight(QuestEnemy);
		}
		break;
	}
}

void GameMaster::newWeek()
{
	qDebug() << "New week has begun.";
	for (QList <const Item *> &i : waresInCities_)
		generateWaresForMarket(i);

	for (int city : questsInCities_.keys()) {
		Field *field = board_->showField(board_->indexToFieldId(city));
		generateQuestsForTavern(questsInCities_[city], field->fraction(), true);
	}
	qDebug() << "Wylosowano zadania";
}

/**
 * @brief GameMaster::wybranoDzialanie		Metoda wywoÅywana z zewnÄtrz.
 *						Sprawdza i obsÅuguje dziaÅanie gracza.
 *						Quest: opcja < 0; Akcja: opcja >= 0
 * @param opcja
 */
void GameMaster::selectedAction(int action)
{
	if (board_->isMoveInProgress())
		return;

	if (action >= 0)
		doAction(action);
	else
		doQuest(action * -1);
}

/**
 * @brief GameMaster::wykonanoRuch	Metoda wywoÅywana z zewnÄtrz.
 *					Informuje, Å¼e gracz jest teraz w innym miejscu.
 */
void GameMaster::moveExecuted()
{
	currentPlayer_->setHasFoughtRecently(false);
	determinePossibleActions();
	actionPanel_->displayActions(possibleActions_);
}

/**
 * @brief GameMaster::poinformujPlansze	Informuje planszÄ o zmianie statystyk (przerysowanie osiÄgalnych pÃ³l)
 */
void GameMaster::updateBoard()
{
	//TODO: use signals
	board_->updateReachableFields();
}

void GameMaster::generateQuests()
{
	FieldId fieldId = currentPlayer_->position();
	int fieldIndex = board_->fieldIdToIndex(fieldId);
	Field *field = board_->showField(fieldId);
	generateQuestsForTavern(questsInCities_[fieldIndex], field->fraction(), false);
}

/**
 * @brief GameMaster::walka	Funkcja losujÄca odpowiedniego przeciwnika i rozpoczynajÄca walkÄ
 * @param opcja		informacja jaka opcja walki (jaki przeciwnik) zostaÅa wybrana
 */
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

/**
 * @brief GameMaster::koniecWalki	Metoda wywoÅywana z zewnÄtrz. Informuje o wyniku walki.
 * @param przeciwnik	przeciwnik, ktÃ³ry braÅ udziaÅ w walce (Å¼eby moÅ¼na byÅo np. przydzieliÄ nagrodÄ)
 * @param rezultat	enumerator opisany w gra.h reprezentujacy wynik walki
 */
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

/**
 * @brief GameMaster::przydzielNagrode	Zmienia dane gracze stosownie do podanej nagrody.
 *					Zmiana poziomu jest wykonywana w Oknie Nagrody.
 * @param gracz		Gracz, ktÃ³remu ma zostaÄ przydzielona prize.
 * @param prize	Nagroda, ktÃ³ra ma zostaÄ przydzielona.
 */
void GameMaster::grantPrize(Player *player, Prize *prize, bool isEndOfTurn)
{
	QList <const Item *> grantedItems;

	//Gold
	player->setGold(qMax(0, player->gold() + prize->gold()));

	//Experience
	player->setExperience(player->experience() + prize->experience());

	//Random item
	QList <int> items;
	for (int i = 0; i < prize->groupNames().size(); ++i)
		items.append(*itemGroups_[prize->groupNames()[i]]);

	if (items.size() > 0) {
		int randItem = qrand() % items.size();
		grantedItems.push_back(items_[items[randItem]]);
	}

	//Reputation
	for (int i = 0; i < KingdomCount; ++i) {
		int sum = prize->reputation()[i] + player->reputation()[i];
		int newValue = qMin((int)MaximumReputation, sum);
		newValue = qMax(0, (int)newValue);
		player->setReputation(newValue, i);
	}

	//Specific items
	for (int i : *prize->items())
		grantedItems.append(items_[i]);

	//Grant item
	for (const Item *item : grantedItems)
		//TODO: to change with introducing one-time use equipement (different dealing with potions)
		if (item->type() == Item::Type::Potion) {
			if (item->name() == "MNIEJSZA MIKSTURA ZDROWIA") //WARNING CFiend magic string
				player->equipment()->setSmallPotions(player->equipment()->smallPotions() + 1); //TODO CFiend brzydkie, moze rozszerzyc API
			else
				player->equipment()->setLargePotions(player->equipment()->largePotions() + 1); //TODO CFiend brzydkie, moze rozszerzyc API
		} else {
			player->equipment()->addItem(item);
		}

	playerWindow_->update();

	prizeWindow_ = new PrizeWindow(currentPlayer_, prize, grantedItems, gameCycle_, isEndOfTurn); //NOTE CFiend moze lepiej nie alokowac na stercie
	prizeWindow_->setWindowModality(Qt::ApplicationModal);
	prizeWindow_->setAttribute(Qt::WA_DeleteOnClose);
	prizeWindow_->displayPrizeWindow();
}

/**
 * @brief GameMaster::losujWroga Metoda losujÄca przeciwnika z zadanej grupy.
 * @param grupa		indeks grupy, z ktÃ³rej ma byÄ losowany przeciwnik.
 * @return		WskaÅºnik na wylosowanego przeciwnika.
 */
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

/**
 * @brief GameMaster::polaczNagrody	ÅÄczy 2 nagrody w jednÄ i daje do niej wskaÅºnik, naleÅ¼y zatroszczyÄ siÄ						o jej wÅasnorÄczne usuniÄcie
 * @param pierwsza	dane pierwszej nagrody
 * @param druga		dane drugiej nagrody
 * @return		zwraca wskaÅºnik do nowo utworzonej nagrody
 */
Prize * GameMaster::mergePrizes(Prize *first, Prize *second)
{
	QList <int> *mergedItems = new QList<int>();
	mergedItems->append(*first->items());
	mergedItems->append(*second->items());

	int *mergedReputation = new int[KingdomCount];
	for (int i = 0; i < KingdomCount; ++i)
		mergedReputation[i] = first->reputation()[i] + second->reputation()[i];

	return new Prize(mergedReputation,
		first->gold() + second->gold(),
		first->experience() + second->experience(),
		first->groupNames() + second->groupNames(),
		mergedItems);

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
