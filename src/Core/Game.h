#pragma once

#include <QString>

static const quint8 DaysPerWeek = 5;

static const uint PlayerDice = 10;

static const quint8 MaximumReputationsToWin = 2; //ile reputacji trzeba wymaksować, żeby wygrać.
static const quint8 MaximumLevel = 10;
static const quint16 GRANICE_POZIOMOW[MaximumLevel] = {0, 500, 1100, 1800, 2600, 3500, 4500, 5600, 6800, 8100};

static const quint8 AttributePointsPerLevel = 3; //TODO CFiend nie jestem pewien czy to wlasciwe tlumaczenie
static const quint8 LICZBA_ATRYBOTOW_DO_AWANSU = 5;
static const quint8 HealthIncreasePerLevel = 3;
static const quint8 MaximumReputation = 5;
static const quint8 HealingPerGoldPiece = 4;

static const quint8 ItemCountInMarket = 6;
static const quint8 QuestsInTavernCount = 3;
static const quint8 MaximumNumberOfQuestsTaken = 5;
static const quint8 QuestDeclineCost = 2;

static const quint8 DZIALANIE_MALYCH_POTOW = 3; //TODO: nieco konfliktuje z danymi w pliku przeciwnicy (trzeba dbać o jednolitość)
static const quint8 CENA_MALEJ_MIKSTURY = 1;
static const quint8 DZIALANIE_DUZYCH_POTOW = 10;
static const quint8 CENA_DUZEJ_MIKSTURY = 3;

static const int CZAS_TRWANIA_JEDNEGO_PRZEJSCIA = 500; //w milisekundach
static const int CZAS_TRWANIA_PODSWIETLENIA = 1500; //w milisekundach
static const int DLUGOSC_TRWANIA_KOMUNIKATU = 4000; //w milisekundach
static const qreal ZMIANA_WIELKOSCI_PLANSZY = 5;
static const qreal InitialTileSize = 20;
static const qreal MAKSYMALNY_ROZMIAR_HEXA = 80;
static const qreal MINIMALNY_ROZMIAR_HEXA = 10;

//TODO CFiend porzadek musi byc, enum class i te sprawy

static const quint8 KingdomCount = 4;

static const QString KingdomString[KingdomCount] = {
	QString::fromUtf8("Ludzie"),
	"Krasnoludy",
	"Elfy",
	QString::fromUtf8("Niziołki")
};

enum atrybut
{
	Awrecz,
	Adystansowy,
	Amagiczny,
	defence,
	perception,
	zdrowie
};

//index nazwy mozliwych atrybutow do awansu jest równoznaczny z wartością enumeratora atrybut
static const QString MOZLIWE_AWANSE[] = {
	QString::fromUtf8("Atak wręcz"),
	"Atak dystansowy",
	"Atak magiczny",
	"Obrona",
	"Percepcja",
};

static const int LICZBA_POZIOMOW_ZADAN = 3;
static const int LICZBA_RODZAJOW_ZADAN = 3;
static const int BAZOWA_SZANSA_NA_ODNALEZIENIE = 50; // w procentach
static const int BONUS_Z_PERCEPCJI = 5; // w procentach

enum Blad
{
	blad_parsera_przedmiotow= 11,
	blad_parsera_nagrod = 12,
	blad_parsera_przeciwnikow = 13,
	blad_liczby_grup_przeciwnikow = 131,
	blad_parsera_zadan = 14,
	blad_liczby_zadan = 141,
	blad_parsera_ustawienia_planszy = 21
};
