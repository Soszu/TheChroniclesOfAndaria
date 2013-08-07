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
	czyAktywny = true;
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

QList<Zadanie*> *Gracz::getZadania()
{
	return &zadania;
}

Zadanie *Gracz::getKonkretneZadanie(int indeks)
{
	return zadania[indeks];
}

void Gracz::usunKonkretneZadanie(int id)
{
	int i = 0;
	while (i < zadania.size() && zadania[i]->getId() != id)
		++i;
	if(i != zadania.size())
	{
		delete zadania[i];
		zadania.removeAt(i);
	}
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

int *Gracz::getReputacja()
{
	return reputacja;
}

void Gracz::setKonkretnaReputacja(int wartosc, int indeks)
{
	reputacja[indeks] = wartosc;
}

int Gracz::getZdrowieMaks()
{
	return zdrowieMaks;
}

void Gracz::setZdrowieMaks(int wartosc)
{
	zdrowieMaks = wartosc;
}

int Gracz::getZdrowieAktualne()
{
	return zdrowieAktualne;
}

void Gracz::setZdrowieAktualne(int zdrowie)
{
	zdrowieAktualne = zdrowie;
}

int Gracz::getRegeneracja()
{
	return regeneracja;
}

void Gracz::setRegeneracja(int wartosc)
{
	regeneracja = wartosc;
}

int Gracz::getAtakWrecz()
{
	return atakWrecz;
}

void Gracz::setAtakWrecz(int wartosc)
{
	atakWrecz = wartosc;
}

int Gracz::getAtakDystansowy()
{
	return atakDystansowy;
}

void Gracz::setAtakDystansowy(int wartosc)
{
	atakDystansowy = wartosc;
}

int Gracz::getAtakMagiczny()
{
	return atakMagiczny;
}

void Gracz::setAtakMagiczny(int wartosc)
{
	atakMagiczny = wartosc;
}

int Gracz::getObrona()
{
	return obrona;
}

void Gracz::setObrona(int wartosc)
{
	obrona = wartosc;
}

int Gracz::getPercepcja()
{
	return percepcja;
}

void Gracz::setPercepcja(int wartosc)
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

void Gracz::setCzyAktywny(bool wartosc)
{
	czyAktywny = wartosc;
}

bool Gracz::getCzyAktywny()
{
	return czyAktywny;
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

