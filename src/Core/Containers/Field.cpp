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

Field::Field (FieldId fieldId, QString name, int coefficient, bool hasEnemy, bool hasCity, QString imageFile, int fraction)
    : fieldId_(fieldId), name_(name), moveCost_(coefficient), hasEnemy_(hasEnemy), hasCity_(hasCity), imageFile_(imageFile), fraction_(fraction)
{
}

FieldId Field::fieldId() const
{
	return fieldId_;
}

QString Field::name() const
{
	return name_;
}

int Field::moveCost() const
{
	return moveCost_;
}

bool Field::hasEnemy() const
{
	return hasEnemy_;
}

bool Field::hasCity() const
{
	return hasCity_;
}

QString Field::imageFile() const
{
	return imageFile_;
}

int Field::fraction() const
{
	return fraction_;
}
