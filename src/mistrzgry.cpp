#include "mistrzgry.h"

MistrzGry::MistrzGry()
{

	ParserPrzedmiotow parserPrzedmiotow(this);
	if(parserPrzedmiotow.bladWczytywania())
	{
		cyklGry->wystapilBlad(QString::fromUtf8("Wystąpił błąd przy wczytywaniu danych przedmiotow"));
		return;
	}
	qDebug() << QString::fromUtf8("Informacje o przedmiotach wczytano poprawnie");

	ParserNagrod parserNagrod(this);
	if(parserNagrod.bladWczytywania())
	{
		cyklGry->wystapilBlad(QString::fromUtf8("Wystąpił błąd przy wczytywaniu danych nagród"));
		return;
	}
	qDebug() << QString::fromUtf8("Informacje o nagrodach wczytano poprawnie");

	ParserPrzeciwnikow parserPrzeciwnikow(this);
	if(parserPrzeciwnikow.bladWczytywania())
	{
		cyklGry->wystapilBlad(QString::fromUtf8("Wystąpił błąd przy wczytywaniu danych przeciwników"));
		return;
	}
	qDebug() << QString::fromUtf8("Informacje o przeciwnikach wczytano poprawnie");

}

MistrzGry::~MistrzGry()
{

	QMap<int, Przedmiot*>::iterator it;
	for (it = przedmioty.begin(); it != przedmioty.end(); ++it)
		delete it.value();

	QMap<int, Przeciwnik*>::iterator it2;
	for (it2 = przeciwnicy.begin(); it2 != przeciwnicy.end(); ++it2)
		delete it2.value();

	QMap<int, Nagroda*>::iterator it3;
	for (it3 = nagrody.begin(); it3 != nagrody.end(); ++it3)
		delete it3.value();

	QMap<QString, QSet<int>*>::iterator it4;
	for (it4 = grupy.begin(); it4 != grupy.end(); ++it4)
		delete it4.value();
}

/**
 * @brief MistrzGry::ruszGracza Wykonuje wymagane operacje dla momentu, gdy rozpoczyna się tura kolejnego gracza
 * @param gracz aktualny gracz
 */
void MistrzGry::ruszGracza(Gracz *gracz)
{
	qDebug() <<"Mistrz gry obsluguje gracza: " <<gracz->getNazwa();

	aktualnyGracz = gracz;

	//regeneracja
	gracz->setZdrowieAktualne(qMin(gracz->getZdrowieMaks(), (quint8)(gracz->getZdrowieAktualne() + gracz->getRegeneracja())));

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

	switch (nazwa) {
	case koniecTury:
		cyklGry->zakonczTure();
		break;
	case przeciwnikLatwy:
		walka(nazwa);
		break;
	case przeciwnikTrudny:
		walka(nazwa);
		break;
	case bazar:
		break;
	case tawerna:
		break;
	default:
		break;
	}
}

void MistrzGry::wykonanoRuch()
{
	panelAkcji->wyswietlAkcje(mozliweAkcje(aktualnyGracz));
}

void MistrzGry::koniecWalki(Przeciwnik *przeciwnik, WynikWalki rezultat)
{
	if(rezultat = wygrana)
	{
		przydzielNagrode(aktualnyGracz, przeciwnik->getNagroda());
		cyklGry->zakonczTure();
	}
	if(rezultat = przegrana)
		cyklGry->wykreslGracza(aktualnyGracz);

	if(rezultat = ucieczka)
		cyklGry->zakonczTure();
}

void MistrzGry::przydzielNagrode(Gracz *gracz, Nagroda *nagroda)
{
	//TODO: przydzielanie
	qDebug("przydzielanie nagrody");
}

void MistrzGry::walka(Akcja opcja)
{
//TODO: Losowanie
	if(opcja == przeciwnikLatwy)
	{}//losowanie
	else
	{}//losowanie
	//Stocz walkę gracz, przeciwnik
	qsrand( QDateTime::currentDateTime().toTime_t() );
	int los = qrand() % przeciwnicy.size() + 1;

	oknoWalki = new Walka(aktualnyGracz, przeciwnicy[los], this);
	oknoWalki->setAttribute(Qt::WA_DeleteOnClose);
	oknoWalki->show();
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
