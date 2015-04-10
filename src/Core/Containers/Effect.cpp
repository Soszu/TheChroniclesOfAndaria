/*
Copyright (C) 2014-2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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
#include "Core/Containers/Effect.hpp"
#include "Core/Strings.hpp"

inline uint qHash(Effect::Type type)
{
	return qHash(toUnderlying(type));
}

QDataStream & operator<<(QDataStream &out, const Effect::Type &effectType)
{
	return out << toUnderlying(effectType);
}

QDataStream & operator>>(QDataStream &in, Effect::Type &effectType)
{
	return in >> toUnderlyingRef(effectType);
}

const BiHash <Effect::Type, QString> Effect::TypeLabels = {
	{Effect::Type::MaxHealth,       QObject::tr("Maximum Health")},
	{Effect::Type::Perception,      QObject::tr("Perception")},
	{Effect::Type::Defence,         QObject::tr("Defence")},
	{Effect::Type::MeleeBase,       QObject::tr("Melee attack base")},
	{Effect::Type::MeleeRange,      QObject::tr("Melee attack base")},
	{Effect::Type::RangedBase,      QObject::tr("Ranged attack base")},
	{Effect::Type::RangedRange,     QObject::tr("Ranged attack range")},
	{Effect::Type::MagicalBase,     QObject::tr("Magical attack base")},
	{Effect::Type::MagicalRange,    QObject::tr("Magical attack range")},
	{Effect::Type::Regeneration,    QObject::tr("Regeneraion")},
	{Effect::Type::MovePoints,      QObject::tr("Move points")},
	{Effect::Type::Heal,            QObject::tr("Heal")},
	{Effect::Type::Vamp,            QObject::tr("Vamp")},
	{Effect::Type::Deflect,         QObject::tr("Deflect")},
	{Effect::Type::Absorb,          QObject::tr("Absorb")},
	{Effect::Type::GoldBonus,       QObject::tr("Gold bonus")},
	{Effect::Type::ExperienceBonus, QObject::tr("Experience bonus")},
	{Effect::Type::Fear,            QObject::tr("Fear")},
	{Effect::Type::Stun,            QObject::tr("Stun")},
};
QString Effect::description(const Effect &effect)
{
	return TypeLabels[effect.type()]
	       + "(V: " + QString::number(effect.value())
	       + " D: " + QString::number(effect.duration()) + ")";
}

bool Effect::expired(const Effect &effect)
{
	return (effect.duration() == 0);
}

bool Effect::isInstant(const Effect &effect)
{
	return (effect.duration() == Effect::Instant);
}

bool Effect::isPermanent(const Effect &effect)
{
	return (effect.duration() == Effect::Permanent);
}

bool Effect::contains(const QList <Effect> &effects, Type type)
{
	for (auto &effect : effects)
		if (effect.type() == type)
			return true;
	return false;
}

QList <Effect> Effect::filter(const QList <Effect> &effects, Type type)
{
	QList <Effect> result;
	for (auto &effect : effects)
		if (effect.type() == type)
			result.append(effect);
	return result;
}

Effect::Value Effect::sumValue(const QList <Effect> &effects)
{
	Effect::Value sum= 0;
	for (auto &effect : effects)
		sum += effect.value();
	return sum;
}

Effect::Value Effect::sumValue(const QList <Effect> &effects, Type type)
{
	return sumValue(filter(effects, type));
}

Effect::Effect(Type type, Effect::Value value, Effect::Duration duration) :
	type_(type),
	value_(value),
	duration_(duration)
{}

bool Effect::operator==(const Effect &other) const
{
	return (type_ == other.type() && value_ == other.value() && duration_ == other.duration());
}

Effect::Duration Effect::duration() const
{
	return duration_;
}

QDataStream & Effect::toDataStream(QDataStream &out) const
{
	return out << toUnderlying(type_) << value_ << duration_;
}

Effect::Type Effect::type() const
{
	return type_;
}

Effect::Value Effect::value() const
{
	return value_;
}

QDataStream & Effect::fromDataStream(QDataStream &in)
{
	return in >> type_ >> value_ >> duration_;
}

void Effect::setDuration(Effect::Duration duration)
{
	duration_ = duration;
}

void Effect::setType(Effect::Type type)
{
	type_ = type;
}

void Effect::setValue(Effect::Value value)
{
	value_ = value;
}

void Effect::shorten()
{
	if (duration_ > 0)
		--duration_;
}

QDataStream & operator<<(QDataStream &out, const Effect &effect)
{
	return effect.toDataStream(out);
}

QDataStream & operator>>(QDataStream &in, Effect &effect)
{
	return effect.fromDataStream(in);
}
