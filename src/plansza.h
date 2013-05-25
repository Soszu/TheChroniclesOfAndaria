#ifndef PLANSZA_H
#define PLANSZA_H

#include <QList>
#include <QPair>
#include <map>
#include "gra.h"
#include "plansza.h"
#include "mistrzgry.h"
#include "parserukladu.h"
#include "gracz.h"
#include "obszarplanszy.h"
#include "pole.h"

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
	QList<IDPola> pokazOsiagalne();
	QList<IDPola> odtworzDroge(IDPola pole);
	QList<QPair<QColor, IDPola> >* spiszPozycje();
	void ruchAI(IDPola pole);
private:
	ObszarPlanszy* obszarPlanszy;
	MistrzGry* mistrzGry;
	QList<QPair<QColor, IDPola> >* pozycjeGraczy;
	std::map<IDPola, IDPola> osiagalne;
	QList<Gracz*>* gracze;
	quint8 szerokoscPlanszy;
	quint8 wysokoscPlanszy;
	QList<Pole*>* pola;
	Gracz* aktualnyGracz;
	int indeksAktualnego;
	bool graRozpoczeta;
	bool graczWykonalRuch;
};

#endif // PLANSZA_H
