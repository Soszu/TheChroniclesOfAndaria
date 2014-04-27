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

#ifndef EQUIPMENTWINDOW_H
#define EQUIPMENTWINDOW_H

#include <QtWidgets>

#include "Core/DataManager.h"
#include "Core/Containers/Item.h"
#include "Core/Containers/Player.h"
#include "Core/Operations/EquipmentManagement.h"
#include "Game/PlayerWindow.h"

class PlayerWindow;

class EquipmentWindow : public QDialog {
	Q_OBJECT;
public:
	EquipmentWindow(Player *player, PlayerWindow *playerWindow);

private:
	Player *player_;
	PlayerWindow *playerWindow_;
	QTextBrowser *itemDescription_;
	QListWidget *itemList_;

	QPushButton *buttonEquip_;
	QPushButton *buttonOk_;
	QPushButton *buttonLargePotion_;
	QPushButton *buttonSmallPotion_;;

private slots:
	void equip();
	void showDescription(const QModelIndex &index);
	void useLargePotion();
	void useSmallPotion();
};

#endif
