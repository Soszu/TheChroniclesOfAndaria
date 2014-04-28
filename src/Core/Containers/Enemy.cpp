/*
Copyright (C) 2013 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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

#include "Core/Containers/Enemy.h"

Enemy::Enemy(QString name, 
				 QString pictureName, 
				 qint8 attackMin,
				 //qint8 attackRange, NOTE change this after applying new mechanics
				 qint8 attackMax, 
				 qint8 defence, 
				 qint8 perception, 
				 qint8 healthMax,
				 AttackType defaultAttack,
				 Prize *prize)
	: FightParticipant(name, pictureName, healthMax),
	  baseStats_({healthMax, 
	              defence, 
	              perception, 
	              {{AttackType::Melee, {attackMin, attackMax - attackMin}}, 
	               {AttackType::Magical, {attackMin, attackMax - attackMin}}, 
	               {AttackType::Ranged, {attackMin, attackMax - attackMin}}}}),
	  defaultAttack_(defaultAttack),
	  prize_(prize)
{
}

QString Enemy::name() const
{
	return name_;
}

QString Enemy::pictureName() const
{
	return imageFile_;
}

int Enemy::attackMin() const
{
	return baseStats_.attacks_[defaultAttack_].first;
}

int Enemy::attackRange() const
{
	return baseStats_.attacks_[defaultAttack_].second;
}

int Enemy::attackMax() const
{
	return baseStats_.attacks_[defaultAttack_].second + baseStats_.attacks_[defaultAttack_].first;
}

int Enemy::defence() const
{
	return baseStats_.defence_;
}

int Enemy::perception() const
{
	return baseStats_.perception_;
}

int Enemy::healthMax() const
{
	return baseStats_.healthMax_;
}

Prize * Enemy::prize() const
{
	return prize_;
}
