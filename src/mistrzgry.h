#ifndef MISTRZGRY_H
#define MISTRZGRY_H

#include <QList>
#include <QString>
#include <QMap>
#include "cyklgry.h"
#include "gracz.h"
#include "przeciwnik.h"
#include "plansza.h"
#include "parserprzeciwnikow.h"
#include "parserprzedmiotow.h"
#include "oknogracza.h"
#include "panelakcji.h"
#include "gra.h"

class PanelAkcji;
class CyklGry;
class Plansza;
class ParserPrzeciwnikow;
class ParserPrzedmiotow;

class MistrzGry
{
	friend class ParserPrzeciwnikow;
	friend class ParserPrzedmiotow;
public:
	MistrzGry();
	void ruszGracza(Gracz* gracz);
	QList<Akcja> mozliweAkcje(Gracz* gracz);
	void setCyklGry(CyklGry* cykl);
	void setPlansza(Plansza* plansza);
	void setPanelAkcji(PanelAkcji* panel);
	void setOknoGracza(OknoGracza* okno);
	void wybranoAkcje(Akcja nazwa);
	void wykonanoRuch();
private:
	QMap<int, Przeciwnik*> przeciwnicy; //jako klucz jest zapisywany identyfikator w postaci liczby całkowitej
	Gracz* aktualnyGracz;
	CyklGry* cyklGry;
	PanelAkcji* panelAkcji;
	OknoGracza* oknoGracza;
	Plansza* plansza;

	Nagroda* podajNagrode(int id);
};

#endif // MISTRZGRY_H
