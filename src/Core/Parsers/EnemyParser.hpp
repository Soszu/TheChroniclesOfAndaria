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

#ifndef ENEMYPARSER_H
#define ENEMYPARSER_H

#include <QtCore>

#include "Core/Mod.hpp"

class Mod;

class EnemyParser {

public:
	EnemyParser(Mod *dataKeeper);
	bool bladWczytywania();
	QString trescBledu;

private:
	bool bylBlad;
	Mod *dataKeeper;
	bool wczytajDane(QTextStream* wejscie);
	QString nastepny(QTextStream* wejscie);
	int aktualnaGrupa;
	QMap <int, QList <int> *> enemyGroups_;

	struct informacje{
		int id;
		QString name;
		QString nameObrazka;
		int atakMin;
		int atakMaks;
		int defence;
		int perception;
		int zdrowie;
		int idNagrody;
	};

};

#endif
