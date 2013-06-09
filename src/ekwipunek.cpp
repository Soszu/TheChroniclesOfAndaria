#include "ekwipunek.h"

Ekwipunek::Ekwipunek()
{
	this->glowa = NULL;
	this->tulw = NULL;
	this->lewaReka = NULL;
	this->prawaReka= NULL;

	this->malePoty = POCZATKOWA_ILOSC_MALYCH_POTOW;
	this->duzePoty = POCZATKOWE_ILOSC_DUZYCH_POTOW;
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
