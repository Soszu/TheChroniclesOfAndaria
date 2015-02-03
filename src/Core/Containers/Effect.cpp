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
	{Effect::Type::MaxHealth,       Labels::Effect::Types::MaxHealth},
	{Effect::Type::Perception,      Labels::Effect::Types::Perception},
	{Effect::Type::Defence,         Labels::Effect::Types::Defence},
	{Effect::Type::MeleeBase,       Labels::Effect::Types::MeleeBase},
	{Effect::Type::MeleeRange,      Labels::Effect::Types::MeleeRange},
	{Effect::Type::RangedBase,      Labels::Effect::Types::RangedBase},
	{Effect::Type::RangedRange,     Labels::Effect::Types::RangedRange},
	{Effect::Type::MagicalBase,     Labels::Effect::Types::MagicalBase},
	{Effect::Type::MagicalRange,    Labels::Effect::Types::MagicalRange},
	{Effect::Type::Regeneration,    Labels::Effect::Types::Regeneration},
	{Effect::Type::MovePoints,      Labels::Effect::Types::MovePoints},
	{Effect::Type::Heal,            Labels::Effect::Types::Heal},
	{Effect::Type::Vamp,            Labels::Effect::Types::Vamp},
	{Effect::Type::Deflect,         Labels::Effect::Types::Deflect},
	{Effect::Type::Absorb,          Labels::Effect::Types::Absorb},
	{Effect::Type::GoldBonus,       Labels::Effect::Types::GoldBonus},
	{Effect::Type::ExperienceBonus, Labels::Effect::Types::ExperienceBonus},
	{Effect::Type::Fear,            Labels::Effect::Types::Fear},
	{Effect::Type::Stun,            Labels::Effect::Types::Stun},
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

bool Effect::isDisposable(const Effect &effect)
{
	return (effect.duration() == Effect::Disposable);
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
