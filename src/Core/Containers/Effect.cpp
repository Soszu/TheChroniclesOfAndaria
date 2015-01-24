#include "Core/Containers/Effect.h"

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
	{Effect::Type::MaxHealth,       Label::MaxHealth},
	{Effect::Type::Perception,      Label::Perception},
	{Effect::Type::Defence,         Label::Defence},
	{Effect::Type::MeleeBase,       Label::MeleeBase},
	{Effect::Type::MeleeRange,      Label::MeleeRange},
	{Effect::Type::RangedBase,      Label::RangedBase},
	{Effect::Type::RangedRange,     Label::RangedRange},
	{Effect::Type::MagicalBase,     Label::MagicalBase},
	{Effect::Type::MagicalRange,    Label::MagicalRange},
	{Effect::Type::Regeneration,    Label::Regeneration},
	{Effect::Type::MovePoints,      Label::MovePoints},
	{Effect::Type::Heal,            Label::Heal},
	{Effect::Type::Vamp,            Label::Vamp},
	{Effect::Type::Deflect,         Label::Deflect},
	{Effect::Type::Absorb,          Label::Absorb},
	{Effect::Type::GoldBonus,       Label::GoldBonus},
	{Effect::Type::ExperienceBonus, Label::ExperienceBonus},
	{Effect::Type::Fear,            Label::Fear},
	{Effect::Type::Stun,            Label::Stun},
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

Effect::Effect(Type type, Effect::Value value, Effect::Duration duration)
      : type_(type), value_(value), duration_(duration)
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
