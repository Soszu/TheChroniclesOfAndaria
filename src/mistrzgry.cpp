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

	//panelAkcji->wyswietlAkcje(mozliweAkcje(gracz));
	//wybranoAkcje(QString::fromUtf8("Zakończ turę"));
	if(gracz->czyAI)
		oknoGracza ->wyswietlMonitAI();
	else
		oknoGracza->wyswietlGracza(gracz);
}

/**
 * @brief MistrzGry::mozliweAkcje Na podstawie aktualnej pozycji /sytuacji ustala możliwe akcje.
 * @param gracz aktualny gracz
 * @return lista QString zawierająca nazwy możliwych akcji
 */
QList<QString> MistrzGry::mozliweAkcje(Gracz *gracz)
{
	QList<QString> test;

	if(gracz->czyAI)
		return test; //pusta lista akcji

	test.push_back("okno");
	test.push_back("dupa");
	test.push_back("chuj");
	test.push_back("hipster");
	test.push_back("okno");
	test.push_back("dupa");
	test.push_back(QString::fromUtf8("Zakończ turę")); //można zrobić enum

	return test;
}

/**
 * @brief MistrzGry::setCyklGry Ustawia cykl gry, żeby powiedzieć mu o końcy tury/gry
 * @param cykl
 */
void MistrzGry::setCyklGry(CyklGry *cykl)
{
	this->cyklGry = cykl;
}

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

/**
 * @brief MistrzGry::wybranoAkcje Jeżeli ta metoda została wywołana, to grafika zgłasza kliknięcie na przycisk
 * @param nazwa nazwa akcji, która została wybrana (Tekst przycisku)
 */
void MistrzGry::wybranoAkcje(QString nazwa)
{
	qDebug() << "wybrano akcje: " << nazwa;
	if(nazwa == QString::fromUtf8("Zakończ turę"))
		cyklGry->zakonczTure();
}
