#include "przedmiot.h"

Przedmiot::Przedmiot(QString nazwa,
		     RodzajPrzedmiotu rodzaj,
		     int bonusAWrecz,
		     int bonusADystansowy,
		     int bonusAMagiczny,
		     int bonusObrona,
		     int bonusPercepcja,
		     int bonusHP,
		     int bonusHPregen,
		     int ograniczenia,
		     int wartosc,
		     bool czyMocny,
		     QColor kolorCzcionki)
{
	this->nazwa = nazwa;
	this->rodzaj = rodzaj;
	this->bonusAWrecz = bonusAWrecz;
	this->bonusADystansowy = bonusADystansowy;
	this->bonusAMagiczny = bonusAMagiczny;
	this->bonusObrona = bonusObrona;
	this->bonusPercepcja = bonusPercepcja;
	this->bonusHP = bonusHP;
	this->bonusHPregen = bonusHPregen;
	this->ograniczenia = ograniczenia;
	this->wartosc = wartosc;
	this->czyMocny = czyMocny;
	this->kolorCzcionki = kolorCzcionki;
}

QString Przedmiot::getNazwa()
{
	return nazwa;
}

RodzajPrzedmiotu Przedmiot::getRodzaj()
{
	return rodzaj;
}

int Przedmiot::getBonusAWrecz()
{
	return bonusAWrecz;
}

int Przedmiot::getBonusADystansowy()
{
	return bonusADystansowy;
}

int Przedmiot::getBonusAMagiczny()
{
	return bonusAMagiczny;
}

int Przedmiot::getBonusObrona()
{
	return bonusObrona;
}

int Przedmiot::getBonusPercepcja()
{
	return bonusPercepcja;
}

int Przedmiot::getOgraniczenia()
{
	return ograniczenia;
}

int Przedmiot::getWartosc()
{
	return wartosc;
}

bool Przedmiot::getCzyMocny()
{
	return czyMocny;
}

QColor Przedmiot::getKolorCzcionki()
{
	return kolorCzcionki;
}

int Przedmiot::getBonusHPregen()
{
	return bonusHPregen;
}

int Przedmiot::getBonusHP()
{
	return bonusHP;
}
