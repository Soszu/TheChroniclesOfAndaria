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
#include "Core/Containers/Entity.hpp"

Entity::Entity() :
	health_(0)
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
