#ifndef GRA_H
#define GRA_H

const quint8 LICZBA_KROLESTW = 3;

const quint8 POCZATKOWY_POZIOM = 1;
const quint8 POCZATKOWA_REPUTACJA = 0;
const quint8 POCZATKOWE_ZLOTO = 10;
const quint8 POCZATKOWE_DOSWIADCZENIE = 0;

const quint8 POCZATKOWA_ILOSC_MALYCH_POTOW = 2;
const quint8 POCZATKOWE_ILOSC_DUZYCH_POTOW = 1;

struct IDPola
{
	//wstępnie
	int x;
	int y;
};

struct statystyka
{
	quint8 zdrowieMaks;
	quint8 regeneracja;
	quint8 atakWrecz;
	quint8 atakDystansowy;
	quint8 atakMagiczny;
	quint8 obrona;
	quint8 percepcja;
	quint8 punktyRuchu;
};
/*
statystyka statyWojownik =	{1, 2, 3, 4, 5, 6, 7, 8};
statystyka statyMag =		{1, 2, 3, 4, 5, 6, 7, 8};
statystyka statyLucznik =	{1, 2, 3, 4, 5, 6, 7, 8};
statystyka statyDruid =		{1, 2, 3, 4, 5, 6, 7, 8};
*/
enum Krolestwo
{
	RPA,
	ZSRR,
	Kanada
};

enum Rasa
{
	czlowiek,
	elf,
	krasnolud,
	niziolek
};

enum Klasa
{
	wojownik,
	mag,
	lucznik,
	druid
};

enum RodzajPrzedmiotu
{
	helm,
	zbrojaLekka,
	zbrojaCiezka,
	bronJednoreczna,
	bronDwureczna,
	tarcza
};

#endif // GRA_H
