#include "gracz.h"

Gracz::Gracz(QColor kolor, QString nazwa, Rasa rasa, Klasa klasa)
{
	this->kolor = kolor;
	this->nazwa = nazwa;
	this->rasa = rasa;
	this->klasa = klasa;

	this->ekwipunek = new Ekwipunek();

	this->poziom = POCZATKOWY_POZIOM;
	this->zloto = POCZATKOWE_ZLOTO;
	this->doswiadczenie = POCZATKOWE_DOSWIADCZENIE;
	for(int i = 0; i < LICZBA_KROLESTW; ++i)
		this->reputacja[i] = POCZATKOWA_REPUTACJA;
/*
	switch (klasa) {
	case wojownik:
		przepiszStaty(statyWojownik);
		break;
	case mag:
		przepiszStaty(statyMag);
		break;
	case lucznik:
		przepiszStaty(statyLucznik);
		break;
	case druid:
		przepiszStaty(statyDruid);
		break;
	default:
		qDebug() <<"Nie rozpoznano klasy przy ustalaniu pozycji";
		break;
	}
*/
/*
	switch (rasa) {
	case czlowiek:
		this->pozycja = POCZATEK_CZLOWIEK;
		break;
	case elf:
		this->pozycja = POCZATEK_ELF;
		break;
	case krasnolud:
		this->pozycja = POCZATEK_KRASNOLUD;
		break;
	case niziolek:
		this->pozycja = POCZATEK_NIZIOLEK;
		break;
	default:
		qDebug() <<"Nie rozpoznano rasy przy ustalaniu pozycji";
		break;
	}
*/
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
	this->punktyRuchu = konkret.punktyRuchu;
}
