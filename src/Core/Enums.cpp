/*
Copyright (C) 2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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
#include "Enums.hpp"

#include "Core/Utils/EnumHelpers.hpp"

inline uint qHash(Kingdom val)
{
	return qHash(toUnderlying(val));
}

QDataStream & operator<<(QDataStream & out, const Kingdom & val)
{
	return out << toUnderlying(val);
}

QDataStream & operator>>(QDataStream & in, Kingdom & val)
{
	return in >> toUnderlyingRef(val);
}

inline uint qHash(Race val)
{
	return qHash(toUnderlying(val));
}

QDataStream & operator<<(QDataStream & out, const Race & val)
{
	return out << toUnderlying(val);
}

QDataStream & operator>>(QDataStream & in, Race & val)
{
	return in >> toUnderlyingRef(val);
}

inline uint qHash(Class val)
{
	return qHash(toUnderlying(val));
}

QDataStream & operator<<(QDataStream & out, const Class & val)
{
	return out << toUnderlying(val);
}

QDataStream & operator>>(QDataStream & in, Class & val)
{
	return in >> toUnderlyingRef(val);
}

inline uint qHash(Attack val)
{
	return qHash(toUnderlying(val));
}

QDataStream & operator<<(QDataStream & out, const Attack & val)
{
	return out << toUnderlying(val);
}

QDataStream & operator>>(QDataStream & in, Attack & val)
{
	return in >> toUnderlyingRef(val);
}

inline uint qHash(Action val)
{
	return qHash(toUnderlying(val));
}

QDataStream & operator<<(QDataStream & out, const Action & val)
{
	return out << toUnderlying(val);
}

QDataStream & operator>>(QDataStream & in, Action & val)
{
	return in >> toUnderlyingRef(val);
}

inline uint qHash(Difficulty val)
{
	return qHash(toUnderlying(val));
}

QDataStream & operator<<(QDataStream & out, const Difficulty & val)
{
	return out << toUnderlying(val);
}

QDataStream & operator>>(QDataStream & in, Difficulty & val)
{
	return in >> toUnderlyingRef(val);
}
