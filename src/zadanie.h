#ifndef ZADANIE_H
#define ZADANIE_H
#include <QString>
#include "nagroda.h"
#include "gra.h"

class Zadanie
{
public:
	Zadanie(QString tytul, QString tresc, bool czyPowrot, quint8 poziomTrudnosci, IDPola poleCelu, Nagroda* nagroda);

	QString getTytul();
	QString getTresc();
	bool getCzyPowrot();
	quint8 getPoziomTrudnosci();
	IDPola getPoleCelu();
	Nagroda* getNagroda();

private:
	QString tytul;
	QString tresc;
	bool czyPowrot;
	quint8 poziomTrudnosci;
	IDPola poleCelu;
	Nagroda* nagroda;
};

#endif // ZADANIE_H
