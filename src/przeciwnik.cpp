#include "przeciwnik.h"

Przeciwnik::Przeciwnik(QString nazwa, QString nazwaObrazka, QString opis, quint8 atakMinimalny, quint8 atakMaksymalny, quint8 obrona, quint8 zdrowieMaks, Nagroda *nagroda)
{
	this->nazwa = nazwa;
	this->nazwaObrazka = nazwaObrazka;
	this->opis = opis;
	this->atakMaksymalny = atakMaksymalny;
	this->atakMinimalny = atakMinimalny;
	this->obrona = obrona;
	this->zdrowieMaks = zdrowieMaks;
	this->zdrowieAktualne = zdrowieAktualne;
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

QString Przeciwnik::getOpis()
{
	return opis;
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

quint8 Przeciwnik::getZdrowieMaks()
{
	return zdrowieMaks;
}

quint8 Przeciwnik::getZdrowieAktualne()
{
	return zdrowieAktualne;
}

Nagroda *Przeciwnik::getNagroda()
{
	return nagroda;
}
