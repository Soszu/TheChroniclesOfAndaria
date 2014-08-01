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

#include "Core/Containers/Prize.h"

Prize::Prize(int *reputation, quint16 gold, quint16 experience, QStringList groupNames, const QList <int> &items)
	: reputation_(reputation), gold_(gold), experience_(experience), groupNames_(groupNames), items_(items)
{
}

Prize::~Prize()
{
	delete [] reputation_; //TODO CFiend skad wiadomo, ze to nalezy do nas? Moze lepiej trzymac stala tablice, zamiast alokowac na stercie?
}

int * Prize::reputation() const
{
	return reputation_;
}

quint16 Prize::gold() const
{
	return gold_;
}

quint16 Prize::experience() const
{
	return experience_;
}

QStringList Prize::groupNames() const
{
	return groupNames_;
}

const QList<int> & Prize::items()
{
	return items_;
}
