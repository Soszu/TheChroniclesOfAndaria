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

#ifndef NEWGAMEWINDOW_H
#define NEWGAMEWINDOW_H

#include <QtWidgets>

#include "Core/Containers/Player.h"
#include "Core/Game.h"
#include "Core/GameCycle.h"

class NewGameWindow : public QDialog {
	Q_OBJECT;
public:
	explicit NewGameWindow(QWidget *parent = nullptr);
	~NewGameWindow();
	void setGameCycle(GameCycle *gameCycle);
	void setMainWindow(QMainWindow *mainWindow);

private:
	GameCycle *gameCycle_;
	QMainWindow *mainWindow_;
	quint8 playerCount_;

	//TODO CFiend kill it or enhance it?
	struct PlayerSelectionRow {
		QLineEdit *nameEdit;
		QComboBox *playerRaceCombo;
		QComboBox *playerClassCombo;
		QComboBox *colorCombo;
		QCheckBox *isAiCheckBox;
	};

	QList <PlayerSelectionRow> playerRows;

	QHBoxLayout *playerSelectionRowLayouts[MaxPlayers];

	QMessageBox *messageBox;

	void fillPlayerSelectionRow(PlayerSelectionRow *row, int playerNumber);

private slots:
	void addPlayerSelectionRow();
	void removePlayerSelectionRow();
	void validate();
};

#endif
