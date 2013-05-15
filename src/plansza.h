#ifndef PLANSZA_H
#define PLANSZA_H

#include "plansza.h"
#include "mistrzgry.h"
#include "gracz.h"
#include "obszarplanszy.h"

class ObszarPlanszy;
class MistrzGry;

class Plansza
{
public:
	Plansza();
	void setObszarPlanszy(ObszarPlanszy* obszar);
	void setMistrzGry(MistrzGry* mistrz);
	void ruszGracza(Gracz* gracz);

private:
	ObszarPlanszy* obszarPlanszy;
	MistrzGry* mistrzGry;
};

#endif // PLANSZA_H
