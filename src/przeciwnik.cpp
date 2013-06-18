#include "przeciwnik.h"

Przeciwnik::Przeciwnik(QString nazwa, QString nazwaObrazka, quint8 atakMinimalny, quint8 atakMaksymalny, quint8 obrona, quint8 percepcja, quint8 zdrowieMaks, Nagroda *nagroda)
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

quint8 Przeciwnik::getAtakMinimalny()
{
	return atakMinimalny;
}

quint8 Przeciwnik::getAtakMaksymalny()
{
	return atakMaksymalny;
}

quint8 Przeciwnik::getObrona()
{
	return obrona;
}

quint8 Przeciwnik::getPercepcja()
{
	return percepcja;
}

quint8 Przeciwnik::getZdrowieMaks()
{
	return zdrowieMaks;
}

Nagroda *Przeciwnik::getNagroda()
{
	return nagroda;
}
