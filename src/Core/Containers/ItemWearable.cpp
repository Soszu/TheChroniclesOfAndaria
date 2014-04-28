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

#include <Core/Containers/ItemWearable.h>

ItemWearable::ItemWearable(QString name,
	   Item::Type type,
	   int bonusMelee,
	   int bonusRanged,
	   int bonusMagical,
	   int bonusDefence,
	   int bonusPerception,
	   int bonusHitPoints,
	   int bonusRegeneration,
	   int restrictions,
	   int value,
	   bool isStrong,
	   Item::Quality quality,
	   bool isComplex)
	: Item(name, 
			 type, 
			 bonusMelee,
			 bonusRanged, 
			 bonusMagical, 
			 bonusDefence, 
			 bonusPerception, 
			 bonusHitPoints, 
			 bonusRegeneration,
			 restrictions,
			 value,
			 isStrong,
			 quality),
	  isComplex_(isComplex)
{
}

ItemWearable::ItemWearable(//UID ID,
	     QString name,
	     //CharacterStats statsModifiers,
	     Item::Type type,
	     //QMap <Player::Class, bool> restriction,
	     int value,
	     Item::Quality quality,
	     bool isComplex)
	: Item(//ID_(ID),
			name,
			//statsModifiers_(statsModifiers),
			type,
			//restrictions_(restrictions),
			value,
			quality),
	  isComplex_(isComplex)
{
}


bool ItemWearable::isComplex() const
{
	return isComplex_;
}

QDataStream & operator<<(QDataStream &out, const ItemWearable &itemWearable)
{
	out //<< itemWearable.ID_
		 << itemWearable.name_
		 //<< itemWearable.statsModifiers_
		 << toUnderlying(itemWearable.type_)
		 << itemWearable.restrictions_
		 << itemWearable.value_
		 << toUnderlying(itemWearable.quality_)
		 << itemWearable.isStrong_;
	return out;
}

QDataStream & operator>>(QDataStream &in, ItemWearable &itemWearable)
{
	in //>> itemWearable.ID_
		>> itemWearable.name_
		//>> itemWearable.statsModifiers_
		>> toUnderlyingRef(itemWearable.type_)
		>> itemWearable.restrictions_
		>> itemWearable.value_
		>> toUnderlyingRef(itemWearable.quality_)
		>> itemWearable.isStrong_;
	return in;
}

