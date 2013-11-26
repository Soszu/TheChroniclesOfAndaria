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

	MainWindow mainWindow;
	NewGameWindow newGameWindow;
	int parseResult = 0;
	GameCycle gameCycle(&parseResult);

	Board board(&gameCycle);
	if (parseResult != 0)
		return parseResult;

	GameMaster gameMaster(&gameCycle);
	if (parseResult != 0)
		return parseResult;

	mainWindow.setGameMaster(&gameMaster);
	mainWindow.setBoard(&board);

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

