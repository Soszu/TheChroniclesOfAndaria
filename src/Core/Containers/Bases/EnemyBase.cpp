/*
Copyright (C) 2013-2014 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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

#include "EnemyBase.h"
#include "Core/Containers/Entity.h"

EnemyBase::EnemyBase(UID uid, QString name)
         : uid_(uid),
           name_(name),
           level_(0),
           defaultAttack_(Attack::Melee)
{}

const QList <Effect> & EnemyBase::baseStats() const
{
	return baseStats_;
}

Attack EnemyBase::defaultAttack() const
{
	return defaultAttack_;
}

const QString &EnemyBase::imagePath() const
{
	return imagePath_;
}

quint8 EnemyBase::level() const
{
	return level_;
}

const QString &EnemyBase::name() const
{
	return name_;
}

const Prize & EnemyBase::prize() const
{
	return prize_;
}

QDataStream & EnemyBase::toDataStream(QDataStream &out) const
{
	return out << uid_ << name_ << imagePath_ << level_ << defaultAttack_ << baseStats_ << prize_;
}

UID EnemyBase::uid() const
{
	return uid_;
}

void EnemyBase::addStat(const Effect &effect)
{
	baseStats_.append(effect);
}

QDataStream & EnemyBase::fromDataStream(QDataStream &in)
{
	return in >> uid_ >> name_ >> imagePath_ >> level_ >> defaultAttack_ >> baseStats_ >> prize_;
}

void EnemyBase::setBaseStats(const QList <Effect> &baseStats)
{
	baseStats_ = baseStats;
}

void EnemyBase::setDefaultAttack(Attack type)
{
	defaultAttack_ = type;
}

void EnemyBase::setImagePath(const QString &imagePath)
{
	imagePath_ = imagePath;
}

void EnemyBase::setLevel(quint8 level)
{
	level_ = level;
}

void EnemyBase::setName(const QString &name)
{
	name_ = name;
}

void EnemyBase::setPrize(const Prize &prize)
{
	prize_ = prize;
}

QDataStream & operator<<(QDataStream &out, const EnemyBase &base)
{
	return base.toDataStream(out);
}

QDataStream & operator>>(QDataStream &in, EnemyBase &base)
{
	return base.fromDataStream(in);
}
