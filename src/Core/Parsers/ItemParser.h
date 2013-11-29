#ifndef ITEMPARSER_H
#define ITEMPARSER_H

#include <QtCore>

#include "Core/GameMaster.h"
#include "Core/Containers/Item.h"
#include "Core/Game.h"

class GameMaster;

class ItemParser
{
public:
	ItemParser(GameMaster* mistrz);
	bool bladWczytywania();
	QString trescBledu;
private:
	bool bylBlad;
	GameMaster* mistrzGry;
	bool wczytajDane(QTextStream* wejscie);
	QString nastepny(QTextStream* wejscie);
	QString aktualnaGrupa;

	struct informacje{
		int id;
		QString name;
		char typ;
		int wrecz;
		int dystans;
		int magia;
		int defence;
		int perception;
		int HP;
		int HPregen;
		int ograniczenie;
		bool czy1Reczna;
		bool czyMocny;
		int wartosc;
		int jakosc;
	};
};

#endif
