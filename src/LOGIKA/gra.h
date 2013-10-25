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
//grupy przeciwnikow są numerowane od 1.
static const quint8 LICZBA_GRUP_PRZECIWNIKOW = 5;
static const quint8 LICZBA_DNI_TYGODNIA = 5;

static const uint KOSTKA_GRACZA = 10;

static const quint8 LICZBA_POTRZEBNYCH_REPUTACJI = 2; //ile reputacji trzeba wymaksować, żeby wygrać.
static const quint8 MAKSYMALNY_POZIOM = 10;
static const quint16 GRANICE_POZIOMOW[MAKSYMALNY_POZIOM] = {0, 500, 1100, 1800, 2600, 3500, 4500, 5600, 6800, 8100};
static const quint8 POCZATKOWY_POZIOM = 1;
static const quint8 POZIOM_GRANICZNY = 5;
static const quint8 LICZBA_PUNKTOW_NA_POZIOM = 3;
static const quint8 LICZBA_ATRYBOTOW_DO_AWANSU = 5;
static const quint8 BONUS_DO_HP_PRZY_AWANSIE = 3;
static const quint8 MAX_REPUTACJA = 5;
static const quint8 POCZATKOWA_REPUTACJA = 0;
static const quint8 POCZATKOWE_ZLOTO = 3;
static const quint8 POCZATKOWE_DOSWIADCZENIE = 0;
static const quint8 POCZATKOWE_PUNKTY_RUCHU = 8;
static const quint8 ODZYSKANE_ZDROWIE_ZA_SZTUKE_ZLOTA = 4;

static const quint8 LICZBA_PRZEDMIOTOW_NA_BAZARZE = 6;
static const quint8 LICZBA_ZADAN_W_TAWERNIE = 3;
static const quint8 MAKSYMALNA_LICZBA_ZADAN = 5;
static const quint8 KOSZT_ODRZUCENIA_ZADANIA = 2;

static const quint8 LIMIT_ARTEFAKTOW = 5;
static const quint8 POCZATKOWA_ILOSC_MALYCH_POTOW = 2;
static const quint8 DZIALANIE_MALYCH_POTOW = 3; //TODO: nieco konfliktuje z danymi w pliku przeciwnicy (trzeba dbać o jednolitość)
static const quint8 CENA_MALEJ_MIKSTURY = 1;
static const quint8 POCZATKOWE_ILOSC_DUZYCH_POTOW = 1;
static const quint8 DZIALANIE_DUZYCH_POTOW = 10;
static const quint8 CENA_DUZEJ_MIKSTURY = 3;

static const int CZAS_TRWANIA_JEDNEGO_PRZEJSCIA = 500; //w milisekundach
static const int CZAS_TRWANIA_PODSWIETLENIA = 1500; //w milisekundach
static const int DLUGOSC_TRWANIA_KOMUNIKATU = 4000; //w milisekundach
static const qreal ZMIANA_WIELKOSCI_PLANSZY = 5;
static const qreal POCZATKOWY_ROZMIAR_HEXA = 20;
static const qreal MAKSYMALNY_ROZMIAR_HEXA = 80;
static const qreal MINIMALNY_ROZMIAR_HEXA = 10;

static const QString PLIK_PRZEDMIOTOW = "data/przedmioty.txt";
static const QString PLIK_PRZECIWNIKOW = "data/przeciwnicy.txt";
static const QString PLIK_NAGROD = "data/nagrody.txt";
static const QString PLIK_ZADAN = "data/zadania.txt";
static const QString PLIK_USTAWIENIA_PLANSZY = "data/plansza.txt";

static const QString IKONKA_WRECZ = "img/ikonki/wrecz.png";
static const QString IKONKA_DYSTANSOWY = "img/ikonki/dystans.png";
static const QString IKONKA_MAGICZNY = "img/ikonki/magia.png";
static const QString IKONKA_OBRONA = "img/ikonki/obrona.png";
static const QString IKONKA_ATAK = "img/ikonki/wrecz.png";
static const QString IKONKA_PERCEPCJA = "img/ikonki/percepcja.png";
static const QString IKONKA_RUCH = "img/ikonki/ruch.png";
static const QString IKONKA_MALA_MIKSTURA_ZDROWIA = "img/ikonki/mala_mikstura.png";
static const QString IKONKA_DUZA_MIKSTURA_ZDROWIA = "img/ikonki/duza_mikstura.png";
static const QString IKONKA_ZLOTO = "img/ikonki/zloto.png";
static const QString IKONKA_REGENERACJA = "img/ikonki/regeneracja.png";

static const QString PREFIX_PRZECIWNIKOW = "przeciwnicy/";
static const QString PREFIX_HEXOW = "img/hexy/";
static const QString PLIK_Z_SYMBOLEM_WALKI = "img/hexy/symbol.png";

static const QString KROLESTWA[LICZBA_KROLESTW] = {
	QString::fromUtf8("Ludzie"),
	"Krasnoludy",
	"Elfy",
	QString::fromUtf8("Niziołki")
};

//index nazwy rasy jest równoznaczny z wartością enumeratora Rasa, dla tej rasy
static const QString RASY[LICZBA_RAS] = {
	QString::fromUtf8("Człowiek"),
	"Krasnolud",
	"Elf",
	QString::fromUtf8("Niziołek")
};

enum Rasa
{
	czlowiek = 0,
	krasnolud = 1,
	elf = 2,
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
	{14,18}, //krasnolud
	{28,8}, //elf
	{2,8}  //niziołek
};

struct statystyka
{
	int zdrowieMaks;
	int regeneracja;
	int atakWrecz;
	int atakDystansowy;
	int atakMagiczny;
	int obrona;
	int percepcja;
};

static const statystyka POCZATKOWE_STATYSTYKI[LICZBA_RAS][LICZBA_KLAS] = {
	{{15,2,10,3,1,10,1},	//Człowiek wojownik:
	{13,3,5,9,1,8,7},	//Człowiek łowca
	{11,3,2,1,11,7,4},	//Człowiek mag
	{13,5,2,2,8,10,3}},	//Człowiek druid:

	{{15,2,10,5,1,10,1},	//Krasnolud wojownik
	{13,3,5,9,1,8,7},	//Krasnolud łowca
	{11,3,2,1,11,7,4},	//Krasnolud mag
	{13,5,2,2,8,9,3}},	//Krasnolud druid

	{{15,2,10,5,1,10,1},	//Elf wojownik
	{13,3,5,9,1,8,7},	//Elf łowca
	{11,3,2,1,11,7,4},	//Elf mag
	{13,5,2,2,8,9,3}},	//Elf druid

	{{15,2,10,5,1,10,1},	//Niziołek wojownik
	{13,3,5,9,1,8,7},	//Niziołek łowca
	{11,3,2,1,11,7,4},	//Niziołek mag
	{13,5,2,2,8,9,3}}	//Niziołek druid
};

static const quint8 LICZBA_RODZAJOW_PRZEDMIOTOW = 7;

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

static const QString RODZAJE_PRZEDMIOTOW[LICZBA_RODZAJOW_PRZEDMIOTOW] = {
	QString::fromUtf8("broń dwuręczna"),
	QString::fromUtf8("broń jednoręczna"),
	QString::fromUtf8("tarcza"),
	QString::fromUtf8("pancerz"),
	QString::fromUtf8("hełm"),
	QString::fromUtf8("artefakt"),
	QString::fromUtf8("mikstura"),
};

static const quint8 LICZBA_MOZLIWYCH_KOLOROW = 9;
static const QString MOZLIWE_KOLORY[LICZBA_MOZLIWYCH_KOLOROW] = {
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

static const QColor KOLORY[LICZBA_MOZLIWYCH_KOLOROW]= {
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
	koniecTury,
	przeciwnikLatwy,
	przeciwnikTrudny,
	bazar,
	tawerna,
	przeciwnikZZadania,
	uzdrowiciel
};

//index nazwy akcji jest równoznaczny z wartością enumeratora Akcja, dla tej akcji
static const QString AKCJE[] = {
	QString::fromUtf8("Zakończ turę"),
	QString::fromUtf8("Walcz ze zwyczajnym przeciwnikiem "),
	QString::fromUtf8("Walcz z wymagającym przeciwnikiem"),
	QString::fromUtf8("Idź na bazar handlować ekwipunkiem"),
	QString::fromUtf8("Idź do tawerny \nposzukać nowych zadań"),
	QString::fromUtf8("Walcz z przeciwnikiem z zadania"),
	QString::fromUtf8("Idź do uzdrowiciela")
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
};

//modyfikatory służące do przesuwania pionków jeśli kilka stoi na tym samym polu
struct modyfikator{
	int x;
	int y;
};
static const int LICZBA_PRZEWIDZIANYCH_MODYFIKATOROW = 9;
static const modyfikator MODYFIKATORY_POZYCJI[LICZBA_PRZEWIDZIANYCH_MODYFIKATOROW]= {
	{0,0}, {0, -1}, {-1, 1}, {1, 1}, {-1, -1}, {1, -1}, {0, 1}, {-1, 0}, {1, 0} };

static const int LICZBA_RODZAJOW_ZADAN = 3;
static const int BAZOWA_SZANSA_NA_ODNALEZIENIE = 50; // w procentach
static const int BONUS_Z_PERCEPCJI = 5; // w procentach
enum RodzajZadania
{
	pokonaj = 1,
	przynies = 2, //realizuje też "dotrzyj na miejsce" jeśli czyPowrótWymagany == false
	odnajdz = 3
};

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
#endif // GRA_H
