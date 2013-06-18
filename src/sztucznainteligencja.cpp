#include "sztucznainteligencja.h"

SztucznaInteligencja::SztucznaInteligencja(Gracz *gracz)
{
	this->gracz = gracz;
}

void SztucznaInteligencja::ustawAkcje(QList<Akcja> akcje)
{
	this->akcje = akcje;
}

void SztucznaInteligencja::ustawZadania(QList<Zadanie *> zadania)
{
	this->zadania = zadania;
}

int SztucznaInteligencja::decyduj()
{
	return koniecTury; //zawsze mozliwe
}
