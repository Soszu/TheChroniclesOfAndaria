/*
Copyright (C) 2013 Łukasz Piesiewicz <wookesh [at] gmail [dot] com>
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

#ifndef ITEAM_WEARABLE_H
#define ITEAM_WEARABLE_H

#include <Core/Containers/Item.h>

class ItemWearable : public Item {
public:
	ItemWearable(QString name = QString("Default"),
	     Item::Type type = Type::OneHanded,
	     int bonusMelee = 0,
	     int bonusRanged = 0,
	     int bonusMagical = 0,
	     int bonusDefence =  0,
	     int bonusPerception = 0,
	     int bonusHitPoints  = 0,
	     int bonusRegeneration = 0,
	     int restrictions = 0,
	     int value = 1,
	     bool isStrong = false,
	     Item::Quality quality = Quality::Normal,
	     bool isComplex = false);
	
	ItemWearable(//UID ID,
					 QString name,
					 //CharacterStats statsModifiers,
					 Item::Type type,
					 //QMap <Player::Class, bool> restriction,
					 int value,
					 Item::Quality quality,
					 bool isComplex);
	
	bool isComplex() const;
	
	friend QDataStream & operator<<(QDataStream &out, const ItemWearable &itemWearable);
	friend QDataStream & operator>>(QDataStream &in, ItemWearable &itemWearable);
protected:
	const bool isComplex_;
};


#endif