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

#ifndef BOARDPARSER_H
#define BOARDPARSER_H

#include <QtCore>

#include "Core/Board.h"

class Board;

class BoardParser {
public:
	BoardParser(Board* plansza);
	bool bladWczytywania();
	QString trescBledu;
private:
	bool bylBlad;
	Board* plansza;

	quint8 szerokosc;
	quint8 wysokosc;

	bool wczytajWymiary(QTextStream* wejscie);
	bool wczytajLegende(QTextStream* wejscie);
	bool wczytajUstawienie(QTextStream* wejscie);

	QString nastepny(QTextStream* wejscie);

	struct info{
		QString name;
		QString plik;
		bool czyPoleZEnemyiem;
		bool czyPoleZMiastem;
		int wspolczynnik;
		int frakcja;
	};
	QMap<QString, info> legenda;
};

#endif
