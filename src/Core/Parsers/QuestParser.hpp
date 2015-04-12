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

#ifndef QUESTPARSER_H
#define QUESTPARSER_H

#include "Core/Containers/Enemy.hpp"
#include "Core/Containers/Quest.hpp"

class Mod;

class QuestParser {
public:
	QuestParser(Mod *dataKeeper);
	bool bladWczytywania();
	QString trescBledu;
private:
	quint8 wysokoscPlanszy;
	quint8 szerokoscPlanszy;
	bool bylBlad;
	Mod *dataKeeper;
	bool wczytajWymiary(QTextStream *wejscie);
	bool wczytajDane(QTextStream *wejscie);
	QString nastepny(QTextStream *wejscie);

	struct informacje {
		int id;
		int rodzaj;
		int poziom;
		int frakcja;
		QString tytul;
		QString tresc;
		bool czyPowrot;
		Coordinates cel;
		int idNagrody;
		QList <int> idWrogow;
	};
};

#endif
