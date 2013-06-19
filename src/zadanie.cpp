#include "zadanie.h"

Zadanie::Zadanie(int id,
		 RodzajZadania rodzaj,
		 QString tytul,
		 QString tresc,
		 bool czyPowrot,
		 IDPola poleCelu,
		 char kolorCzcionki,
		 Nagroda* nagroda,
		 QList<Przeciwnik *> *przeciwnicy)
{
	this->id = id;
	this->rodzaj = rodzaj;
	this->tytul = tytul;
	this->tresc = tresc;
	this->czyPowrot = czyPowrot;
	this->poleCelu = poleCelu;
	this->kolorCzcionki = kolorCzcionki;
	this->nagroda = nagroda;
	this->przeciwnicy = przeciwnicy;

	czyWykonanoCzesc = czyPowrot ? false : true;
}

Zadanie::Zadanie(Zadanie *zad)
{
	this->id = zad->id;
	this->rodzaj = zad->rodzaj;
	this->tytul = zad->tytul;
	this->tresc = zad->tresc;
	this->czyPowrot = zad->czyPowrot;
	this->poleCelu = zad->poleCelu;
	this->kolorCzcionki = zad->kolorCzcionki;
	this->nagroda = zad->nagroda;

	przeciwnicy = new QList<Przeciwnik*>;
	for(int i = 0; i < zad->przeciwnicy->size(); ++i)
		przeciwnicy->push_back(zad->przeciwnicy->at(i));

	zleceniodawca = zad->zleceniodawca;

	czyWykonanoCzesc = czyPowrot ? false : true;
}

Zadanie::~Zadanie()
{
	delete przeciwnicy;
}

int Zadanie::getId()
{
	return id;
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

void Zadanie::setPoleCelu(IDPola pole)
{
	this->poleCelu = pole;
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

void Zadanie::setZeceniodawca(IDPola pole)
{
	zleceniodawca = pole;
}

IDPola Zadanie::getZleceniodawca()
{
	return zleceniodawca;
}

void Zadanie::setCzyWykonanoCzesc(bool wartosc)
{
	czyWykonanoCzesc = wartosc;
	qDebug("============================");
}

bool Zadanie::getCzyWykonanoCzesc()
{
	return czyWykonanoCzesc;
}
