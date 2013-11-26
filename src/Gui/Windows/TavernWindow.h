#ifndef TAVERNWINDOW_H
#define TAVERNWINDOW_H

#include <QtWidgets>

#include "Core/Containers/Player.h"
#include "Core/Containers/Quest.h"
#include "Core/Board.h"
#include "Core/Game.h"
#include "Gui/PlayerWindow.h"

class Board;

class TavernWindow : public QDialog {
	Q_OBJECT;
public:
	TavernWindow(Player *player, Board *board, GameMaster *gameMaster, PlayerWindow *playerWindow, QList <Quest *> *availableQuests);

private:
	void fillQuestListWidgets();

	Player* player_;
	Board* board_;
	GameMaster* gameMaster_;
	PlayerWindow* playerWindow_;
	QList <Quest *> *availableQuests_; //TODO CFiend zamiast grzebac w czyjejs liscie lepiej rozszerzyc odpowiednie API
	bool questRejected;

	QListWidget *availableQuestsWidget;
	QListWidget *currentQuestsWidget;
	QTextBrowser *questDescriptionWidget;

	QPushButton *acceptQuestButton;
	QPushButton *showDestinationButton;

	Quest *lastDisplayedQuest;

private slots:
	void acceptQuest(); //TODO CFiend ta metoda zarowno przyjmuje jak i odrzuca; madness nazewniczy
	void displayAvailableQuest(const QModelIndex &index);
	void displayPlayerQuest(const QModelIndex &index);
	void generateQuests();
	void showDestination();
};

#endif
