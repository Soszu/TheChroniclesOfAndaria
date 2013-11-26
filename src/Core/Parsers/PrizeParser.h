#ifndef PRIZEPARSER_H
#define PRIZEPARSER_H

#include <QtCore>

#include "Core/GameMaster.h"
#include "Core/Game.h"
#include "Core/Containers/Prize.h"

class GameMaster;

class PrizeParser
{
public:
	PrizeParser(GameMaster* mistrz);
	bool bladWczytywania();
	QString trescBledu;
private:
	bool bylBlad;
	GameMaster* mistrzGry;
	bool wczytajDane(QTextStream* wejscie);
	QString nastepny(QTextStream* wejscie);

	struct informacje{
		int id;
		int* reputacja;
		int zloto;
		int doswiadczenie;
		QStringList grupy;
		QList<int>* przedmioty;
	};
};

#endif
