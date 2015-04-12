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
#include "Core/Containers/Tests/TestData.hpp"


TestData::TestData(Test::Type type, const QVariant & data) :
	type_(type),
	data_(data)
{}

Test::Type TestData::type() const
{
	return type_;
}

const QVariant & TestData::data() const
{
	return data_;
}

QDataStream & TestData::toDataStream(QDataStream & out) const
{
	return out << type_ << data_;
}

QDataStream & TestData::fromDataStream(QDataStream & in)
{
	return in >> type_ >> data_;
}

void TestData::setType(Test::Type type)
{
	type_ = type;
}

void TestData::setData(const QVariant & data)
{
	data_ = data;
}

QDataStream & operator<<(QDataStream & out, const TestData & val)
{
	return val.toDataStream(out);
}

QDataStream & operator>>(QDataStream & in, TestData & val)
{
	return val.fromDataStream(in);
}
