#include "mistrzgry.h"

MistrzGry::MistrzGry(CyklGry* cykl)
{
	this->cyklGry = cykl;

	ParserPrzedmiotow parserPrzedmiotow(this);
	if(parserPrzedmiotow.bladWczytywania())
	{
		cyklGry->wystapilBlad(QString::fromUtf8("Wystąpił błąd przy wczytywaniu danych przedmiotow\n\n") + parserPrzedmiotow.trescBledu, blad_parsera_przedmiotow);
		return;
	}
	qDebug() << QString::fromUtf8("Informacje o przedmiotach wczytano poprawnie");

	ParserNagrod parserNagrod(this);
	if(parserNagrod.bladWczytywania())
	{
		cyklGry->wystapilBlad(QString::fromUtf8("Wystąpił błąd przy wczytywaniu danych nagród\n\n") + parserNagrod.trescBledu, blad_parsera_nagrod);
		return;
	}
	qDebug() << QString::fromUtf8("Informacje o nagrodach wczytano poprawnie");

	ParserPrzeciwnikow parserPrzeciwnikow(this);
	if(parserPrzeciwnikow.bladWczytywania())
	{
		cyklGry->wystapilBlad(QString::fromUtf8("Wystąpił błąd przy wczytywaniu danych przeciwników\n\n") + parserPrzeciwnikow.trescBledu, blad_parsera_przeciwnikow);
		return;
	}else if(grupyPrzeciwnikow.size() != LICZBA_GRUP_PRZECIWNIKOW)
	{
		cyklGry->wystapilBlad(QString::fromUtf8("Wczytano za mało albo za dużo grup przedmiotów.\n\n"), blad_liczby_grup_przeciwnikow);
		return;
	}
	qDebug() << QString::fromUtf8("Informacje o przeciwnikach wczytano poprawnie");

	ParserZadan parserZadan(this);
	if(parserZadan.bladWczytywania())
	{
		cyklGry->wystapilBlad(QString::fromUtf8("Wystąpił błąd przy wczytywaniu danych zadań\n\n") + parserZadan.trescBledu, blad_parsera_zadan);
		return;
	}
	qDebug() << QString::fromUtf8("Informacje o zadaniach wczytano poprawnie");
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

	QMap<QString, QList<int>*>::iterator it4;
	for (it4 = grupy.begin(); it4 != grupy.end(); ++it4)
		delete it4.value();

	QMap<int, QList<int>*>::iterator it5;
	for (it5 = grupyPrzeciwnikow.begin(); it5 != grupyPrzeciwnikow.end(); ++it5)
		delete it5.value();

	QMap<int, Zadanie*>::iterator it6;
	for (it6 = zadania.begin(); it6 != zadania.end(); ++it6)
		delete it6.value();
}

/**
 * @brief MistrzGry::ruszGracza Wykonuje wymagane operacje dla momentu, gdy rozpoczyna się tura kolejnego gracza
 * @param gracz aktualny gracz
 */
void MistrzGry::ruszGracza(Gracz *gracz)
{
	qDebug() <<"Mistrz gry obsluguje gracza: " <<gracz->getNazwa();

	aktualnyGracz = gracz;
	bazarOdwiedzony = false;

	//regeneracja
	gracz->setZdrowieAktualne(qMin(gracz->getZdrowieMaks(), (quint8)(gracz->getZdrowieAktualne() + gracz->getRegeneracja())));

	oknoGracza->wyswietlGracza(aktualnyGracz);

	panelAkcji->wyswietlAkcje(mozliweAkcje(aktualnyGracz));

	//TODO: jeśli to AI to zapytaj o decyzje
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
		//NOTE: do zmiany
akcje.push_front(koniecTury);
		return akcje; //pusta lista akcji (tymczasowo jest też zakończ turę, żeby się nie zwieszał)
	}

//	if(zajmowanePole->getCzyPoleZMiastem())
	{
		akcje.push_back(bazar);
		akcje.push_back(tawerna);
	}

//	if(zajmowanePole->getCzyPoleZPrzeciwnikiem())
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
		if(!bazarOdwiedzony)
			handelNaBazarze();
		break;
	case tawerna:
		break;
	default:
		break;
	}
}

/**
 * @brief MistrzGry::wykonanoRuch	Funkcja wywoływana przez Planszę, żeby oznajmić, że gracz jest teraz w innym miejscu
 */
void MistrzGry::wykonanoRuch()
{
	panelAkcji->wyswietlAkcje(mozliweAkcje(aktualnyGracz));
}

/**
 * @brief MistrzGry::koniecWalki	Funkcja wywoływana przez klasę Walka po zakończeniu walki.
 * @param przeciwnik	przeciwnik, który brał udział w walce (żeby można było np. przydzielić nagrodę)
 * @param rezultat	enumerator opisany w gra.h reprezentujacy wynik walki
 */
void MistrzGry::koniecWalki(Przeciwnik *przeciwnik, WynikWalki rezultat)
{
	switch (rezultat) {
	case przegrana:
		cyklGry->wykreslGracza(aktualnyGracz);
		break;
	case wygrana:
		przydzielNagrode(aktualnyGracz, przeciwnik->getNagroda());
		break;
	case ucieczka:
		cyklGry->zakonczTure();
		break;
	}
}

void MistrzGry::przydzielNagrode(Gracz *gracz, Nagroda *nagroda)
{
	QList<Przedmiot*> przydzielonePrzedmioty;

	//Zloto
	gracz->setZloto(qMax(0, gracz->getZloto() + nagroda->getZloto()));

	//Doswiadczenie
	gracz->setDoswiadczenie(gracz->getDoswiadczenie() + nagroda->getDoswiadczenie());

	//Losowy przedmiot
	QList<int> pula;
	for(int i = 0; i < nagroda->getNazwyGrup().size(); ++i)
		pula.append(*grupy[nagroda->getNazwyGrup()[i]]);

	if(pula.size() > 0)
	{
		qsrand( QDateTime::currentDateTime().toTime_t() );
		int los = qrand() % pula.size();

		przydzielonePrzedmioty.push_back(przedmioty[pula[los]]);
	}
	//Reputacja
	for(int i = 0; i < LICZBA_KROLESTW; ++i)
	{
		quint8 suma = nagroda->getReputacja()[i] + gracz->getReputacja()[i];
		quint8 nowaWartosc = qMin(MAX_REPUTACJA, suma);
		nowaWartosc = qMax(0, (int)nowaWartosc);
		gracz->setKonkretnaReputacja(nowaWartosc, i);
	}
	//Konkretne Przedmioty
	for(int i = 0; i < nagroda->getKonkretnePrzedmioty()->size(); ++i)
		przydzielonePrzedmioty.push_back(przedmioty[nagroda->getKonkretnePrzedmioty()->at(i)]);

	//Przypisanie przedmiotów
	Przedmiot* rzecz;
	foreach (rzecz, przydzielonePrzedmioty)
		//TODO: do zmiany
		if(rzecz->getRodzaj() == mikstura)
			if(rzecz->getNazwa() == "MNIEJSZA MIKSTURA ZDROWIA")
				gracz->getEkwipunek()->setMalePoty(gracz->getEkwipunek()->getMalePoty() + 1);
			else
				gracz->getEkwipunek()->setDuzePoty(gracz->getEkwipunek()->getDuzePoty() + 1);
		else
		gracz->getEkwipunek()->getPlecak()->push_back(rzecz);

	oknoGracza->uaktualnijInformacje();

	oknoNagrody = new OknoNagrody(aktualnyGracz, nagroda, przydzielonePrzedmioty, cyklGry);
	oknoNagrody->setAttribute(Qt::WA_DeleteOnClose);
	oknoNagrody->show();
}

Przeciwnik *MistrzGry::losujPrzeciwnika(int grupa)
{
	qsrand( QDateTime::currentDateTime().toTime_t() );

	int los = qrand() % grupyPrzeciwnikow[grupa]->size();

	return przeciwnicy[grupyPrzeciwnikow[grupa]->at(los)];
}

QList<Przedmiot*> *MistrzGry::towaryNaBazarze()
{
	towaryBazar.clear();
	for(int i = 0; i < LICZBA_PRZEDMIOTOW_NA_BAZARZE; ++i)
	{
		int los = qrand() % przedmioty.size();
		towaryBazar.push_back(przedmioty[los]);
	}

	return &towaryBazar;
}

/**
 * @brief MistrzGry::walka Funkcja losująca odpowiedniego przeciwnika i rozpoczynająca walkę
 * @param opcja		jaka opcja walki (jaki przeciwnik) została wybrana
 */
void MistrzGry::walka(Akcja opcja)
{
	int poziomLatwy = (aktualnyGracz->getPoziom() + 1 ) / 2;
	Przeciwnik* przeciwnik;

	if(opcja == przeciwnikLatwy)
		przeciwnik = losujPrzeciwnika(poziomLatwy);
	else
		przeciwnik = losujPrzeciwnika(poziomLatwy + 1);

	oknoWalki = new Walka(aktualnyGracz, przeciwnik, this);
	oknoWalki->setAttribute(Qt::WA_DeleteOnClose);
	oknoWalki->rozpocznij();
}

void MistrzGry::handelNaBazarze()
{
	bazarOdwiedzony = true;
	oknoBazaru = new OknoBazaru(aktualnyGracz, oknoGracza, towaryNaBazarze());
	oknoBazaru->setAttribute(Qt::WA_DeleteOnClose);
	oknoBazaru->show();
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
