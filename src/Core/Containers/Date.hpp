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

class Date : public QObject{
public:
	static const quint8 DaysPerWeek = 5;
	Date() : day_(1), week_(1)
	{}

	Date(quint8 day, quint16 week) : day_(day), week_(week)
	{}

	quint8 day() const
	{
		return day_;
	}

	quint32 week() const
	{
		return week_;
	}

	static bool isValid(Date d) const
	{
		return (d.day() >= 1 && d.day() <= DaysPerWeek && week_ >= 1);
	}

public slots:
	void increment()
	{
		emit newDay(++day_);

		if (day > DaysPerWeek) {
			day = 1;
			emit newWeek(++week_);
		}
	}

private:
	quint8 day_;
	quint32 week_;

signals:
	void newDay(quint8 day);
	void newWeek(quint8 week);
};
