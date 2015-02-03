/*
Copyright (C) 2014-2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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

#include "GameCycleClt.hpp"

GameCycleClt::GameCycleClt(ConnectionAdapterClt *connAdapter) :
	connAdapter_(connAdapter) //: board_(this), gameMaster_(this)
{}

ConnectionAdapterClt * GameCycleClt::connectionAdapter()
{
	return connAdapter_;
}

void GameCycleClt::beginGame()
{
	qDebug() << "Game started";
	// connect connAdapter_
	emit showGui();
}

//GameMaster * GameCycle::gameMaster()
//{
//	return &gameMaster_;
//}

//Board * GameCycle::board()
//{
//	return &board_;
//}

/*
void GameCycle::showEquipment()
{
//	equipmentWindow_ = new EquipmentWindow(player, this);
//	equipmentWindow_->setWindowModality(Qt::ApplicationModal);
//	equipmentWindow_->setAttribute(Qt::WA_DeleteOnClose);
//	equipmentWindow_->show();
}

void GameCycle::showQuests()
{
//	questWindow_ = new QuestWindow(player, gameMaster_->board());
//	questWindow_->setWindowModality(Qt::ApplicationModal);
//	questWindow_->setAttribute(Qt::WA_DeleteOnClose);
	//	questWindow_->show();
}


Player *GameCycle::currentPlayer()
{
	return players_[currentPlayerIdx_];
}

const QList<Player *> & GameCycle::players()
{
	return players_;
}

int GameCycle::day()
{
	return day_;
}

int GameCycle::week()
{
	return week_;
}

void GameCycle::removeCurrentPlayer()
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

void GameCycle::playerHasWon(Player *player)
{
//	QMessageBox::information(
//		mainWindow_,
//		QString::fromUtf8("Gratulacje!"),
//		player->name() + QString::fromUtf8(" zwyciężył.")
//	);
//	mainWindow_->close();
}

bool GameCycle::hasPlayerWon(Player *player)
{
	int maxReputations = 0;
	for(int i = 0; i < KingdomCount; ++i)
		if(player->reputation()[i] == MaximumReputation)
			++maxReputations;

	return player->level() == MaximumLevel && maxReputations >= MaximumReputationsToWin;
}

void GameCycle::movePlayer(int index)
{
	qDebug() << "Cykl Gry rusza gracza o indeksie: " << currentPlayerIdx_;
//	board_->movePlayer(index);
//	gameMaster_->movePlayer(index);
}

void GameCycle::nextPlayer()
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

void GameCycle::newDay()
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

void GameCycle::endTurn()
{
	if (hasPlayerWon(players_[currentPlayerIdx_]))
		playerHasWon(players_[currentPlayerIdx_]);

	nextPlayer();
	movePlayer(currentPlayerIdx_);
}

void GameCycle::init()
{
	week_ = 1;
	day_ = 1;
	currentPlayerIdx_ = 0;
}
*/
