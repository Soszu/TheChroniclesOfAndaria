#ifndef PARSERPRZECIWNIKOW_H
#define PARSERPRZECIWNIKOW_H

#include <QMap>
#include "mistrzgry.h"
#include "przeciwnik.h"

class MistrzGry;

class ParserPrzeciwnikow
{
public:
	ParserPrzeciwnikow(MistrzGry* mistrzGry);
	bool bladWczytywania();
private:
	bool bylBlad;
	MistrzGry* mistrzGry;
	bool wczytajDane(QTextStream* wejscie);
	QString nastepny(QTextStream* wejscie);

	struct informacje{
		int id;
		QString nazwa;
		QString nazwaObrazka;
		QString opis;
		int atakMin;
		int atakMaks;
		int obrona;
		int zdrowie;
		int idNagrody;
	};

};

#endif // PARSERPRZECIWNIKOW_H
