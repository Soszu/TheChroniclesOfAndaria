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

#ifndef ENEMY_H
#define ENEMY_H

#include "Core/Containers/Prize.h"
#include "FightParticipant.h"

class Enemy : public FightParticipant {

public:
	
	static const size_t NUMBER_OF_ENEMIES_GROUPS = 5;
	
	Enemy(QString name, 
			QString pictureName, 
			qint8 attackMin,
			//qint8 attackRange, NOTE change this after applying new mechanics
			qint8 attackMax, 
			qint8 defence, 
			qint8 perception, 
			qint8 healthMax,
			AttackType defaultAttack,
			const Prize *prize);

	QString name() const;
	QString pictureName() const;
	int attackMin() const;
	int attackRange() const;
	int attackMax() const;
	int defence() const;
	int perception() const;
	int healthMax() const;
	const Prize *prize() const;

protected:
	BattleStats baseStats_;
	AttackType defaultAttack_;
	const Prize *prize_;
};

#endif
