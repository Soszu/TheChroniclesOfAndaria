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

#ifndef MARKETWINDOW_H
#define MARKETWINDOW_H

#include <QtWidgets>

#include "Core/DataManager.h"
#include "Core/GameMaster.h"
#include "Core/Game.h"
#include "Core/Operations/EquipmentManagement.h"
#include "Core/Containers/Item.h"

class GameMaster;
class PlayerWindow;

static const QString sellText("Sprzedaj");
static const QString buyText("Kup");
static const QString equipText(QString::fromUtf8("Załóż"));
static const QString unequipText("Zdejmij");

class MarketWindow : public QDialog {
	Q_OBJECT
public:
	MarketWindow(Player *player, PlayerWindow *playerWindow, const QList <const Item *> &wares);

private:
	void populateListWidgets();

	Player *player_;
	PlayerWindow *playerWindow_;
	QList <const Item *> wares_;

	QListWidget *playerItemList;
	QListWidget *wareList;
	QTextBrowser *itemDescriptionWidget;
	QLabel *largePotionCountLabel;
	QLabel *smallPotionCountLabel;

	QPushButton* buyButton;
	QPushButton* confirmButton;
	QPushButton* equipButton;
	QPushButton* largePotionButton;
	QPushButton* smallPotionButton;

private slots:
	void buy();
	void buyLargePotion();
	void buySmallPotion();
	void displayMarketItem(const QModelIndex &index);
	void displayPlayerItem(const QModelIndex &index);
	void equip();
};

#endif
