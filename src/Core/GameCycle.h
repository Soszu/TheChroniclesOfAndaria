#ifndef GAMECYCLE_H
#define GAMECYCLE_H

#include <QtWidgets>

#include "Core/AI/AI.h"
#include "Core/Containers/Player.h"
#include "Core/Board.h"
#include "Core/GameMaster.h"
#include "Gui/MainWindow.h" //TODO CFiend dlaczego logika wciaga grafike?

class AI;
class MainWindow;

class GameCycle {

public:
	GameCycle(int *parseResult);
	~GameCycle();

	void setGameMaster(GameMaster *gameMaster);
	void setBoard(Board *board);
	void setPlayers(QList <Player *> players);
	void setMainWindow(MainWindow *okno); //TODO CFiend chcemy wywalic grafike z logiki
	MainWindow * mainWindow() const;
	void displayErrorMessage(const QString &message, int error) const;

	const QList <Player *> & players();

	void removeCurrentPlayer();
	void beginGame();
	void endTurn();

private:
	void initGameCycle();
	void playerHasWon(Player *player);
	bool hasPlayerWon(Player *player);
	void movePlayer(int index);
	void nextPlayer();
	void newDay();

	int playersAlive_;
	int currentPlayer_;
	int week_;
	int day_;

	QList <Player *> players_;
	QMap <int, AI *> computerPlayers_;

	int *parseResult_; //TODO CFiend kill it with fire
	QDialog *errorMessageBox_;
	MainWindow *mainWindow_;
	Board *board_;
	GameMaster *gameMaster_;
};
#endif
