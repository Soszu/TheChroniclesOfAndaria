#ifndef GRA_H
#define GRA_H
#include <QString>
#include <QColor>

const int MAX_GRACZY = 8;
const int MIN_GRACZY = 2;

const quint8 LICZBA_KROLESTW = 4;
const quint8 LICZBA_RAS = 4;
const quint8 LICZBA_KLAS = 4;

const QString KROLESTWA[] = {
	QString::fromUtf8("Ludzie"),
	"Elfy",
	"Krasnoludy",
	QString::fromUtf8("Niziołki")
};

/*
enum Krolestwo
{
	RPA,
	ZSRR,
	Kanada,
	Urugwaj
};
*/

const QString RASY[] = {
	QString::fromUtf8("Człowiek"),
	"Elf",
	"Krasnolud",
	QString::fromUtf8("Niziołek")
};
//wymagana jest odpowiedniość w kolejności pomiędzy powyższym, a poniższym
enum Rasa
{
	czlowiek =0,
	elf = 1,
	krasnolud = 2,
	niziolek = 3
};

const QString KLASY[] = {
	"Wojownik",
	"Mag",
	QString::fromUtf8("Łucznik"),
	"Druid"
};
//wymagana jest odpowiedniość w kolejności pomiędzy powyższym, a poniższym
enum Klasa
{
	wojownik = 0,
	mag = 1,
	lucznik = 2,
	druid = 3
};

const quint8 LICZBA_MOZLIWYCH_KOLOROW = 9;
const QString MOZLIWE_KOLORY[] = {
	"Zielony",
	"Czerwony",
	QString::fromUtf8("Żółty"),
	"Niebieski",
	"Czarny",
	QString::fromUtf8("Biały"),
	QString::fromUtf8("Błękitny"),
	"Fioletowy",
	"Szary"
};

const QColor KOLORY[]= {
	Qt::green,
	Qt::red,
	Qt::yellow,
	Qt::blue,
	Qt::black,
	Qt::white,
	Qt::cyan,
	Qt::magenta,
	Qt::gray
};


const quint16 MAKSYMALNY_POZIOM = 10;
const quint16 GRANICE_POZIOMOW[]={0, 500, 1100, 1800, 2600, 3500, 4500, 5600, 6800, 8100};
const quint8 POCZATKOWY_POZIOM = 1;
const quint8 POCZATKOWA_REPUTACJA = 0;
const quint8 MAX_REPUTACJA = 5;
const quint8 POCZATKOWE_ZLOTO = 10;
const quint8 POCZATKOWE_DOSWIADCZENIE = 0;
const quint8 POCZATKOWE_PUNKTY_RUCHU = 10;

const quint8 POCZATKOWA_ILOSC_MALYCH_POTOW = 2;
const quint8 POCZATKOWE_ILOSC_DUZYCH_POTOW = 1;

struct IDPola
{
	//wstępnie
	int x;
	int y;
};

//IDPola POCZATKOWE_USTAWIENIE[] = {

//}
/*
IDPola POCZATEK_CZLOWIEK =	{2,2};
IDPola POCZATEK_ELF =		{4,4};
IDPola POCZATEK_KRASNOLUD =	{1,5};
IDPola POCZATEK_NIZIOLEK =	{5,7};
*/
struct statystyka
{
	quint8 zdrowieMaks;
	quint8 regeneracja;
	quint8 atakWrecz;
	quint8 atakDystansowy;
	quint8 atakMagiczny;
	quint8 obrona;
	quint8 percepcja;
};
/*
statystyka statyWojownik =	{1, 2, 3, 4, 5, 6, 7};
statystyka statyMag =		{1, 2, 3, 4, 5, 6, 7};
statystyka statyLucznik =	{1, 2, 3, 4, 5, 6, 7};
statystyka statyDruid =		{1, 2, 3, 4, 5, 6, 7};
*/

enum RodzajPrzedmiotu
{
	helm,
	zbrojaLekka,
	zbrojaCiezka,
	bronJednoreczna,
	bronDwureczna,
	tarcza,
	artefakt
};

#endif // GRA_H
