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

GameCycleSrv::GameCycleSrv(ConnectionAdapterSrv *connAdapter) : connAdapter_(connAdapter)
{
	connect(connAdapter_, &ConnectionAdapterSrv::newUser, &newGameSrv_, &NewGameSrv::onUserEntered);
	connect(connAdapter_, &ConnectionAdapterSrv::userDisconnected, &newGameSrv_, &NewGameSrv::onUserQuit);

	connect(&newGameSrv_, &NewGameSrv::gameSet, &GameCycleSrv::beginGame);
	switchAuthority(&newGameSrv_);
}

void GameCycleSrv::beginGame(const QHash <UID, PlayerDraft> &playersDrafts)
{
	disconnect(connAdapter_, &ConnectionAdapterSrv::newUser, this, &NewGameSrv::onUserEntered);
	disconnect(connAdapter_, &ConnectionAdapterSrv::userDisconnected, this, &NewGameSrv::onUserQuit);

	for (auto playerId : playersDrafts.keys())
		players_[playerId] = Player(playersDrafts[playerId]);
	currentPlayer_ = players_.begin().key();
}

void GameCycleSrv::onBecameReceiver(Authority *predecessor)
{
	if (predecessor == nullptr)
		return;

	if (predecessor == &newGameSrv_) {
		emit gameSet();
		return;
	}
}

void GameCycleSrv::endTurn()
{
// 	if (hasPlayerWon(players_[currentPlayerIdx_]))
// 		playerHasWon(players_[currentPlayerIdx_]);

// 	nextPlayer();
// 	movePlayer(currentPlayerIdx_);
}
