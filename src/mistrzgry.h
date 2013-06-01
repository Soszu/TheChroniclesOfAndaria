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

class PanelAkcji;
class CyklGry;
class Plansza;
class ParserPrzeciwnikow;
class ParserPrzedmiotow;
class ParserNagrod;

class MistrzGry
{
	friend class ParserPrzeciwnikow;
	friend class ParserPrzedmiotow;
	friend class ParserNagrod;
public:
	MistrzGry();
	~MistrzGry();
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
	QMap<QString, QSet<int>* > grupy; //dla każdej grupy trzymane są identyfikatory przedmiotów do niej należących
	QMap<int, Przedmiot*> przedmioty; //dla każdego identyfikatora trzymany jest opis przedmiotu.
	QMap<int, Nagroda*> nagrody;//dla każdego identyfikatora trzymany jest opis nagrody.
	Gracz* aktualnyGracz;
	CyklGry* cyklGry;
	PanelAkcji* panelAkcji;
	OknoGracza* oknoGracza;
	Plansza* plansza;

	Nagroda* podajNagrode(int id);
	void walka(Akcja opcja);
};

#endif // MISTRZGRY_H
