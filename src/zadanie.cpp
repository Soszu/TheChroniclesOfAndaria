#include "zadanie.h"

Zadanie::Zadanie(QString tytul, QString tresc, bool czyPowrot, quint8 poziomTrudnosci, IDPola poleCelu, Nagroda* nagroda)
{
	this->tytul = tytul;
	this->tresc = tresc;
	this->czyPowrot = czyPowrot;
	this->poziomTrudnosci = poziomTrudnosci;
	this->poleCelu = poleCelu;
	this->nagroda = nagroda;
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

quint8 Zadanie::getPoziomTrudnosci()
{
	return poziomTrudnosci;
}

IDPola Zadanie::getPoleCelu()
{
	return poleCelu;
}

Nagroda *Zadanie::getNagroda()
{
	return nagroda;
}
