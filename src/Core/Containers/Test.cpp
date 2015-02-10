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
#include "Test.hpp"

Test::Test(Test::Type type, const QVariant & data) :
	type_(type),
	data_(data)
{}

Test::Type Test::type() const
{
	return type_;
}

const QVariant & Test::data() const
{
	return data_;
}

void Test::setType(Test::Type type)
{
	type_ = type;
}

void Test::setData(const QVariant & data)
{
	data_ = data;
}

QDataStream & operator<<(QDataStream & out, const Test & effectType)
{
	return out;
}

QDataStream & operator>>(QDataStream & in, Test & effectType)
{
	return in;
}
