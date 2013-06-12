#ifndef GRA_H
#define GRA_H
#include <QString>
#include <QColor>

static const int MAX_GRACZY = 8;
static const int MIN_GRACZY = 2;
static const quint16 MAKSYMALNA_DLUGOSC_NAZWY = 20; //chodzi o nazwę gracza

static const quint8 LICZBA_KROLESTW = 4;
static const quint8 LICZBA_RAS = 4;
static const quint8 LICZBA_KLAS = 4;
static const quint8 LICZBA_GRUP_PRZECIWNIKOW = 5;

static const quint8 MAKSYMALNY_POZIOM = 10;
static const quint16 GRANICE_POZIOMOW[MAKSYMALNY_POZIOM] = {0, 500, 1100, 1800, 2600, 3500, 4500, 5600, 6800, 8100};
static const quint8 POCZATKOWY_POZIOM = 1;
static const quint8 POZIOM_GRANICZNY = 5;
static const quint8 LICZBA_PUNKTOW_NA_POZIOM = 3;
static const quint8 LICZBA_ATRYBOTOW_DO_AWANSU = 5;
static const quint8 BONUS_DO_HP_PRZY_AWANSIE = 3;
static const quint8 POCZATKOWA_REPUTACJA = 0;
static const quint8 MAX_REPUTACJA = 5;
static const quint8 POCZATKOWE_ZLOTO = 10;
static const quint8 POCZATKOWE_DOSWIADCZENIE = 0;
static const quint8 POCZATKOWE_PUNKTY_RUCHU = 8;

static const quint8 LICZBA_PRZEDMIOTOW_NA_BAZARZE = 4;

static const quint8 POCZATKOWA_ILOSC_MALYCH_POTOW = 2;
static const quint8 DZIALANIE_MALYCH_POTOW = 5; //nieco konfliktuje z danymi w pliku przeciwnicy
static const quint8 CENA_MALEJ_MIKSTURY = 1;
static const quint8 POCZATKOWE_ILOSC_DUZYCH_POTOW = 1;
static const quint8 DZIALANIE_DUZYCH_POTOW = 20;
static const quint8 CENA_DUZEJ_MIKSTURY = 3;

static const int CZAS_TRWANIA_JEDNEGO_PRZEJSCIA = 500; //w milisekundach

static const qreal POCZATKOWY_ROZMIAR_HEXA = 20;
static const qreal MAKSYMALNY_ROZMIAR_HEXA = 80;
static const qreal MINIMALNY_ROZMIAR_HEXA = 10;

static const QString KROLESTWA[LICZBA_KROLESTW] = {
	QString::fromUtf8("Ludzie"),
	"Elfy",
	"Krasnoludy",
	QString::fromUtf8("Niziołki")
};

//index nazwy rasy jest równoznaczny z wartością enumeratora Rasa, dla tej rasy
static const QString RASY[LICZBA_RAS] = {
	QString::fromUtf8("Człowiek"),
	"Elf",
	"Krasnolud",
	QString::fromUtf8("Niziołek")
};

enum Rasa
{
	czlowiek = 0,
	elf = 1,
	krasnolud = 2,
	niziolek = 3
};

//index nazwy klasy jest równoznaczny z wartością enumeratora Klasa, dla tej rasy
static const QString KLASY[LICZBA_KLAS] = {
	"Wojownik",
	QString::fromUtf8("Łowca"),
	"Mag",
	"Druid"
};

enum Klasa
{
	wojownik,
	lowca,
	mag,
	druid
};

struct IDPola
{
	int x;
	int y;
};

//index ustawienia początkowego jest równoznaczna z wartością enumeratora Rasa, dla tej rasy
static const IDPola POCZATKOWE_USTAWIENIE[LICZBA_RAS] = {
	{18,3}, //czlowiek
	{28,8}, //elf
	{14,18}, //krasnolud
	{2,8}  //niziołek
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
};

static const statystyka POCZATKOWE_STATYSTYKI[LICZBA_RAS][LICZBA_KLAS] = {
	{{15,2,10,3,1,10,1},	//Człowiek wojownik:
	{13,3,5,9,1,8,7},	//Człowiek łowca
	{11,3,2,1,11,7,4},	//Człowiek mag
	{13,4,2,2,7,10,3}},	//Człowiek druid:

	{{15,2,10,5,1,10,1},	//Elf wojownik
	{13,3,5,9,1,8,7},	//Elf łowca
	{11,3,2,1,11,7,4},	//Elf mag
	{13,4,2,2,7,9,3}},	//Elf druid

	{{15,2,10,5,1,10,1},	//Krasnolud wojownik
	{13,3,5,9,1,8,7},	//Krasnolud łowca
	{11,3,2,1,11,7,4},	//Krasnolud mag
	{13,4,2,2,7,9,3}},	//Krasnolud druid

	{{15,2,10,5,1,10,1},	//Niziołek wojownik
	{13,3,5,9,1,8,7},	//Niziołek łowca
	{11,3,2,1,11,7,4},	//Niziołek mag
	{13,4,2,2,7,9,3}}	//Niziołek druid
};

static const quint8 LICZBA_RODZAJOW = 7;

enum RodzajPrzedmiotu
{
	bronDwureczna,
	bronJednoreczna,
	tarcza,
	pancerz,
	helm,
	artefakt,
	mikstura
};

static const QString RODZAJE_PRZEDMIOTOW[LICZBA_RODZAJOW] = {
	QString::fromUtf8("broń dwuręczna"),
	QString::fromUtf8("broń jednoręczna"),
	QString::fromUtf8("tarcza"),
	QString::fromUtf8("pancerz"),
	QString::fromUtf8("hełm"),
	QString::fromUtf8("artefakt"),
	QString::fromUtf8("mikstura"),
};

static const quint8 LICZBA_MOZLIWYCH_KOLOROW = 9;
static const QString MOZLIWE_KOLORY[] = {
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

static const QColor KOLORY[]= {
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

enum Akcja
{
	koniecTury = 0,
	przeciwnikLatwy = 1,
	przeciwnikTrudny = 2,
	bazar = 3,
	tawerna = 4
};

//index nazwy akcji jest równoznaczny z wartością enumeratora Akcja, dla tej akcji
static const QString AKCJE[] = {
	QString::fromUtf8("Zakończ turę"),
	QString::fromUtf8("Walcz ze słabszym przeciwnikiem"),
	QString::fromUtf8("Walcz z mocnym przeciwnikiem"),
	QString::fromUtf8("Idź na bazar handlować ekwipunkiem"),
	QString::fromUtf8("Idź do tawerny \nposzukać nowych zadań")
};

enum WynikWalki {
	wygrana,
	przegrana,
	ucieczka
};

enum atrybut
{
	Awrecz,
	Adystansowy,
	Amagiczny,
	obrona,
	percepcja,
	zdrowie
};

//index nazwy mozliwych atrybutow do awansu jest równoznaczny z wartością enumeratora atrybut
static const QString MOZLIWE_AWANSE[] = {
	QString::fromUtf8("Atak wręcz"),
	"Atak dystansowy",
	"Atak magiczny",
	"Obrona",
	"Percepcja",
	"Zdrowie"
};

//modyfikatory służące do przesuwania pionków jeśli kilka stoi na tym samym polu
struct modyfikator{
	int x;
	int y;
};
static const int LICZBA_PRZEWIDZIANYCH_MODYFIKATOROW = 9;
static const modyfikator MODYFIKATORY_POZYCJI[LICZBA_PRZEWIDZIANYCH_MODYFIKATOROW]= {
	{0,0}, {0, -1}, {-1, 1}, {1, 1}, {-1, -1}, {1, -1}, {0, 1}, {-1, 0}, {1, 0} };

enum Blad
{
	blad_parsera_przedmiotow= 11,
	blad_parsera_nagrod = 12,
	blad_parsera_przeciwnikow = 13,
	blad_liczby_grup_przeciwnikow = 131,
	blad_parsera_zadan = 14,
	blad_parsera_ustawienia_planszy = 21
};

#endif // GRA_H
