/**
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

#ifndef PRIZEPARSER_H
#define PRIZEPARSER_H

#include <QtCore>

#include "Core/Containers/Prize.hpp"
#include "Core/Enums.hpp"

class Mod;

class PrizeParser
{
public:
	PrizeParser(Mod *dataKeeper);
	bool bladWczytywania();
	QString trescBledu;
private:
	bool bylBlad;
	Mod *mod;
	bool wczytajDane(QTextStream* wejscie);
	QString nastepny(QTextStream* wejscie);

	struct informacje{
		int id;
		QHash <Kingdom, qint8> reputacja;
		uint zloto;
		uint doswiadczenie;
		QStringList grupy;
		QList<uint> przedmioty;
	};
};

#endif
