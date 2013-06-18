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
	ostatnioWalczyl = false;
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

QList<Zadanie> *Gracz::getZadania()
{
	return &zadania;
}

Zadanie *Gracz::getKonkretneZadanie(int indeks)
{
	return &zadania[indeks];
}

void Gracz::usunZadanie(int id)
{
	int i = 0;
	while (i < zadania.size() && zadania[i].getId() != id)
		++i;
	if(i != zadania.size())
		zadania.removeAt(i);
}

QList<IDPola> Gracz::getPolaSzczegolne()
{
	return polaSzczegolne;
}

quint8 Gracz::getPoziom()
{
	return poziom;
}

void Gracz::setPoziom(quint8 poziom)
{
	this->poziom = poziom;
}

quint8 *Gracz::getReputacja()
{
	return reputacja;
}

void Gracz::setKonkretnaReputacja(int wartosc, int indeks)
{
	reputacja[indeks] = wartosc;
}

quint8 Gracz::getZdrowieMaks()
{
	return zdrowieMaks;
}

void Gracz::setZdrowieMaks(quint8 wartosc)
{
	zdrowieMaks = wartosc;
}

quint8 Gracz::getZdrowieAktualne()
{
	return zdrowieAktualne;
}

void Gracz::setZdrowieAktualne(quint8 zdrowie)
{
	zdrowieAktualne = zdrowie;
}

quint8 Gracz::getRegeneracja()
{
	return regeneracja;
}

void Gracz::setRegeneracja(quint8 wartosc)
{
	regeneracja = wartosc;
}

quint8 Gracz::getAtakWrecz()
{
	return atakWrecz;
}

void Gracz::setAtakWrecz(quint8 wartosc)
{
	atakWrecz = wartosc;
}

quint8 Gracz::getAtakDystansowy()
{
	return atakDystansowy;
}

void Gracz::setAtakDystansowy(quint8 wartosc)
{
	atakDystansowy = wartosc;
}

quint8 Gracz::getAtakMagiczny()
{
	return atakMagiczny;
}

void Gracz::setAtakMagiczny(quint8 wartosc)
{
	atakMagiczny = wartosc;
}

quint8 Gracz::getObrona()
{
	return obrona;
}

void Gracz::setObrona(quint8 wartosc)
{
	obrona = wartosc;
}

quint8 Gracz::getPercepcja()
{
	return percepcja;
}

void Gracz::setPercepcja(quint8 wartosc)
{
	percepcja = wartosc;
}

quint8 Gracz::getPunktyRuchu()
{
	return punktyRuchu;
}

void Gracz::setPunktyRuchu(quint8 wartosc)
{
	punktyRuchu = wartosc;
}

quint16 Gracz::getZloto()
{
	return zloto;
}

void Gracz::setZloto(quint16 wartosc)
{
	zloto = wartosc;
}

quint16 Gracz::getDoswiadczenie()
{
	return doswiadczenie;
}

void Gracz::setDoswiadczenie(quint16 wartosc)
{
	doswiadczenie = wartosc;
}

bool Gracz::getOstatnioWalczyl()
{
	return ostatnioWalczyl;
}

void Gracz::setOstatnioWalczyl(bool wartosc)
{
	ostatnioWalczyl = wartosc;
}

/**
 * @brief Gracz::przepiszStaty Przepisuje statystyki zebrane w jedym miejscu.
 * @param konkret konkretne wartości do przepisania. Zdefiniowane w gra.h
 */
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
