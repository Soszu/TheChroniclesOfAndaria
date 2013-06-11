#include "ekwipunek.h"

Ekwipunek::Ekwipunek()
{
	this->glowa = NULL;
	this->tuluw = NULL;
	this->lewaReka = NULL;
	this->prawaReka= NULL;

	this->plecak = new QList<Przedmiot*>();

	this->malePoty = POCZATKOWA_ILOSC_MALYCH_POTOW;
	this->duzePoty = POCZATKOWE_ILOSC_DUZYCH_POTOW;
}

Ekwipunek::~Ekwipunek()
{
	delete plecak;
}

Przedmiot *Ekwipunek::getGlowa()
{
	return glowa;
}

void Ekwipunek::setGlowa(Przedmiot *rzecz)
{
	glowa = rzecz;
}

Przedmiot *Ekwipunek::getTuluw()
{
	return tuluw;
}

void Ekwipunek::setTuluw(Przedmiot *rzecz)
{
	tuluw = rzecz;
}

Przedmiot *Ekwipunek::getLewaReka()
{
	return lewaReka;
}

void Ekwipunek::setLewaReka(Przedmiot *rzecz)
{
	lewaReka = rzecz;
}

Przedmiot *Ekwipunek::getPrawaReka()
{
	return prawaReka;
}

void Ekwipunek::setPrawaReka(Przedmiot *rzecz)
{
	prawaReka = rzecz;
}

quint8 Ekwipunek::getMalePoty()
{
	return malePoty;
}

quint8 Ekwipunek::getDuzePoty()
{
	return duzePoty;
}

void Ekwipunek::setMalePoty(quint8 ilosc)
{
	if(ilosc >=0)
		malePoty = ilosc;
}

void Ekwipunek::setDuzePoty(quint8 ilosc)
{
	if(ilosc >=0)
		duzePoty = ilosc;
}

QList<Przedmiot *> *Ekwipunek::getPlecak()
{
	return plecak;
}

QList<Przedmiot *> *Ekwipunek::getZalozoneArtefakty()
{
	return &zalozoneArtefakty;
}
