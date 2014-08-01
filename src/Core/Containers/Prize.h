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

#ifndef PRIZE_H
#define PRIZE_H

#include <QtCore>

class Prize {

public:
	Prize(int *reputation, quint16 gold, quint16 experience, QStringList groupNames, const QList <int> &items);
	~Prize();

	int * reputation() const;
	quint16 gold() const;
	quint16 experience() const;
	QStringList groupNames() const;
	const QList <int> & items();

private:
	int *reputation_; //TODO CFiend to na pewno ma byc pointer, a nie np. kopia albo const pointer const?
	quint16 gold_;
	quint16 experience_;
	QStringList groupNames_;
	QList <int> items_;
};

#endif
