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

#ifndef QUESTWINDOW_H
#define QUESTWINDOW_H

#include <QtWidgets>

#include "Core/Containers/Player.h"
#include "Core/Containers/Quest.h"
#include "Core/Board.h"

class Board;

class QuestWindow : public QDialog {
	Q_OBJECT;
public:
	QuestWindow(Player *player, Board *board);

private:
	Player *player_;
	Board *board_;

	QTextBrowser *questDescriptionWidget;
	QListWidget *questListWidget;
	QPushButton *showDestinationButton;

private slots:
	void displayQuestDescription(const QModelIndex &index);
	void showDestination();
};

#endif
