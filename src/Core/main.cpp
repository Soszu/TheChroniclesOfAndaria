/*
Copyright (C) 2013 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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
#include "Core/Board.h"
#include "Core/GameCycle.h"
#include "Core/GameMaster.h"
#include "Gui/Windows/NewGameWindow.h"
#include "Gui/MainWindow.h"

//TODO CFiend ten plik raczej powinien wyladowac w src/Gui/
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	qsrand(QDateTime::currentDateTime().toTime_t());

	NewGameWindow newGameWindow;
	int parseResult = 0;
	GameCycle gameCycle(&parseResult);

	Board board(&gameCycle);
	if (parseResult != 0)
		return parseResult;

	GameMaster gameMaster(&gameCycle);
	if (parseResult != 0)
		return parseResult;

	MainWindow mainWindow(&gameMaster, &board);

	gameMaster.setActionPanel(mainWindow.actionPanel());
	gameMaster.setPlayerWindow(mainWindow.playerWindow());
	board.setBoardArea(mainWindow.boardArea());

	gameCycle.setGameMaster(&gameMaster);
	gameCycle.setBoard(&board);
	gameCycle.setMainWindow(&mainWindow);
	gameMaster.setBoard(&board);
	board.setGameMaster(&gameMaster);

	newGameWindow.setGameCycle(&gameCycle);
	newGameWindow.setMainWindow(&mainWindow);
	newGameWindow.show();

	return app.exec();
}

