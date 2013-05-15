#include "plansza.h"

Plansza::Plansza()
{
}

void Plansza::setObszarPlanszy(ObszarPlanszy *obszar)
{
	this->obszarPlanszy = obszar;
}

void Plansza::setMistrzGry(MistrzGry *mistrz)
{
	this->mistrzGry = mistrz;
}

void Plansza::ruszGracza(Gracz *gracz)
{
	qDebug() <<"Plansza rusza gracza: " <<gracz->nazwa;
}
