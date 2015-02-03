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
#pragma once

#include <QtWidgets>
#include "Game/Client/NewGameClt.hpp"
#include "Game/Client/Strings.hpp"
#include "Core/DataManager.hpp"

#include "Core/Containers/Player.hpp"

class NewGameGui : public QDialog {
	Q_OBJECT
public:
	NewGameGui(NewGameClt *newGameClt);

private:
	void initWindow();
	void initStripes();
	void initButtons();
	void fillOthersStripes();
	void clearOthersStripes();
	QHBoxLayout * draftToStripe(const PlayerDraft &draft);

	NewGameClt  *newGameClt_;
	QVBoxLayout *mainLayout_;
	QVBoxLayout *othersStripes_;
	QPushButton *readyButton_;

	QLineEdit *nameEdit_;
	QComboBox *playerRaceCombo_;
	QComboBox *playerClassCombo_;
	QPushButton *colorButton_;
	QColorDialog *colorDialog_;

private slots:
	void showColorDialog();
	void refreshOthersDrafts();
	void playerRaceChanged(const QString &playerRace);
	void playerClassChanged(const QString &playerClass);
	void playerReady();
};
