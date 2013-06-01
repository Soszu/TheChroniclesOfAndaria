#include "nagroda.h"

Nagroda::Nagroda(quint8 reputacja[LICZBA_KROLESTW], quint16 zloto, quint16 doswiadczenie, QStringList nazwyGrup, QList<int> *konkrety)
{
	this->doswiadczenie = doswiadczenie;
	this->reputacja = reputacja;
	this->zloto = zloto;
	this->nazwyGrup = nazwyGrup;
	this->konkretnePrzedmioty = konkrety;
}

quint8 *Nagroda::getReputacja()
{
	return reputacja;
}

quint16 Nagroda::getZloto()
{
	return zloto;
}

quint16 Nagroda::getDoswiadczenie()
{
	return doswiadczenie;
}

QStringList Nagroda::getNazwyGrup()
{
	return nazwyGrup;
}

QList<int> *Nagroda::getKonkretnePrzedmioty()
{
	return konkretnePrzedmioty;
}
