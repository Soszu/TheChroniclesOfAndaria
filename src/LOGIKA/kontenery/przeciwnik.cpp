#include "przeciwnik.h"

Przeciwnik::Przeciwnik(QString nazwa, QString nazwaObrazka, int atakMinimalny, int atakMaksymalny, int obrona, int percepcja, int zdrowieMaks, Nagroda *nagroda)
{
	this->nazwa = nazwa;
	this->nazwaObrazka = nazwaObrazka;
	this->atakMaksymalny = atakMaksymalny;
	this->atakMinimalny = atakMinimalny;
	this->obrona = obrona;
	this->percepcja = percepcja;
	this->zdrowieMaks = zdrowieMaks;
	this->nagroda = nagroda;
}

QString Przeciwnik::getNazwa()
{
	return nazwa;
}

QString Przeciwnik::getNazwaObrazka()
{
	return nazwaObrazka;
}

int Przeciwnik::getAtakMinimalny()
{
	return atakMinimalny;
}

int Przeciwnik::getAtakMaksymalny()
{
	return atakMaksymalny;
}

int Przeciwnik::getObrona()
{
	return obrona;
}

int Przeciwnik::getPercepcja()
{
	return percepcja;
}

int Przeciwnik::getZdrowieMaks()
{
	return zdrowieMaks;
}

Nagroda *Przeciwnik::getNagroda()
{
	return nagroda;
}
