#include "mistrzgry.h"

MistrzGry::MistrzGry()
{

}

/**
 * @brief MistrzGry::ruszGracza Wykonuje wymagane operacje dla momentu, gdy rozpoczyna się tura kolejnego gracza
 * @param gracz aktualny gracz
 */
void MistrzGry::ruszGracza(Gracz *gracz)
{
	qDebug() <<"Mistrz gry obsluguje gracza: " <<gracz->nazwa;

	oknoGracza->wyswietlGracza(gracz);

	panelAkcji->wyswietlAkcje(mozliweAkcje(gracz));

	//jeśli to AI to zapytaj o decyzje

}

/**
 * @brief MistrzGry::mozliweAkcje Na podstawie aktualnej pozycji /sytuacji ustala możliwe akcje.
 * @param gracz aktualny gracz
 * @return lista QString zawierająca nazwy możliwych akcji
 */
QList<Akcja> MistrzGry::mozliweAkcje(Gracz *gracz)
{
	QList<Akcja> test;

	if(gracz->czyAI)
		return test; //pusta lista akcji

	test.push_back(koniecTury);
	test.push_back(testowa);

	return test;
}

/**
 * @brief MistrzGry::wybranoAkcje Jeżeli ta metoda została wywołana, to grafika zgłasza kliknięcie na przycisk
 * @param nazwa nazwa akcji, która została wybrana (Tekst przycisku)
 */
void MistrzGry::wybranoAkcje(Akcja nazwa)
{
	qDebug() << "wybrano akcje: " << AKCJE[nazwa];

	//switch ?
	if(nazwa == koniecTury)
		cyklGry->zakonczTure();
}

/**
 * @brief MistrzGry::setCyklGry Ustawia cykl gry, żeby powiedzieć mu o końcy tury/gry
 * @param cykl
 */
void MistrzGry::setCyklGry(CyklGry *cykl)
{
	this->cyklGry = cykl;
}

/**
 * @brief MistrzGry::setPlansza Ustawia planszę, żeb ypowiedzieć jej o ewentualnej zmianie punktów ruchu (wtedy plansza może chcieć podświetlić więcej)
 * @param plansza
 */
void MistrzGry::setPlansza(Plansza *plansza)
{
	this->plansza = plansza;
}

/**
 * @brief MistrzGry::setPanelAkcji Ustawia panel którego może prosić o wyświetlenie klikalnych akcji
 * @param panel
 */
void MistrzGry::setPanelAkcji(PanelAkcji *panel)
{
	this->panelAkcji = panel;
}

/**
 * @brief MistrzGry::setOknoGracza Ustawia okno gracza którego może prosić o wyświetlenie informacji o dowolnym graczu
 * @param okno
 */
void MistrzGry::setOknoGracza(OknoGracza *okno)
{
	this->oknoGracza = okno;
}
