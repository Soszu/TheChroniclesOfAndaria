#ifndef ZADANIE_H
#define ZADANIE_H
#include <QString>
#include "nagroda.h"
#include "przeciwnik.h"
#include "gra.h"

class Zadanie
{
public:
	Zadanie(int id,
		RodzajZadania rodzaj,
		QString tytul,
		QString tresc,
		bool czyPowrot,
		IDPola poleCelu,
		char kolorCzcionki,
		Nagroda* nagroda,
		QList<Przeciwnik*>* przeciwnicy);
	Zadanie(Zadanie* zad);
	~Zadanie();

	int getId();
	RodzajZadania getRodzaj();
	QString getTytul();
	QString getTresc();
	bool getCzyPowrot();
	IDPola getPoleCelu();
	void setPoleCelu(IDPola pole);
	char getKolorCzcionki();
	Nagroda* getNagroda();
	QList<Przeciwnik*>* getPrzeciwnicy();
	void setZeceniodawca(IDPola pole);
	IDPola getZleceniodawca();
	void setCzyWykonanoCzesc(bool wartosc);
	bool getCzyWykonanoCzesc();

private:
	int id;
	RodzajZadania rodzaj;
	QString tytul;
	QString tresc;
	bool czyPowrot;
	IDPola poleCelu;
	char kolorCzcionki;
	Nagroda* nagroda;
	QList<Przeciwnik*>* przeciwnicy;
	IDPola zleceniodawca;
	bool czyWykonanoCzesc;
};

#endif // ZADANIE_H
