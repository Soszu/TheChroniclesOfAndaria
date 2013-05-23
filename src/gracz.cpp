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
