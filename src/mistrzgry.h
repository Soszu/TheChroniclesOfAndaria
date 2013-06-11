#ifndef MISTRZGRY_H
#define MISTRZGRY_H

#include <QList>
#include <QString>
#include <QMap>
#include "cyklgry.h"
#include "gracz.h"
#include "przeciwnik.h"
#include "nagroda.h"
#include "przedmiot.h"
#include "plansza.h"
#include "parserprzeciwnikow.h"
#include "parserprzedmiotow.h"
#include "parsernagrod.h"
#include "oknogracza.h"
#include "panelakcji.h"
#include "gra.h"
#include "walka.h"
#include "oknobazaru.h"

class PanelAkcji;
class CyklGry;
class Plansza;
class ParserPrzeciwnikow;
class ParserPrzedmiotow;
class ParserNagrod;
class Walka;
class OknoBazaru;

class MistrzGry
{
	friend class ParserPrzeciwnikow;
	friend class ParserPrzedmiotow;
	friend class ParserNagrod;
public:
	MistrzGry(CyklGry *cykl);
	~MistrzGry();
	void ruszGracza(Gracz* gracz);
	QList<Akcja> mozliweAkcje(Gracz* gracz);
	void setPlansza(Plansza* plansza);
	void setPanelAkcji(PanelAkcji* panel);
	void setOknoGracza(OknoGracza* okno);
	void wybranoAkcje(Akcja nazwa);
	void wykonanoRuch();
	void koniecWalki(Przeciwnik* przeciwnik, WynikWalki rezultat);
	void przydzielNagrode(Gracz* gracz, Nagroda* nagroda);
	void rozdzielPunkty(Gracz* gracz);
private:
	QMap<int, QList<int>* > grupyPrzeciwnikow; //dla każdej grupy reprezentowanej przez poziom trzymane są identyfikatory przeciwnikoe do niej należących
	QMap<int, Przeciwnik*> przeciwnicy; //jako klucz jest zapisywany identyfikator w postaci liczby całkowitej
	QMap<QString, QList <int>* > grupy; //dla każdej grupy trzymane są identyfikatory przedmiotów do niej należących
	QMap<int, Przedmiot*> przedmioty; //dla każdego identyfikatora trzymany jest opis przedmiotu.
	QMap<int, Nagroda*> nagrody;//dla każdego identyfikatora trzymany jest opis nagrody.
	Gracz* aktualnyGracz;
	CyklGry* cyklGry;
	PanelAkcji* panelAkcji;
	OknoGracza* oknoGracza;
	Plansza* plansza;

	Przeciwnik* losujPrzeciwnika(int grupa);
	QList<Przedmiot *> *towaryNaBazarze(IDPola pole);
	void walka(Akcja opcja);
	void handelNaBazarze();
	Walka* oknoWalki;
	OknoBazaru* oknoBazaru;
	QList<Przedmiot*> towaryBazarow;
};

#endif // MISTRZGRY_H
