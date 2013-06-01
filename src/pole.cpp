#include "pole.h"

Pole::Pole(
		IDPola miejsce,
		QString nazwa,
		quint8 wspolczynnik,
		bool czyPoleZPrzeciwnikiem,
		bool czyPoleZMiastem,
		QString plikZObrazkiem)
{
	this->miejsce = miejsce;
	this->nazwa = nazwa;
	this->wspolczynnik = wspolczynnik;
	this->czyPoleZPrzeciwnikiem = czyPoleZPrzeciwnikiem;
	this->czyPoleZMiastem = czyPoleZMiastem;
	this->plikZObrazkiem = plikZObrazkiem;
}

IDPola Pole::getMiejsce()
{
	return miejsce;
}

QString Pole::getNazwa()
{
	return nazwa;
}

quint8 Pole::getWspolczynnik()
{
	return wspolczynnik;
}

bool Pole::getCzyPoleZPrzeciwnikiem()
{
	return czyPoleZPrzeciwnikiem;
}

bool Pole::getCzyPoleZMiastem()
{
	return czyPoleZMiastem;
}

QString Pole::getPlikZObrazkiem()
{
	return plikZObrazkiem;
}
