#include "mistrzgry.h"

MistrzGry::MistrzGry()
{
	ParserPrzeciwnikow parserPrzeciwnikow(this);
	if(parserPrzeciwnikow.bladWczytywania())
	{
		cyklGry->wystapilBlad(QString::fromUtf8("Wystąpił błąd przy wczytywaniu danych przeciwników"));
		return;
	}
	qDebug() << QString::fromUtf8("Informacje o przeciwnikach wczytano poprawnie");

	ParserPrzedmiotow parserPrzedmiotow(this);
	if(parserPrzedmiotow.bladWczytywania())
	{
		cyklGry->wystapilBlad(QString::fromUtf8("Wystąpił błąd przy wczytywaniu danych przedmiotow"));
		return;
	}
	qDebug() << QString::fromUtf8("Informacje o przedmiotach wczytano poprawnie");
}

/**
 * @brief MistrzGry::ruszGracza Wykonuje wymagane operacje dla momentu, gdy rozpoczyna się tura kolejnego gracza
 * @param gracz aktualny gracz
 */
void MistrzGry::ruszGracza(Gracz *gracz)
{
	qDebug() <<"Mistrz gry obsluguje gracza: " <<gracz->getNazwa();

	aktualnyGracz = gracz;

	oknoGracza->wyswietlGracza(aktualnyGracz);

	panelAkcji->wyswietlAkcje(mozliweAkcje(aktualnyGracz));

	//jeśli to AI to zapytaj o decyzje

}

/**
 * @brief MistrzGry::mozliweAkcje Na podstawie aktualnej pozycji /sytuacji ustala możliwe akcje.
 * @param gracz aktualny gracz
 * @return lista QString zawierająca nazwy możliwych akcji
 */
QList<Akcja> MistrzGry::mozliweAkcje(Gracz *gracz)
{
	QList<Akcja> akcje;
	Pole* zajmowanePole = plansza->pokazPole(gracz->getPozycja());

	if(gracz->getCzyAI())
	{
		akcje.push_front(koniecTury);
		return akcje; //pusta lista akcji (tymczasowo jest też zakończ turę, żeby się nie zwieszał)
	}

	if(zajmowanePole->getCzyPoleZMiastem())
	{
		akcje.push_back(bazar);
		akcje.push_back(tawerna);
	}

	if(zajmowanePole->getCzyPoleZPrzeciwnikiem())
	{
		akcje.push_back(przeciwnikLatwy);
		akcje.push_back(przeciwnikTrudny);
	}

	akcje.push_back(koniecTury);
	return akcje;
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

void MistrzGry::wykonanoRuch()
{
	panelAkcji->wyswietlAkcje(mozliweAkcje(aktualnyGracz));
}

Nagroda *MistrzGry::podajNagrode(int id)
{
	//TODO
	return NULL;
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
