#include "przedmiot.h"

Przedmiot::Przedmiot(QString nazwa, short wartosc, QString opis, bool czyPo5Lvlu, short ograniczenia, int rodzaj)
{
}

QString Przedmiot::getNazwa()
{
	return nazwa;
}

short Przedmiot::getWartosc()
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

short Przedmiot::getOgraniczenia()
{
	return ograniczenia;
}

int Przedmiot::getRodzaj()
{
	return rodzaj;
}
