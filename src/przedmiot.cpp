#include "przedmiot.h"

Przedmiot::Przedmiot(QString nazwa, quint8 wartosc, QString opis, bool czyPo5Lvlu, quint8 ograniczenia, RodzajPrzedmiotu rodzaj)
{
	this->nazwa = nazwa;
	this->wartosc = wartosc;
	this->opis = opis;
	this->czyPo5Lvlu = czyPo5Lvlu;
	this->ograniczenia = ograniczenia;
	this->rodzaj = rodzaj;
}

QString Przedmiot::getNazwa()
{
	return nazwa;
}

quint8 Przedmiot::getWartosc()
{
	return wartosc;
}

QString Przedmiot::getOpis()
{
	return opis;
}

bool Przedmiot::getCzyPo5Lvlu()
{
	return czyPo5Lvlu;
}

quint8 Przedmiot::getOgraniczenia()
{
	return ograniczenia;
}

RodzajPrzedmiotu Przedmiot::getRodzaj()
{
	return rodzaj;
}
