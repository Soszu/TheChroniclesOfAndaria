#include "Core/Containers/Entity.h"

inline uint qHash(Attack attack)
{
	return qHash(toUnderlying(attack));
}

QDataStream & operator<<(QDataStream &out, const Attack &attack)
{
	return out << toUnderlying(attack);
}

QDataStream & operator>>(QDataStream &in, Attack &attack)
{
	return in >> toUnderlyingRef(attack);
}

Entity::Entity(): health_(0)
{}

quint16 Entity::health() const
{
	return health_;
}

QList <Effect> Entity::effects() const
{
	return individualEffects() + imposedEffects_;
}

Effect::Value Entity::value(Effect::Type type) const
{
	return Effect::sumValue(effects(), type);
}

void Entity::initHealth()
{
	health_ = value(Effect::Type::MaxHealth);
}

void Entity::heal(quint16 delta)
{
	health_ = qMin(value(Effect::Type::MaxHealth), health_ + delta);
}

void Entity::imposeEffect(const Effect &effect)
{
	imposedEffects_.append(effect);
}

void Entity::imposeEffects(const QList <Effect> & effects)
{
	for (auto &effect : effects)
		imposedEffects_.append(effect);
}
