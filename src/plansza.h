#ifndef PLANSZA_H
#define PLANSZA_H

#include <QList>
#include <QPair>
#include <QMap>
#include <QQueue>
#include "gra.h"
#include "plansza.h"
#include "mistrzgry.h"
#include "parserukladu.h"
#include "gracz.h"
#include "obszarplanszy.h"
#include "pole.h"

using namespace std;

class ObszarPlanszy;
class MistrzGry;
class ParserUkladu;

class Plansza
{
	friend class ParserUkladu;
public:
	Plansza();
	void setObszarPlanszy(ObszarPlanszy* obszar);
	void setMistrzGry(MistrzGry* mistrz);
	void setGracze(QList<Gracz*>* gracze);
	void ruszGracza(Gracz* gracz, int indeks);
	void kliknietoHex(IDPola id);
	void ustalOsiagalne(Gracz* gracz);
	bool czyTrwaAnimacja();
	QList<IDPola> pokazOsiagalne();
	QList<IDPola> odtworzDroge(IDPola pole);
	QList<QPair<QColor, IDPola> >* spiszPozycje();
	void ruchAI(IDPola pole);
private:
	ObszarPlanszy* obszarPlanszy;
	MistrzGry* mistrzGry;

	QList<QPair<QColor, IDPola> >* pozycjeGraczy;
	QList<Gracz*>* gracze;
	QList<Pole*>* pola;
	QList<IDPola> osiagalne;
	QMap<int, IDPola> poprzednie;

	quint8 szerokoscPlanszy;
	quint8 wysokoscPlanszy;
	Gracz* aktualnyGracz;
	int indeksAktualnego;

	bool graRozpoczeta;
	bool graczWykonalRuch;

	int IDToIndeks(IDPola pole);
	IDPola indeksToID(int indeks);
	QList<IDPola> sasiedniePola(IDPola pole);
};

#endif // PLANSZA_H
