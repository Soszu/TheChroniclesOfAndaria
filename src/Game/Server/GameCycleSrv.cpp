/*
Copyright (C) 2014 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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

#include "GameCycleSrv.h"

GameCycleSrv::GameCycleSrv(ConnectionAdapterSrv *connAdapter) : connAdapter_(connAdapter) //: board_(this), gameMaster_(this)
{}

//GameMaster * GameCycleSrv::gameMaster()
//{
//	return &gameMaster_;
//}

//Board * GameCycleSrv::board()
//{
//	return &board_;
//}

void GameCycleSrv::beginGame(const QHash <UID, PlayerDraft> &playersDrafts)
{
	//NOTE need refactoring Logic/Graphic controlGameCycle::
// 	playersAlive_ = players.size();
// 	this->players_ = players;
//
// 	init();
// 	qDebug() << "Player count: " << players_.size();
// 	gameMaster_->beginGame();
// 	board_->init();
// 	movePlayer(currentPlayerIdx_);
}

void GameCycleSrv::showEquipment()
{
//	equipmentWindow_ = new EquipmentWindow(player, this);
//	equipmentWindow_->setWindowModality(Qt::ApplicationModal);
//	equipmentWindow_->setAttribute(Qt::WA_DeleteOnClose);
//	equipmentWindow_->show();
}

void GameCycleSrv::showQuests()
{
//	questWindow_ = new QuestWindow(player, gameMaster_->board());
//	questWindow_->setWindowModality(Qt::ApplicationModal);
//	questWindow_->setAttribute(Qt::WA_DeleteOnClose);
	//	questWindow_->show();
}

ConnectionAdapterSrv * GameCycleSrv::connectionAdapter()
{
	return connAdapter_;
}

Player *GameCycleSrv::currentPlayer()
{
	return players_[currentPlayerIdx_];
}

const QList<Player *> & GameCycleSrv::players()
{
	return players_;
}

int GameCycleSrv::day()
{
	return day_;
}

int GameCycleSrv::week()
{
	return week_;
}

void GameCycleSrv::removeCurrentPlayer()
{
////	QMessageBox::information(
////		mainWindow_,
////		QString::fromUtf8("Przykro mi, ale ..."),
////		players_[currentPlayerIdx_]->name() + QString::fromUtf8(" wypadł z gry.")
////	);

//	if (playersAlive_ == 1) {
//		nextPlayer();
////		QMessageBox::information(
////			mainWindow_,
////			QString::fromUtf8("Gratulacje!"),
////			players_[currentPlayer_]->name() + QString::fromUtf8(" jest teraz jedynym żywym graczem i tym samym zwycięża.")
////		);
////		mainWindow_->close();
//	} else {
//		board_->removePlayer(currentPlayerIdx_);
//	}
}

void GameCycleSrv::playerHasWon(Player *player)
{
//	QMessageBox::information(
//		mainWindow_,
//		QString::fromUtf8("Gratulacje!"),
//		player->name() + QString::fromUtf8(" zwyciężył.")
//	);
//	mainWindow_->close();
}

bool GameCycleSrv::hasPlayerWon(Player *player)
{
	int maxReputations = 0;
	for(int i = 0; i < KingdomCount; ++i)
		if(player->reputation()[i] == MaximumReputation)
			++maxReputations;

	return player->level() == MaximumLevel && maxReputations >= MaximumReputationsToWin;
}

void GameCycleSrv::movePlayer(int index)
{
	qDebug() << "Cykl Gry rusza gracza o indeksie: " << currentPlayerIdx_;
//	board_->movePlayer(index);
//	gameMaster_->movePlayer(index);
}

void GameCycleSrv::nextPlayer()
{
	do {
		++currentPlayerIdx_;
		if(currentPlayerIdx_ >= players_.size())
		{
			newDay();
			currentPlayerIdx_ = 0;
		}
	} while (!players_[currentPlayerIdx_]->isActive());
}

void GameCycleSrv::newDay()
{
	if (day_ < DaysPerWeek) {
		++day_;
	} else {
		day_ = 1;
		++week_;
//		gameMaster_->newWeek();
	}
//	mainWindow_->changeDate(day_, week_);
}

void GameCycleSrv::endTurn()
{
	if (hasPlayerWon(players_[currentPlayerIdx_]))
		playerHasWon(players_[currentPlayerIdx_]);

	nextPlayer();
	movePlayer(currentPlayerIdx_);
}

void GameCycleSrv::init()
{
	week_ = 1;
	day_ = 1;
	currentPlayerIdx_ = 0;
}
