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

#ifndef EQUIPMENTMANAGEMENT_H
#define EQUIPMENTMANAGEMENT_H

#include <QtWidgets>

#include "Core/Containers/Item.h"
#include "Core/Containers/Player.h"

//TODO CFiend czy to nie powinny byc metody Player albo Equipment?
void activateBonus(const Item *item, Player *player, int multiplier = 1);
void deactivateBonus(const Item *item, Player *player);

bool isPermitted(const Item *item, const Player *player);
bool isAllowedForClass(Item *item, Player::Class index);

QString effectString(int bonus, QString effect);
void generateDescription(const Item *item, const Player *player, QTextBrowser *target);

bool isEquipped(const Item *item, const Player *player);
void equipItem(const Item *item, Player *player);
void unequipItem(const Item *item, Player *player);

#endif
