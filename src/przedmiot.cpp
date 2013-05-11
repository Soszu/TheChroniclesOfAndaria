#include "przedmiot.h"

Przedmiot::Przedmiot(string nazwa, short wartosc, string opis, bool czyPo5Lvlu, short ograniczenia, int rodzaj)
{
}

string Przedmiot::getNazwa()
{
	return nazwa;
}

short Przedmiot::getWartosc()
{
	return wartosc;
}

string Przedmiot::getOpis()
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
