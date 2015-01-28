/*
 * Copyright (C) 2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
 * This file is part of The Chronicles Of Andaria Project.
 *
 *	The Chronicles of Andaria Project is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	The Chronicles of Andaria Project is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with The Chronicles Of Andaria.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "Enums.hpp"

#include "Core/Utils/EnumHelpers.hpp"
#include "Core/Strings.h"

inline uint qHash(Kingdom kingdom)
{
	return qHash(toUnderlying(kingdom));
}

QDataStream & operator<<(QDataStream &out, Kingdom kingdom)
{
	return out << toUnderlying(kingdom);
}

QDataStream & operator>>(QDataStream &in, Kingdom kingdom)
{
	return in >> toUnderlyingRef(kingdom);
}

inline uint qHash(Race playerRace)
{
	return qHash(toUnderlying(playerRace));
}

QDataStream & operator<<(QDataStream &out, const Race &playerRace)
{
	return out << toUnderlying(playerRace);
}

QDataStream & operator>>(QDataStream &in, Race &playerRace)
{
	return in >> toUnderlyingRef(playerRace);
}

inline uint qHash(Class playerClass)
{
	return qHash(toUnderlying(playerClass));
}

QDataStream & operator<<(QDataStream &out, const Class &playerClass)
{
	return out << toUnderlying(playerClass);
}

QDataStream & operator>>(QDataStream &in, Class &playerClass)
{
	return in >> toUnderlyingRef(playerClass);
}

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

inline uint qHash(Action action)
{
	return qHash(toUnderlying(action));
}

QDataStream & operator<<(QDataStream &out, const Action &action)
{
	return out << toUnderlying(action);
}

QDataStream & operator>>(QDataStream &in, Action &action)
{
	return in >> toUnderlyingRef(action);
}
