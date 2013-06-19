#include "sztucznainteligencja.h"

SztucznaInteligencja::SztucznaInteligencja(Gracz *gracz)
{
	this->gracz = gracz;
}

void SztucznaInteligencja::ustawAkcje(QList<Akcja> akcje)
{
}

void SztucznaInteligencja::ustawZadania(QList<Zadanie *> zadania)
{
}

int SztucznaInteligencja::decyduj()
{
	return koniecTury; //zawsze mozliwe
}
