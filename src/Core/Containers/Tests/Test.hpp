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
#pragma once

#include <QtCore>

class TestData;

// virtual class; super class for specific types of tests; also works as test factory
class Test {
	//factory method
	static Test * createTest(const TestData & data);
public:
// 	enum class Result : quint8 {
// 		Fail,
// 		Pass,
// 		Unsettled
// 	};

	enum class Type : quint8 {
		Blank,
		Fight,
		Luck,
		Skills,
	};

	virtual Type type() const = 0;
	// 	TODO some virtual methods for taking test
};
Q_DECLARE_METATYPE(Test::Type)
uint qHash(Test::Type type);
QDataStream & operator<<(QDataStream & out, const Test::Type & val);
QDataStream & operator>>(QDataStream & in, Test::Type & val);
