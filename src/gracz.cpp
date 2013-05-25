#include "gracz.h"

Gracz::Gracz(QString nazwa, Rasa rasa, Klasa klasa, QColor kolor, bool czyAI)
{
	this->kolor = kolor;
	this->nazwa = nazwa;
	this->rasa = rasa;
	this->klasa = klasa;
	this->czyAI = czyAI;
	this->pozycja = POCZATKOWE_USTAWIENIE[this->rasa];
	przepiszStaty(POCZATKOWE_STATYSTYKI[this->rasa][this->klasa]);
	this->ekwipunek = new Ekwipunek();

	this->poziom = POCZATKOWY_POZIOM;
	this->zloto = POCZATKOWE_ZLOTO;
	this->doswiadczenie = POCZATKOWE_DOSWIADCZENIE;
	this->punktyRuchu = POCZATKOWE_PUNKTY_RUCHU;
	for(int i = 0; i < LICZBA_KROLESTW; ++i)
		this->reputacja[i] = POCZATKOWA_REPUTACJA;

	this->zdrowieAktualne = this->zdrowieMaks;
}

Gracz::~Gracz()
{
	delete ekwipunek;
}

QString Gracz::getNazwa()
{
	return nazwa;
}

Rasa Gracz::getRasa()
{
	return rasa;
}

Klasa Gracz::getKlasa()
{
	return klasa;
}

QColor Gracz::getKolor()
{
	return kolor;
}

bool Gracz::getCzyAI()
{
	return czyAI;
}

IDPola Gracz::getPozycja()
{
	return pozycja;
}

void Gracz::setPozycja(IDPola id)
{
	this->pozycja = id;
}

Ekwipunek *Gracz::getEkwipunek()
{
	return ekwipunek;
}

QList<Zadanie *> Gracz::getZadania()
{
	return zadania;
}

QList<IDPola> Gracz::getPolaSzczegolne()
{
	return polaSzczegolne;
}

quint8 Gracz::getPoziom()
{
	return poziom;
}

quint8 *Gracz::getReputacja()
{
	return reputacja;
}

quint8 Gracz::getZdrowieMaks()
{
	return zdrowieMaks;
}

quint8 Gracz::getZdrowieAktualne()
{
	return zdrowieAktualne;
}

quint8 Gracz::getRegeneracja()
{
	return regeneracja;
}

quint8 Gracz::getAtakWrecz()
{
	return atakWrecz;
}

quint8 Gracz::getAtakDystansowy()
{
	return atakDystansowy;
}

quint8 Gracz::getAtakMagiczny()
{
	return atakMagiczny;
}

quint8 Gracz::getObrona()
{
	return obrona;
}

quint8 Gracz::getPercepcja()
{
	return percepcja;
}

quint8 Gracz::getPunktyRuchu()
{
	return punktyRuchu;
}

quint16 Gracz::getZloto()
{
	return zloto;
}

quint16 Gracz::getDoswiadczenie()
{
	return doswiadczenie;
}

void Gracz::przepiszStaty(statystyka konkret)
{
	this->zdrowieMaks = konkret.zdrowieMaks;
	this->regeneracja = konkret.regeneracja;
	this->atakWrecz = konkret.atakWrecz;
	this->atakDystansowy = konkret.atakDystansowy;
	this->atakMagiczny = konkret.atakMagiczny;
	this->obrona = konkret.obrona;
	this->percepcja = konkret.percepcja;
}
