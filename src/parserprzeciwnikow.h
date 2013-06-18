#ifndef PARSERPRZECIWNIKOW_H
#define PARSERPRZECIWNIKOW_H

#include <QMap>
#include <QList>
#include "mistrzgry.h"
#include "przeciwnik.h"

class MistrzGry;

class ParserPrzeciwnikow
{
public:
	ParserPrzeciwnikow(MistrzGry* mistrzGry);
	bool bladWczytywania();
	QString trescBledu;
private:
	bool bylBlad;
	MistrzGry* mistrzGry;
	bool wczytajDane(QTextStream* wejscie);
	QString nastepny(QTextStream* wejscie);
	int aktualnaGrupa;

	struct informacje{
		int id;
		QString nazwa;
		QString nazwaObrazka;
		int atakMin;
		int atakMaks;
		int obrona;
		int percepcja;
		int zdrowie;
		int idNagrody;
	};

};

#endif // PARSERPRZECIWNIKOW_H
