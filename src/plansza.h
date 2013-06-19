#ifndef PLANSZA_H
#define PLANSZA_H

#include <QList>
#include <QPair>
#include <QMap>
#include <QQueue>
#include "gra.h"
#include "plansza.h"
#include "mistrzgry.h"
#include "cyklgry.h"
#include "parserukladu.h"
#include "gracz.h"
#include "obszarplanszy.h"
#include "pole.h"

using namespace std;

class ObszarPlanszy;
class MistrzGry;
class CyklGry;
class ParserUkladu;

class Plansza
{
	friend class ParserUkladu;
public:
	Plansza(CyklGry *cykl);
	~Plansza();
	void setObszarPlanszy(ObszarPlanszy* obszar);
	void setMistrzGry(MistrzGry* mistrz);
	void setGracze(QList<Gracz*>* gracze);
	void ruszGracza(Gracz* gracz, int indeks);
	void kliknietoHex(IDPola id);
	void ustalOsiagalne(Gracz* gracz);
	void uaktualnijOsiagalne();
	void wykreslGracza(int indeks);
	Pole *pokazPole(IDPola pole);
	bool czyTrwaAnimacja();
	QList<IDPola> pokazOsiagalne();
	void ruchAI(IDPola pole);
	void pokazHex(IDPola id);
	void blokujRuch();
private:
	ObszarPlanszy* obszarPlanszy;
	MistrzGry* mistrzGry;
	CyklGry* cyklGry;

	QList<QPair<QColor, IDPola> >* pozycjeGraczy;
	QList<Gracz*>* gracze;
	QList<Pole*>* pola;
	QList<IDPola> osiagalne;
	QMap<int, IDPola> poprzednie; //<indeks pola obecnego, pole z którego można na nie przyjść>

	quint8 szerokoscPlanszy;
	quint8 wysokoscPlanszy;
	Gracz* aktualnyGracz;
	int indeksAktualnego;

	bool graRozpoczeta;
	bool graczWykonalRuch;

	QList<IDPola> odtworzDroge(IDPola pole);
	QList<QPair<QColor, IDPola> >* spiszPozycje();

	int IDToIndeks(IDPola pole);
	IDPola indeksToID(int indeks);
	QList<IDPola> sasiedniePola(IDPola pole);
};

#endif // PLANSZA_H
