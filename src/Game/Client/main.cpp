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
#include <QApplication>

#include "Game/Client/ConnectionAdapterClt.hpp"
#include "Game/Client/MainWindow.hpp"
#include "Game/Client/NewGameGui.hpp"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	qsrand(QDateTime::currentDateTime().toTime_t());

	ConnectionAdapterClt connAdapter;

	GameCycleClt gameCycle(&connAdapter);
	MainWindow mainWindow(&gameCycle);
	QObject::connect(&gameCycle, &GameCycleClt::showGui, &mainWindow, &QMainWindow::show);

	NewGameClt newGameClt(&connAdapter);
	NewGameGui newGameGui(&newGameClt);
	QObject::connect(&newGameClt, &NewGameClt::showGui, &newGameGui, &QDialog::show);
	QObject::connect(&newGameClt, &NewGameClt::gameSet, &newGameGui, &NewGameGui::close);


	QObject::connect(&newGameClt, &NewGameClt::gameSet, &gameCycle, &GameCycleClt::beginGame);
	newGameClt.start();

	return app.exec();
}
