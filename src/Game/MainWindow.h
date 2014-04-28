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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>

#include "Core/Board.h"
#include "Core/GameMaster.h"
#include "Game/Windows/RulesWindow.h"
#include "Game/ActionPanel.h"
#include "Game/BoardArea.h"
#include "Game/PlayerWindow.h"

class GameMaster;
class BoardArea;
class PlayerWindow;
class ActionPanel;

class MainWindow : public QMainWindow {
	Q_OBJECT;
public:
	explicit MainWindow(GameMaster *gameMaster, Board *board, QWidget *parent = nullptr);
	~MainWindow();

	ActionPanel * actionPanel();
	BoardArea * boardArea();
	PlayerWindow * playerWindow();

	void changeDate(int day, int week);

private slots:
	void displayRules();

private:
	QGraphicsView *graphicsView;

	QMenu *menuGame;
	QMenu *menuView;
	QMenu *menuHelp;
	QLabel *dateDisplay;

	ActionPanel *actionPanel_;
	BoardArea *boardArea_;
	PlayerWindow *playerWindow_;
	RulesWindow *rulesWindow_;
};

#endif
