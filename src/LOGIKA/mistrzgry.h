﻿#ifndef MISTRZGRY_H
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
	void ruszGracza(Gracz* gracz, int indeks);
	void setPlansza(Plansza* plansza);
	Plansza* getPlansza();
	void setPanelAkcji(PanelAkcji* panel);
	void setOknoGracza(OknoGracza* okno);
	void setBoty(QMap<int, SztucznaInteligencja*>);
	void wybranoDzialanie(int nazwa);
	void wykonanoRuch();
	void poinformujPlansze();
	void koniecWalki(Przeciwnik* przeciwnik, WynikWalki rezultat);
	void przydzielNagrode(Gracz* gracz, Nagroda* nagroda, bool czyKoniecTury);
	void wykonajAkcje(Akcja opcja);
	void wykonajZadanie(Gracz *gracz, int id);
	void nowyTydzien();
	void rozpocznij();
private:
	QMap<int, QList<int>* > grupyPrzeciwnikow; //dla każdej grupy reprezentowanej przez poziom trzymane są identyfikatory przeciwnikoe do niej należących
	QMap<int, Przeciwnik*> przeciwnicy; //jako klucz jest zapisywany identyfikator w postaci liczby całkowitej
	QMap<QString, QList <int>* > grupy; //dla każdej grupy trzymane są identyfikatory przedmiotów do niej należących
	QMap<int, Przedmiot*> przedmioty; //dla każdego identyfikatora trzymany jest opis przedmiotu.
	QMap<int, Nagroda*> nagrody;//dla każdego identyfikatora trzymany jest opis nagrody.
	QMap<int, Zadanie*> zadania;//dla każdego identyfikatora trzymany jest opis zadania.

	Gracz* aktualnyGracz;
	CyklGry* cyklGry;
	Plansza* plansza;
	PanelAkcji* panelAkcji;
	OknoGracza* oknoGracza;
	QLabel* dzienTygodnia;
	QMap<int, SztucznaInteligencja*> boty;
	QList<int>* miasta;

	Przeciwnik* losujPrzeciwnika(int grupa);
	void walka(Akcja opcja);
	Walka* oknoWalki;
	OknoNagrody* oknoNagrody;

	void idzDoTawerny();
	void wylosujZadaniaDoTawerny(QList<Zadanie*>* lista, int frakcja);
	OknoTawerny* oknoTawerny;
	QMap<int, QList<Zadanie*>* > zadaniaWMiastach;

	void handelNaBazarze();
	void wylosujPrzedmiotyNaBazar(QList<Przedmiot*>* lista);
	OknoBazaru* oknoBazaru;
	QMap<int, QList<Przedmiot*>* > towaryWMiastach;

	OknoUzdrowiciela* oknoUzdrowiciela;
	void idzDoUzdrowiciela();

	Zadanie* realizowaneZadanie;
	QList<Akcja> mozliweAkcje(Gracz* gracz);
	QList<Zadanie*>mozliweZadania(Gracz* gracz);
	Nagroda* polaczNagrody(Nagroda* pierwsza, Nagroda* druga);
};

#endif // MISTRZGRY_H