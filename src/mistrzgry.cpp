#include "mistrzgry.h"

MistrzGry::MistrzGry(CyklGry* cykl)
{
	qsrand( QDateTime::currentDateTime().toTime_t() );

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
void MistrzGry::ruszGracza(Gracz *gracz, int indeks)
{
	qDebug() <<"Mistrz gry obsluguje gracza: " <<gracz->getNazwa();

	aktualnyGracz = gracz;
	bazarOdwiedzony = false;
	tawernaOdwiedzona = false;
	realizowaneZadanie = NULL;

	//regeneracja
	gracz->setZdrowieAktualne(qMin(gracz->getZdrowieMaks(), (quint8)(gracz->getZdrowieAktualne() + gracz->getRegeneracja())));

	oknoGracza->wyswietlGracza(aktualnyGracz);
	if(gracz->getCzyAI())
	{
		boty[indeks]->ustawAkcje(mozliweAkcje(aktualnyGracz));
		boty[indeks]->ustawZadania(mozliweZadania(aktualnyGracz));
		wybranoDzialanie(boty[indeks]->decyduj());
	}
	else
	{
		panelAkcji->ustawAkcje(mozliweAkcje(aktualnyGracz));
		panelAkcji->ustawZadania(mozliweZadania(aktualnyGracz));
		panelAkcji->wyswietl();
	}
}

/**
 * @brief MistrzGry::mozliweAkcje	Zwraca listę możliwych do wykonania akcji zależnie od rodzaju pola na którym znajduje się gracz.
 * @param gracz		Gracz, którego akcje mają być wyświetlone.
 * @return		QList<Akcja> zawierająca możliwe akcje
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
		if(!bazarOdwiedzony)
			akcje.push_back(bazar);
		if(!tawernaOdwiedzona)
			akcje.push_back(tawerna);
	}

	if(zajmowanePole->getCzyPoleZPrzeciwnikiem() && !gracz->getOstatnioWalczyl())
	{
		akcje.push_back(przeciwnikLatwy);
		akcje.push_back(przeciwnikTrudny);
	}

	akcje.push_back(koniecTury);
	return akcje;
}

/**
 * @brief MistrzGry::mozliweZadania	Zwraca listę zadań możliwych do wykonania na polu, na którym znajduje się gracz.
 * @param gracz		dane gracza, którego zadania mają być wyświetlone.
 * @return		QList<Zadanie*> zawierające możliwe akcje
 */
QList<Zadanie *> MistrzGry::mozliweZadania(Gracz *gracz)
{
	QList<Zadanie*> zadania;

	for(int i = 0; i < gracz->getZadania()->size(); ++i)
	{
		IDPola cel = gracz->getKonkretneZadanie(i)->getPoleCelu();
		if(gracz->getPozycja().x == cel.x && gracz->getPozycja().y == cel.y)
			zadania.push_back(gracz->getKonkretneZadanie(i));
	}

	return zadania;
}

/**
 * @brief MistrzGry::polaczNagrody	Łączy 2 nagrody w jedną i daje do niej wskaźnik, należy zatroszczyć się						o jej własnoręczne usunięcie
 * @param pierwsza	dane pierwszej nagrody
 * @param druga		dane drugiej nagrody
 * @return		zwraca wskaźnik do nowo utworzonej nagrody
 */
Nagroda* MistrzGry::polaczNagrody(Nagroda *pierwsza, Nagroda *druga)
{
	QList<int>* konkrety = new QList<int>();
	konkrety->append(*pierwsza->getKonkretnePrzedmioty());
	konkrety->append(*druga->getKonkretnePrzedmioty());

	quint8* reputacja = new quint8[LICZBA_KROLESTW];
	for(int i = 0; i < LICZBA_KROLESTW; ++i)
		reputacja[i] = pierwsza->getReputacja()[i] + druga->getReputacja()[i];

	return new Nagroda(reputacja,
			   pierwsza->getZloto() + druga->getZloto(),
			   pierwsza->getDoswiadczenie() + druga->getDoswiadczenie(),
			   pierwsza->getNazwyGrup() + druga->getNazwyGrup(),
			   konkrety);

}

/**
 * @brief MistrzGry::wybranoAkcje	Jeżeli ta metoda została wywołana,
 *					to grafika zgłasza kliknięcie na przycisk
 * @param nazwa		opcja, która została wybrana
 */
void MistrzGry::wykonajAkcje(Akcja opcja)
{
	switch ((Akcja)opcja) {
	case koniecTury:
		aktualnyGracz->setOstatnioWalczyl(false);
		cyklGry->zakonczTure();
		break;
	case przeciwnikLatwy:
		walka((Akcja)opcja);
		break;
	case przeciwnikTrudny:
		walka((Akcja)opcja);
		break;
	case bazar:
		plansza->blokujRuch();
		if(!bazarOdwiedzony)
			handelNaBazarze();
		panelAkcji->ustawAkcje(mozliweAkcje(aktualnyGracz));
		panelAkcji->wyswietl();
		break;
	case tawerna:
		plansza->blokujRuch();
		if(!tawernaOdwiedzona)
			idzDoTawerny();
		panelAkcji->ustawAkcje(mozliweAkcje(aktualnyGracz));
		panelAkcji->wyswietl();
		break;
	}
}

/**
 * @brief MistrzGry::wykonajZadanie	Wykonuje zadanie o podanym id.
 *					Działanie jest uzależnione od stopnia wykonania zadania.
 *					Metoda zakłada, że zadanie o podany
 * @param gracz		dane gracza, wykonującego zadanie
 * @param id		id zadania
 */
void MistrzGry::wykonajZadanie(Gracz* gracz, int id)
{
	gracz->setOstatnioWalczyl(false);
	bool sukces;
	int indeks = 0;
	while(gracz->getKonkretneZadanie(indeks)->getId() != id)
		++indeks;

	Zadanie* zadanie = gracz->getKonkretneZadanie(indeks);

	switch (zadanie->getRodzaj()) {
	case przynies:
		if(!zadanie->getCzyPowrot() || zadanie->getCzyWykonanoCzesc())
		{
			przydzielNagrode(gracz, zadanie->getNagroda());
			gracz->getZadania()->removeAt(indeks);
		}
		else
		{
			zadanie->setCzyWykonanoCzesc(true);
			zadanie->setPoleCelu(zadanie->getZleceniodawca());
			cyklGry->zakonczTure();
		}
		break;
	case odnajdz:
		if(zadanie->getCzyWykonanoCzesc())
		{
			przydzielNagrode(gracz, zadanie->getNagroda());
			gracz->getZadania()->removeAt(indeks);
			break;
		}
		sukces = qrand() % 100 < SZANSA_NA_ODNALEZIENIE;
		QMessageBox::information(
			cyklGry->getMainWindow(),
			zadanie->getTytul(),
			sukces ?
			QString::fromUtf8("Udało Ci się wykonać zadanie.") :
			QString::fromUtf8("Niestety, nie udało Ci się wykonać zadania.") );
		if(sukces)
		{
			if(zadanie->getCzyPowrot())
			{
				zadanie->setCzyWykonanoCzesc(true);
				zadanie->setPoleCelu(zadanie->getZleceniodawca());
			}
			else
			{
				przydzielNagrode(gracz, zadanie->getNagroda());
				gracz->getZadania()->removeAt(indeks);
			}
		}
		cyklGry->zakonczTure();
		break;
	case pokonaj:
		realizowaneZadanie = zadanie;
		walka(przeciwnikZZadania);
		break;
	}
}

/**
 * @brief MistrzGry::wybranoDzialanie		Metoda wywoływana z zewnątrz.
 *						Sprawdza i obsługuje działanie gracza.
 *						Zadanie: opcja < 0; Akcja: opcja >= 0
 * @param opcja
 */
void MistrzGry::wybranoDzialanie(int opcja)
{
	if(plansza->czyTrwaAnimacja())
		return;

	if(opcja >= 0)
	{
		qDebug() << "wybrano akcje: " << AKCJE[opcja];
		wykonajAkcje((Akcja)opcja);
	}
	else
	{
		qDebug()<<"wybrano zadanie: " << zadania[opcja * -1]->getTytul();
		wykonajZadanie(aktualnyGracz, opcja * -1);
	}
}

/**
 * @brief MistrzGry::wykonanoRuch	Metoda wywoływana z zewnątrz.
 *					Informuje, że gracz jest teraz w innym miejscu.
 */
void MistrzGry::wykonanoRuch()
{
	aktualnyGracz->setOstatnioWalczyl(false);
	panelAkcji->ustawAkcje(mozliweAkcje(aktualnyGracz));
	panelAkcji->ustawZadania(mozliweZadania(aktualnyGracz));
	panelAkcji->wyswietl();
}

/**
 * @brief MistrzGry::poinformujPlansze	Informuje planszę o zmianie statystyk (przerysowanie osiągalnych pól)
 */
void MistrzGry::poinformujPlansze()
{
	plansza->uaktualnijOsiagalne();
}

/**
 * @brief MistrzGry::koniecWalki	Metoda wywoływana z zewnątrz. Informuje o wyniku walki.
 * @param przeciwnik	przeciwnik, który brał udział w walce (żeby można było np. przydzielić nagrodę)
 * @param rezultat	enumerator opisany w gra.h reprezentujacy wynik walki
 */
void MistrzGry::koniecWalki(Przeciwnik *przeciwnik, WynikWalki rezultat)
{
	switch (rezultat) {
	case przegrana:
		cyklGry->wykreslAktualnego();
		cyklGry->zakonczTure();
		break;
	case wygrana:
		if(realizowaneZadanie != NULL)
		{
			realizowaneZadanie->getPrzeciwnicy()->removeFirst();
			if(realizowaneZadanie->getPrzeciwnicy()->isEmpty());
			{
				Nagroda* nagroda = polaczNagrody(przeciwnik->getNagroda(), realizowaneZadanie->getNagroda());
				przydzielNagrode(aktualnyGracz, nagroda);
				delete nagroda;
				aktualnyGracz->usunZadanie(realizowaneZadanie->getId());
				realizowaneZadanie = NULL;
				break;
			}
		}
		przydzielNagrode(aktualnyGracz, przeciwnik->getNagroda());
		break;
	case ucieczka:
		cyklGry->zakonczTure();
		break;
	}
}

/**
 * @brief MistrzGry::przydzielNagrode	Zmienia dane gracze stosownie do podanej nagrody.
 *					Zmiana poziomu jest wykonywana w Oknie Nagrody.
 * @param gracz		Gracz, któremu ma zostać przydzielona nagroda.
 * @param nagroda	Nagroda, która ma zostać przydzielona.
 */
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
	oknoNagrody->rozpocznij();
}

/**
 * @brief MistrzGry::losujPrzeciwnika Metoda losująca przeciwnika z zadanej grupy.
 * @param grupa		indeks grupy, z której ma być losowany przeciwnik.
 * @return		Wskaźnik na wylosowanego przeciwnika.
 */
Przeciwnik *MistrzGry::losujPrzeciwnika(int grupa)
{

	int los = qrand() % grupyPrzeciwnikow[grupa]->size();

	return przeciwnicy[grupyPrzeciwnikow[grupa]->at(los)];
}

/**
 * @brief MistrzGry::walka	Funkcja losująca odpowiedniego przeciwnika i rozpoczynająca walkę
 * @param opcja		informacja jaka opcja walki (jaki przeciwnik) została wybrana
 */
void MistrzGry::walka(Akcja opcja)
{
	int poziomLatwy = (aktualnyGracz->getPoziom() + 1 ) / 2;
	Przeciwnik* przeciwnik;

	switch(opcja) {
	case przeciwnikLatwy:
		przeciwnik = losujPrzeciwnika(poziomLatwy);
		break;
	case przeciwnikTrudny:
		przeciwnik = losujPrzeciwnika(poziomLatwy + 1);
		break;
	case przeciwnikZZadania:
		przeciwnik = realizowaneZadanie->getPrzeciwnicy()->front();
	}

	aktualnyGracz->setOstatnioWalczyl(true);
	oknoWalki = new Walka(aktualnyGracz, przeciwnik, this);
	oknoWalki->setAttribute(Qt::WA_DeleteOnClose);
	oknoWalki->rozpocznij();
}

/**
 * @brief MistrzGry::idzDoTawerny	Metoda losująca zadania w tawernie i wyświetlająca Okno Tawerny
 */
void MistrzGry::idzDoTawerny()
{
	zadaniaWTawernie.clear();
	for(int i = 0; i < LICZBA_ZADAN_W_TAWERNIE; ++i)
	{
		int los = qrand() % zadania.size() + 1;
		//FIXME: dodanie losowych nie bazujących na ciągłości przedziału + bez powtórzeń
		QMap<int, Zadanie*>::iterator iter = zadania.begin();
		for (int i = 0; i < los; ++i)
			++iter;
		zadaniaWTawernie.push_back(zadania[los]);
	}

	tawernaOdwiedzona = true;
	oknoTawerny = new OknoTawerny(aktualnyGracz, plansza, &zadaniaWTawernie);
	oknoTawerny->setAttribute(Qt::WA_DeleteOnClose);
	oknoTawerny->show();
}

/**
 * @brief MistrzGry::handelNaBazarze	Metoda losująca przedmioty na bazarze i wyświetlająca Okno Bazaru
 */
void MistrzGry::handelNaBazarze()
{
	towaryNaBazarze.clear();
	for(int i = 0; i < LICZBA_PRZEDMIOTOW_NA_BAZARZE; ++i)
	{
		int los = qrand() % przedmioty.size();
		//FIXME: dodanie losowych nie bazujących na ciągłości przedziału + bez powtórzeń

		QMap<int, Przedmiot*>::iterator iter = przedmioty.begin();
		for(int i = 0; i < los; ++i)
			++iter;
		towaryNaBazarze.push_back(przedmioty[los]);
	}

	bazarOdwiedzony = true;
	oknoBazaru = new OknoBazaru(aktualnyGracz, oknoGracza, &towaryNaBazarze);
	oknoBazaru->setAttribute(Qt::WA_DeleteOnClose);
	oknoBazaru->show();
}

void MistrzGry::setPlansza(Plansza *plansza)
{
	this->plansza = plansza;
}

Plansza *MistrzGry::getPlansza()
{
	return plansza;
}

void MistrzGry::setPanelAkcji(PanelAkcji *panel)
{
	this->panelAkcji = panel;
}

void MistrzGry::setOknoGracza(OknoGracza *okno)
{
	this->oknoGracza = okno;
}

void MistrzGry::setBoty(QMap<int, SztucznaInteligencja *>)
{
	this->boty = boty;
}
