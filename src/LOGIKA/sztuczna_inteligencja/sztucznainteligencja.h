#ifndef SZTUCZNAINTELIGENCJA_H
#define SZTUCZNAINTELIGENCJA_H

#include "gra.h"
#include "zadanie.h"
#include "gracz.h"

class SztucznaInteligencja
{
public:
	SztucznaInteligencja(Gracz* gracz);
	void ustawAkcje(QList<Akcja> akcje);
	void ustawZadania(QList<Zadanie*> zadania);
	int decyduj();
private:
	Gracz* gracz;
};

#endif // SZTUCZNAINTELIGENCJA_H
