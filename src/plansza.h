#ifndef PLANSZA_H
#define PLANSZA_H

#include <QList>
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
	void ruszGracza(Gracz* gracz);

private:
	ObszarPlanszy* obszarPlanszy;
	MistrzGry* mistrzGry;

	quint8 szerokoscPlanszy;
	quint8 wysokoscPlanszy;
	QList<Pole*>* pola;
};

#endif // PLANSZA_H
