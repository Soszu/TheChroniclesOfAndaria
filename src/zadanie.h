#ifndef ZADANIE_H
#define ZADANIE_H
#include <QString>
#include "nagroda.h"
#include "przeciwnik.h"
#include "gra.h"

class Zadanie
{
public:
	Zadanie(RodzajZadania rodzaj,
		QString tytul,
		QString tresc,
		bool czyPowrot,
		IDPola poleCelu,
		char kolorCzcionki,
		Nagroda* nagroda,
		QList<Przeciwnik*>* przeciwnicy);
	~Zadanie();

	RodzajZadania getRodzaj();
	QString getTytul();
	QString getTresc();
	bool getCzyPowrot();
	IDPola getPoleCelu();
	char getKolorCzcionki();
	Nagroda* getNagroda();
	QList<Przeciwnik*>* getPrzeciwnicy();

private:

	RodzajZadania rodzaj;
	QString tytul;
	QString tresc;
	bool czyPowrot;
	IDPola poleCelu;
	char kolorCzcionki;
	Nagroda* nagroda;
	QList<Przeciwnik*>* przeciwnicy;
};

#endif // ZADANIE_H
