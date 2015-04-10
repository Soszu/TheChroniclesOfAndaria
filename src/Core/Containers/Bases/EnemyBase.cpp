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
#include "EnemyBase.hpp"

#include "Core/Enums.hpp"
#include "Core/DataManager.hpp"
#include "Core/Containers/Entity.hpp"
#include "Core/Paths.hpp"

const BiHash <EnemyBase::Type, QString> EnemyBase::TypeLabels = {
	{EnemyBase::Type::Beast,    QObject::tr("Beast")},
	{EnemyBase::Type::Deamon,   QObject::tr("Demon")},
	{EnemyBase::Type::Humanoid, QObject::tr("Humanoid")},
	{EnemyBase::Type::Undead,   QObject::tr("Undead")},
};

inline uint qHash(EnemyBase::Type d)
{
	return qHash(toUnderlying(d));
}

QDataStream & operator<<(QDataStream & out, const EnemyBase::Type & t)
{
	return out << toUnderlying(t);
}

QDataStream & operator>>(QDataStream & in, EnemyBase::Type & t)
{
	return in >> toUnderlyingRef(t);
}

EnemyBase::EnemyBase(UID uid, QString name) :
	uid_(uid),
	name_(name),
	level_(0),
	difficulty_(Difficulty::Easy),
	type_(Type::Beast),
	defaultAttack_(Attack::Melee)
{
	//TODO add sth to baseStats [hp, armor, ...]
}

const QString & EnemyBase::name() const
{
	return name_;
}

const QString & EnemyBase::imageName() const
{
	return imageName_;
}

const QPixmap & EnemyBase::avatar() const
{
	return DataManager::pixmap(resolveEnemyImage(imageName_));
}

quint8 EnemyBase::level() const
{
	return level_;
}

Difficulty EnemyBase::difficulty() const
{
	return difficulty_;
}

EnemyBase::Type EnemyBase::type() const
{
	return type_;
}

Attack EnemyBase::defaultAttack() const
{
	return defaultAttack_;
}

const QList<Effect> & EnemyBase::baseStats() const
{
	return baseStats_;
}

const Prize & EnemyBase::prize() const
{
	return prize_;
}

QDataStream & EnemyBase::toDataStream(QDataStream & out) const
{
	return out << uid_ << name_ << imageName_ << level_ << type_ << defaultAttack_
	           << baseStats_ << prize_;
}

UID EnemyBase::uid() const
{
	return uid_;
}

void EnemyBase::addStat(const Effect & effect)
{
	baseStats_.append(effect);
}

QDataStream & EnemyBase::fromDataStream(QDataStream & in)
{
	return in >> uid_ >> name_ >> imageName_ >> level_ >> type_ >> defaultAttack_
	          >> baseStats_ >> prize_;
}

void EnemyBase::setName(const QString & name)
{
	name_ = name;
}

void EnemyBase::setImageName(const QString & imageName)
{
	imageName_ = imageName;
}

void EnemyBase::setLevel(quint8 level)
{
	level_ = level;
}

void EnemyBase::setDifficulty(Difficulty difficulty)
{
	difficulty_ = difficulty;
}

void EnemyBase::setType(EnemyBase::Type type)
{
	type_ = type;
}

void EnemyBase::setDefaultAttack(Attack type)
{
	defaultAttack_ = type;
}

void EnemyBase::setBaseStats(const QList <Effect> & baseStats)
{
	baseStats_ = baseStats;
}

void EnemyBase::setPrize(const Prize & prize)
{
	prize_ = prize;
}

QDataStream & operator<<(QDataStream & out, const EnemyBase & base)
{
	return base.toDataStream(out);
}

QDataStream & operator>>(QDataStream & in, EnemyBase & base)
{
	return base.fromDataStream(in);
}
