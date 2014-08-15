/*
Copyright (C) 2013 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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

#pragma once

#include <QtCore>
#include "Core/Utils/BiHash.hpp"
#include "Core/Utils/EnumHelpers.hpp"
#include "Core/Strings.h"
#include "Core/Containers/Terrain.h"

enum class ActionId : quint8 {
	//TODO
};

class Coordinates : public QPoint
{
	friend uint qHash(const Coordinates &c, uint seed);
public:
	constexpr Coordinates(QPoint p = QPoint{0, 0}) : QPoint(p) {}
	constexpr Coordinates(int x, int y) : Coordinates(QPoint(x, y)) {}

	QString toString() const {return QString("[%1, %2]").arg(x()).arg(y());}
};

inline uint qHash(const Coordinates &c, uint seed)
{
	return qHash(QPair <int, int>(c.x(), c.y()), seed);
}

enum class Kingdom : quint8 {
	Neutral,
	Humans,
	Dwarfs,
	Elves,
	Halflings
};
uint qHash(Kingdom kingdom);
QDataStream & operator<<(QDataStream &out, const Kingdom &kingdom);
QDataStream & operator>>(QDataStream &in, Kingdom &kingdom);


class Field {
public:
	Field(Coordinates coordinates, Kingdom kingdom, Terrain *terrain);
	const QList <ActionId> & actions() const;
	quint8 coefficient() const;
	Coordinates coordinates() const;
	const QString & imagePath() const;
	Kingdom kingdom() const;
	const QString & name() const;

private:
	Coordinates coordinates_;
	Kingdom kingdom_;
	const Terrain *terrain_;
};
