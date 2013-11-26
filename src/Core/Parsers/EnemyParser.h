#ifndef ENEMYPARSER_H
#define ENEMYPARSER_H

#include <QtCore>

#include "Core/GameMaster.h"
#include "Core/Containers/Enemy.h"

class GameMaster;

class EnemyParser
{
public:
	EnemyParser(GameMaster* mistrzGry);
	bool bladWczytywania();
	QString trescBledu;
private:
	bool bylBlad;
	GameMaster* mistrzGry;
	bool wczytajDane(QTextStream* wejscie);
	QString nastepny(QTextStream* wejscie);
	int aktualnaGrupa;

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
