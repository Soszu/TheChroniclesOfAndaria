#include "cyklgry.h"

CyklGry::CyklGry()
{
	indeksAktualnego = 0;
}

void CyklGry::setGracze(QList<Gracz *> gracze)
{
	this->gracze = gracze;
}

void CyklGry::setPanelAkcji(PanelAkcji *panel)
{
	this->panelAkcji = panel;
}

void CyklGry::setOknoGracza(OknoGracza *okno)
{
	this->oknoGracza = okno;
}

void CyklGry::wybranoAkcje(QString nazwa)
{

}

QList<Gracz *> CyklGry::getGracze()
{
	return gracze;
}

void CyklGry::rozpocznij()
{
	ruszGracza(indeksAktualnego);
}


void CyklGry::ruszGracza(int indeks)
{
	if(gracze[indeks]->czyAI)
	{
		//wyswietl "AI myśli..."
		//zapytaj o decyzje dając akcje (być może jeszcze osiągalne pola jeśli plansza je udostępnia)
		//jeśli to ruch niech plansza go wyświetli
	}
	else
	{
		oknoGracza->wyswietlGracza(gracze[indeks]);
		//panelAkcji->wyswietlAkcje(/*Akcje*/); //mistrzGry->akcjeGracza(gracze[index]) ??
		//powiedz planszy niech się podświetli
	}
}


void CyklGry::zakonczTure()
{
	if(++indeksAktualnego >= gracze.size())
		indeksAktualnego = 0;
	ruszGracza(indeksAktualnego);
}
