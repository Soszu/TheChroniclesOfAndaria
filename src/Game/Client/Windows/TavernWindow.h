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

#ifndef TAVERNWINDOW_H
#define TAVERNWINDOW_H

#include <QtWidgets>

#include "Core/Containers/Player.h"
#include "Core/Containers/Quest.h"
#include "Core/Board.h"
#include "Game/PlayerWindow.h"

class Board;

static const quint8 QuestsInTavernCount = 3;
static const QString acceptText("Przyjmij");
static const QString abandonText(QString::fromUtf8("Porzuć"));

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
	void processQuest();
	void displayAvailableQuest(const QModelIndex &index);
	void displayPlayerQuest(const QModelIndex &index);
	void generateQuests();
	void showDestination();
};

#endif
