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

#include "Core/Containers/Item.h"

Item::Item(QString name,
	   ItemType type,
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
	   ItemQuality quality)
	: name_(name),
	  type_(type),
	  bonusMelee_(bonusMelee),
	  bonusRanged_(bonusRanged),
	  bonusMagical_(bonusMagical),
	  bonusDefence_(bonusDefence),
	  bonusPerception_(bonusPerception),
	  bonusHitPoints_(bonusHitPoints),
	  bonusRegeneration_(bonusRegeneration),
	  restrictions_(restrictions),
	  value_(value),
	  isStrong_(isStrong),
	  quality_(quality)
{
}

QString Item::name() const
{
	return name_;
}

ItemType Item::type() const
{
	return type_;
}

int Item::bonusMelee() const
{
	return bonusMelee_;
}

int Item::bonusRanged() const
{
	return bonusRanged_;
}

int Item::bonusMagical() const
{
	return bonusMagical_;
}

int Item::bonusDefence() const
{
	return bonusDefence_;
}

int Item::bonusPerception() const
{
	return bonusPerception_;
}

int Item::restrictions() const
{
	return restrictions_;
}

int Item::value() const
{
	return value_;
}

bool Item::isStrong() const
{
	return isStrong_;
}

ItemQuality Item::quality() const
{
	return quality_;
}

int Item::bonusRegeneration() const
{
	return bonusRegeneration_;
}

int Item::bonusHitPoints() const
{
	return bonusHitPoints_;
}
