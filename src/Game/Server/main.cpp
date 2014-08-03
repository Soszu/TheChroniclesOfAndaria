/*
Copyright (C) 2013-2014 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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

#include <QApplication>
#include "Game/Common/DataKeeper.h"
#include "Game/Server/ConnectionAdapterSrv.h"
#include "Game/Server/GameCycleSrv.h"
#include "Game/Server/NewGameSrv.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	qsrand(QDateTime::currentDateTime().toTime_t());

	int initError = DataKeeper::instance().initError();
	if (initError)
		return initError;
	
	ConnectionAdapterSrv connAdapter;
	GameCycleSrv gameCycle(&connAdapter);
	NewGameSrv newGameSrv(&connAdapter);

	QObject::connect(&newGameSrv, &NewGameSrv::gameSet, &gameCycle, &GameCycleSrv::beginGame);
	newGameSrv.waitForPlayers();

	return app.exec();
}

