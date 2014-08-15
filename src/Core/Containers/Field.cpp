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

#include "Core/Containers/Field.h"

inline uint qHash(const QPoint& p)
{
	return qHash(p.x()+p.y());
}

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

static const BiHash <Kingdom, QString> KingdomLabels {
	{Kingdom::Neutral, Label::Neutral},
	{Kingdom::Humans, Label::Humans},
	{Kingdom::Dwarfs, Label::Dwarfs},
	{Kingdom::Elves, Label::Elves},
	{Kingdom::Halflings, Label::Halflings}
};

Field::Field(Coordinates coordinates, Kingdom kingdom, Terrain *terrain)
     : coordinates_(coordinates), kingdom_(kingdom), terrain_(terrain)
{}

const QList <ActionId> & Field::actions() const
{
	return terrain_->actions();
}

Coordinates Field::coordinates() const
{
	return coordinates_;
}

quint8 Field::coefficient() const
{
	return terrain_->coefficient();
}

const QString & Field::imagePath() const
{
	return terrain_->imagePath();
}

Kingdom Field::kingdom() const
{
	return kingdom_;
}

const QString & Field::name() const
{
	return terrain_->name();
}
