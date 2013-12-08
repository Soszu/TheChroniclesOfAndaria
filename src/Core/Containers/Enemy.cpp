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

#include "Core/Containers/Enemy.h"

Enemy::Enemy(QString name, QString pictureName, int attackMin, int attackMax, int defence, int perception, int healthMax, Prize *prize)
	: name_(name),
	  pictureName_(pictureName),
	  attackMin_(attackMin),
	  attackMax_(attackMax),
	  defence_(defence),
	  perception_(perception),
	  healthMax_(healthMax),
	  prize_(prize)
{
}

QString Enemy::name() const
{
	return name_;
}

QString Enemy::pictureName() const
{
	return pictureName_;
}

int Enemy::attackMin() const
{
	return attackMin_;
}

int Enemy::attackMax() const
{
	return attackMax_;
}

int Enemy::defence() const
{
	return defence_;
}

int Enemy::perception() const
{
	return perception_;
}

int Enemy::healthMax() const
{
	return healthMax_;
}

Prize * Enemy::prize() const
{
	return prize_;
}
