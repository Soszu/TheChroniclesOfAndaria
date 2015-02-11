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

#include "Core/Mod.hpp"
#include "Core/Paths.hpp"
#include "Core/Enums.hpp"
#include "Core/Containers/Player.hpp"

class Mod;

class BoardParser {
public:
	BoardParser(Mod *dataKeeper);
	bool bladWczytywania();
	QString trescBledu;
private:
	const QHash <Race, Coordinates> initialPositions_{
		{Race::Human, {18,3}},
		{Race::Dwarf, {14,18}},
		{Race::Elf, {28,8}},
		{Race::Halfling, {2,8}}
	};

	const QHash <int, Kingdom> kingdoms{
		{0, Kingdom::Humans},
		{1, Kingdom::Dwarfs},
		{2, Kingdom::Elves},
		{3, Kingdom::Halflings},
		{4, Kingdom::Neutral}
	};

	bool bylBlad;
	Mod *dataKeeper;

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
		UID uid;
	};
	QMap<QString, info> legenda;
};

#endif
