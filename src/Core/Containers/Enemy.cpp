/*
Copyright (C) 2013-2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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

#include "Core/Containers/Enemy.hpp"
#include "Core/Containers/Bases/EnemyBase.hpp"
#include "Core/DataManager.hpp"

Enemy::Enemy(const EnemyBase * base) :
	base_(base)
{
	initHealth();
}

const QString & Enemy::name() const
{
	return base_->name();
}

const QPixmap & Enemy::avatar() const
{
	return base_->avatar();
}

quint8 Enemy::level() const
{
	return base_->level();
}

Difficulty Enemy::difficulty() const
{
	return base_->difficulty();
}

EnemyBase::Type Enemy::type() const
{
	return base_->type();
}

Attack Enemy::defaultAttack() const
{
	return base_->defaultAttack();
}

const QList <Effect> Enemy::individualEffects() const
{
	return base_->baseStats();
}

const Prize & Enemy::prize() const
{
	return base_->prize();
}

QDataStream & Enemy::toDataStream(QDataStream &out) const
{
	return out << base_->uid();
}

QDataStream & Enemy::fromDataStream(QDataStream &in)
{
	UID uid;
	in >> uid;
	//TODO
	// 	base_ = DataKeeper::giveEnemyBaseByUid(uid);
	return in;
}

QDataStream & operator<<(QDataStream & out, const Enemy & enemy)
{
	return enemy.toDataStream(out);
}

QDataStream & operator>>(QDataStream & in, Enemy & enemy)
{
	return enemy.fromDataStream(in);
}
