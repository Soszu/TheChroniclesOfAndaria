#include "nagroda.h"

Nagroda::Nagroda(quint8 reputacja[], quint16 zloto, quint16 doswiadczenie, quint8 ileLosowych, QList<Przedmiot *> konkrety)
{
	this->doswiadczenie = doswiadczenie;
//FIX	this->reputacja = reputacja;
	this->zloto = zloto;
	this->ileLosowych = ileLosowych;
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

quint8 Nagroda::getIleLosowych()
{
	return ileLosowych;
}

QList<Przedmiot *>* Nagroda::getKonkretnePrzedmioty()
{
	return &konkretnePrzedmioty;
}
