#include "przedmiot.h"

Przedmiot::Przedmiot(QString nazwa,
		     RodzajPrzedmiotu rodzaj,
		     quint8 bonusAWrecz,
		     quint8 bonusADystansowy,
		     quint8 bonusAMagiczny,
		     quint8 bonusObrona,
		     quint8 bonusPercepcja,
		     quint8 bonusHP,
		     quint8 bonusHPregen,
		     int ograniczenia,
		     quint8 wartosc,
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

quint8 Przedmiot::getBonusAWrecz()
{
	return bonusAWrecz;
}

quint8 Przedmiot::getBonusADystansowy()
{
	return bonusADystansowy;
}

quint8 Przedmiot::getBonusAMagiczny()
{
	return bonusAMagiczny;
}

quint8 Przedmiot::getBonusObrona()
{
	return bonusObrona;
}

quint8 Przedmiot::getBonusPercepcja()
{
	return bonusPercepcja;
}

int Przedmiot::getOgraniczenia()
{
	return ograniczenia;
}

quint8 Przedmiot::getWartosc()
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

quint8 Przedmiot::getBonusHPregen()
{
	return bonusHPregen;
}

quint8 Przedmiot::getBonusHP()
{
	return bonusHP;
}
