#ifndef MISTRZGRY_H
#define MISTRZGRY_H

#include <QList>
#include <QString>
#include <QMap>
#include "cyklgry.h"
#include "sztucznainteligencja.h"
#include "gracz.h"
#include "przeciwnik.h"
#include "nagroda.h"
#include "przedmiot.h"
#include "zadanie.h"
#include "plansza.h"
#include "parserprzeciwnikow.h"
#include "parserprzedmiotow.h"
#include "parsernagrod.h"
#include "parserzadan.h"
#include "oknogracza.h"
#include "panelakcji.h"
#include "gra.h"
#include "walka.h"
#include "oknobazaru.h"
#include "oknonagrody.h"
#include "oknotawerny.h"
#include "oknouzdrowiciela.h"

class PanelAkcji;
class CyklGry;
class Plansza;
class ParserPrzeciwnikow;
class ParserPrzedmiotow;
class ParserNagrod;
class ParserZadan;
class Walka;
class OknoBazaru;
class OknoNagrody;
class OknoTawerny;
class OknoUzdrowiciela;

class MistrzGry
{
	friend class ParserPrzeciwnikow;
	friend class ParserPrzedmiotow;
	friend class ParserNagrod;
	friend class ParserZadan;
public:
	MistrzGry(CyklGry *cykl);
	~MistrzGry();
	void setPlansza(Plansza* plansza);
	Plansza* getPlansza();
	void setPanelAkcji(PanelAkcji* panel);
	void setOknoGracza(OknoGracza* okno);
	void setGracze(QList<Gracz*>*gracze);
	void setBoty(QMap<int, SztucznaInteligencja*>);

	void rozpocznij();
	void ruszGracza(int indeks);
	void nowyTydzien();
	void wybranoDzialanie(int nazwa);
	void wykonanoRuch();
	void poinformujPlansze();
	void dolosujZadania();
	void koniecWalki(Przeciwnik* przeciwnik, WynikWalki rezultat);
	void przydzielNagrode(Gracz* gracz, Nagroda* nagroda, bool czyKoniecTury);
private:
	static const int PRZESUNIECIE_DZIALAN_PVP = 20;

	CyklGry* cyklGry;
	Plansza* plansza;
	PanelAkcji* panelAkcji;
	OknoGracza* oknoGracza;

	QMap<int, QList<int>* > grupyPrzeciwnikow; //dla każdej grupy reprezentowanej przez poziom trzymane są identyfikatory przeciwnikoe do niej należących
	QMap<int, Przeciwnik*> przeciwnicy; //jako klucz jest zapisywany identyfikator w postaci liczby całkowitej
	QMap<QString, QList <int>* > grupy; //dla każdej grupy trzymane są identyfikatory przedmiotów do niej należących
	QMap<int, Przedmiot*> przedmioty; //dla każdego identyfikatora trzymany jest opis przedmiotu.
	QMap<int, Nagroda*> nagrody;//dla każdego identyfikatora trzymany jest opis nagrody.
	QMap<int, Zadanie*> zadania;//dla każdego identyfikatora trzymany jest opis zadania.

	Gracz* aktualnyGracz;
	QMap<int, SztucznaInteligencja*> boty;
	QList<Gracz*>* gracze;
	QList<int>* miasta;
	QMap<int, QList<Zadanie*>* > zadaniaWMiastach;
	QMap<int, QList<Przedmiot*>* > towaryWMiastach;
	QList<QPair<int, QString> > mozliweDzialania;
	Zadanie* realizowaneZadanie;

	void ustalMozliweDzialania();
	void wykonajAkcje(int opcja);
	void wykonajZadanie(int id);
	void walka(int opcja);
	Nagroda* polaczNagrody(Nagroda* pierwsza, Nagroda* druga);
	Przeciwnik* losujPrzeciwnika(int grupa);
	void wylosujZadaniaDoTawerny(QList<Zadanie*>* lista, int frakcja, bool usunPoprzednie);
	void wylosujPrzedmiotyNaBazar(QList<Przedmiot*>* lista);

	Walka* oknoWalki;
	OknoNagrody* oknoNagrody;
	OknoTawerny* oknoTawerny;
	OknoBazaru* oknoBazaru;
	OknoUzdrowiciela* oknoUzdrowiciela;
};

#endif // MISTRZGRY_H
