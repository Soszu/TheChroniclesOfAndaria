#include "przeciwnik.h"

Przeciwnik::Przeciwnik(QString nazwa, quint8 atak, quint8 obrona, quint8 zdrowieMaks, quint8 zdrowieAktualne, Nagroda *nagroda)
{
	this->nazwa = nazwa;
	this->atak = atak;
	this->obrona = obrona;
	this->zdrowieMaks = zdrowieMaks;
	this->zdrowieAktualne = zdrowieAktualne;
	this->nagroda = nagroda;
}

QString Przeciwnik::getNazwa()
{
	return nazwa;
}

quint8 Przeciwnik::getAtak()
{
	return atak;
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
