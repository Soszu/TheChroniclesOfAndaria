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

inline uint qHash(Effect::Category type)
{
	return qHash(toUnderlying(type));
}

QDataStream & operator<<(QDataStream & out, const Effect::Category & val)
{
	return out << toUnderlying(val);
}

QDataStream & operator>>(QDataStream & in, Effect::Category & val)
{
	return in >> toUnderlyingRef(val);
}

inline uint qHash(Effect::Type type)
{
	return qHash(toUnderlying(type));
}

QDataStream & operator<<(QDataStream & out, const Effect::Type & val)
{
	return out << toUnderlying(val);
}

QDataStream & operator>>(QDataStream & in, Effect::Type & val)
{
	return in >> toUnderlyingRef(val);
}

const BiHash<Effect::Category, QString> Effect::CategoryLabels = {
	{Category::Attributes,  QObject::tr("Attributes")},
	{Category::Damages,     QObject::tr("Damages")},
	{Category::Operations,  QObject::tr("Operations")},
	{Category::Bonuses,     QObject::tr("Bonuses")},
	{Category::States,      QObject::tr("States")},
};

const QHash<Effect::Category, QSet<Effect::Type>> Effect::Categories = {
	{Category::Attributes, {Type::MaxHealth, Type::Perception, Type::Defence,
	                        Type::Regeneration, Type::MovePoints,}},
	{Category::Damages,    {Type::MeleeBase, Type::MeleeRange,
	                        Type::RangedBase, Type::RangedRange,
	                        Type::MagicalBase, Type::MagicalRange,}},
	{Category::Operations, {Type::Heal, Type::Vamp, Type::Deflect,}},
	{Category::Bonuses,    {Type::GoldBonus, Type::ExperienceBonus,}},
	{Category::States,     {Type::Stun,}},
};

const BiHash<Effect::Type, QString> Effect::TypeLabels = {
	{Type::MaxHealth,       QObject::tr("Maximum Health")},
	{Type::Perception,      QObject::tr("Perception")},
	{Type::Defence,         QObject::tr("Defence")},
	{Type::Regeneration,    QObject::tr("Regeneration")},
	{Type::MovePoints,      QObject::tr("Move points")},

	{Type::MeleeBase,       QObject::tr("Melee attack base")},
	{Type::MeleeRange,      QObject::tr("Melee attack base")},
	{Type::RangedBase,      QObject::tr("Ranged attack base")},
	{Type::RangedRange,     QObject::tr("Ranged attack range")},
	{Type::MagicalBase,     QObject::tr("Magical attack base")},
	{Type::MagicalRange,    QObject::tr("Magical attack range")},

	{Type::Heal,            QObject::tr("Heal")},
	{Type::Vamp,            QObject::tr("Vamp")},
	{Type::Deflect,         QObject::tr("Deflect")},

	{Type::GoldBonus,       QObject::tr("Gold bonus")},
	{Type::ExperienceBonus, QObject::tr("Experience bonus")},

	{Type::Stun,            QObject::tr("Stun")},
};

QSet<Effect::Type> Effect::categoryContent(Effect::Category c)
{
	return Categories[c];
}

Effect::Category Effect::effectCategory(Effect::Type t)
{
	for (auto & cat : Categories.keys())
		if (Categories[cat].contains(t))
			return cat;

	Q_ASSERT(false);
	return Category::Attributes;
}

QString Effect::description(const Effect & effect)
{
	return TypeLabels[effect.type()]
	       + "(V: " + QString::number(effect.value())
	       + " D: " + QString::number(effect.duration()) + ")";
}

bool Effect::expired(const Effect & effect)
{
	return (effect.duration() == 0);
}

bool Effect::isInstant(const Effect & effect)
{
	return (effect.duration() == Effect::Instant);
}

bool Effect::isPermanent(const Effect & effect)
{
	return (effect.duration() == Effect::Permanent);
}

bool Effect::contains(const QList<Effect> & effects, Type type)
{
	for (auto &effect : effects)
		if (effect.type() == type)
			return true;
	return false;
}

QList<Effect> Effect::filter(const QList<Effect> & effects, Type type)
{
	QList<Effect> result;
	for (auto &effect : effects)
		if (effect.type() == type)
			result.append(effect);
	return result;
}

Effect::Value Effect::sumValue(const QList<Effect> & effects)
{
	Effect::Value sum= 0;
	for (auto &effect : effects)
		sum += effect.value();
	return sum;
}

Effect::Value Effect::sumValue(const QList<Effect> & effects, Type type)
{
	return sumValue(filter(effects, type));
}

Effect::Effect(Type type, Effect::Value value, Effect::Duration duration) :
	type_(type),
	value_(value),
	duration_(duration)
{}

bool Effect::operator==(const Effect & other) const
{
	return (type_ == other.type() && value_ == other.value() && duration_ == other.duration());
}

Effect::Duration Effect::duration() const
{
	return duration_;
}

QDataStream & Effect::toDataStream(QDataStream & out) const
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

QDataStream & Effect::fromDataStream(QDataStream & in)
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

QDataStream & operator<<(QDataStream & out, const Effect & effect)
{
	return effect.toDataStream(out);
}

QDataStream & operator>>(QDataStream & in, Effect & effect)
{
	return effect.fromDataStream(in);
}
