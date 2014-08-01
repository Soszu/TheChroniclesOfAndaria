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

#ifndef PRIZEWINDOW_H
#define PRIZEWINDOW_H

#include <QtWidgets>

#include "Core/Containers/Item.h"
#include "Core/Containers/Prize.h"
#include "Core/Containers/Player.h"
#include "Core/Game.h"
#include "Core/GameCycle.h"

class GameCycle;

class PrizeWindow : public QDialog {
	Q_OBJECT
public:
	PrizeWindow(Player *player, Prize *prize, const QList <const Item *> &prizeItems, GameCycle *gameCycle, bool isEndOfTurn); //TODO CFiend bool w API jest podejrzany

public slots:
	void displayPrizeWindow();

private:
	void increaseAttribute(atrybut index);
	QString prizeDescription() const;

	Player *player_;
	Prize *prize_;
	QList <const Item *> prizeItems_;
	GameCycle *gameCycle_;
	bool isEndOfTurn_;

	QListWidget *itemListWidget;
	QTextBrowser *itemDescriptionWidget;
	QTextBrowser *prizeDescriptionWidget;

	bool isLevelUp;
	QList <QComboBox *> attributePointChoice;

private slots:
	void displayItemDescription(const QModelIndex &index);
	void confirm();
};

#endif
