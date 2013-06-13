#include "zadanie.h"

Zadanie::Zadanie(RodzajZadania rodzaj, QString tytul, QString tresc, bool czyPowrot, IDPola poleCelu, char kolorCzcionki, Nagroda* nagroda, QList<Przeciwnik *> *przeciwnicy)
{
	this->rodzaj = rodzaj;
	this->tytul = tytul;
	this->tresc = tresc;
	this->czyPowrot = czyPowrot;
	this->poleCelu = poleCelu;
	this->kolorCzcionki = kolorCzcionki;
	this->nagroda = nagroda;
	this->przeciwnicy = przeciwnicy;
}

Zadanie::~Zadanie()
{
	delete przeciwnicy;
}

RodzajZadania Zadanie::getRodzaj()
{
	return rodzaj;
}

QString Zadanie::getTytul()
{
	return tytul;
}

QString Zadanie::getTresc()
{
	return tresc;
}

bool Zadanie::getCzyPowrot()
{
	return czyPowrot;
}

IDPola Zadanie::getPoleCelu()
{
	return poleCelu;
}

char Zadanie::getKolorCzcionki()
{
	return kolorCzcionki;
}

Nagroda *Zadanie::getNagroda()
{
	return nagroda;
}

QList<Przeciwnik *> *Zadanie::getPrzeciwnicy()
{
	return przeciwnicy;
}
