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