#include "nagroda.h"

Nagroda::Nagroda(int reputacja[LICZBA_KROLESTW], quint16 zloto, quint16 doswiadczenie, QStringList nazwyGrup, QList<int> *konkrety)
{
	this->doswiadczenie = doswiadczenie;
	this->reputacja = reputacja;
	this->zloto = zloto;
	this->nazwyGrup = nazwyGrup;
	this->konkretnePrzedmioty = konkrety;
}

Nagroda::~Nagroda()
{
	delete [] reputacja;
	delete konkretnePrzedmioty;
}

int *Nagroda::getReputacja()
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
