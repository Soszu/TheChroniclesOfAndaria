#include "plansza.h"

Plansza::Plansza()
{
	ParserUkladu pu(this);
	if(pu.bladWczytywania())
	{
		qDebug()<< "blad wczytywania";
	}
	if(pu.bladWczytywania())
		qDebug() << QString::fromUtf8("Wystąpił błąd przy wczytywaniu ustawienia planszy");
	qDebug() << QString::fromUtf8("Ustawienie planszy wczytano poprawnie");

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
