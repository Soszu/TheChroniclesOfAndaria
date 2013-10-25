﻿#include "mistrzgry.h"

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
	} else if(zadania.size() < LICZBA_ZADAN_W_TAWERNIE)
	{
		cyklGry->wystapilBlad(QString::fromUtf8("Wczytano za mało zadań.\n\n"), blad_liczby_zadan);
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

	QMap<int, QList<Zadanie*>* >::iterator it7;
	for(it7 = zadaniaWMiastach.begin(); it7 != zadaniaWMiastach.end(); ++it7)
		delete it7.value();

	QMap<int, QList<Przedmiot*>* >::iterator it8;
	for(it8 = towaryWMiastach.begin(); it8 != towaryWMiastach.end(); ++it8)
		delete it8.value();
}

/**
 * @brief MistrzGry::ruszGracza Wykonuje wymagane operacje dla momentu, gdy rozpoczyna się tura kolejnego gracza
 * @param gracz aktualny gracz
 */
void MistrzGry::ruszGracza(Gracz *gracz, int indeks)
{
	qDebug() <<"Mistrz gry obsluguje gracza: " <<gracz->getNazwa();

	aktualnyGracz = gracz;
	realizowaneZadanie = NULL;

	//regeneracja
	gracz->setZdrowieAktualne(qMin(gracz->getZdrowieMaks(), gracz->getZdrowieAktualne() + gracz->getRegeneracja()));

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

	if(zajmowanePole->getCzyPoleZMiastem())
	{
		akcje.push_back(bazar);
		akcje.push_back(tawerna);
		akcje.push_back(uzdrowiciel);
	}

	if(zajmowanePole->getCzyPoleZPrzeciwnikiem() && !gracz->getOstatnioWalczyl())
	{
		akcje.push_back(przeciwnikLatwy);
		//grupy przeciwnikow są numerowane od 1.
		int grupaPrzeciwnika = (gracz->getPoziom() + 1) / 2;
		if(grupaPrzeciwnika + 1 <= LICZBA_GRUP_PRZECIWNIKOW)
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

	int* reputacja = new int[LICZBA_KROLESTW];
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
		handelNaBazarze();
		break;
	case tawerna:
		plansza->blokujRuch();
		idzDoTawerny();
		break;
	case uzdrowiciel:
		plansza->blokujRuch();
		idzDoUzdrowiciela();
		break;
	default:
		qDebug() << QString::fromUtf8("Błędna opcja");
		//TODO: assert
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
	int szansaGracza;
	int indeks = 0;
	while(gracz->getKonkretneZadanie(indeks)->getId() != id)
		++indeks;

	Zadanie* zadanie = gracz->getKonkretneZadanie(indeks);
	switch (zadanie->getRodzaj()) {
	case przynies:
		if(zadanie->getCzyWykonanoCzesc())
		{
			przydzielNagrode(gracz, zadanie->getNagroda(), false);
			gracz->usunKonkretneZadanie(id);
			panelAkcji->ustawZadania(mozliweZadania(aktualnyGracz));
			panelAkcji->wyswietl();
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
			przydzielNagrode(gracz, zadanie->getNagroda(), false);
			gracz->usunKonkretneZadanie(id);
			panelAkcji->ustawZadania(mozliweZadania(aktualnyGracz));
			panelAkcji->wyswietl();
			break;
		}
		szansaGracza = BAZOWA_SZANSA_NA_ODNALEZIENIE + gracz->getPercepcja() * BONUS_Z_PERCEPCJI;
		sukces = qrand() % 100 < szansaGracza;
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
				przydzielNagrode(gracz, zadanie->getNagroda(), true);
				gracz->usunKonkretneZadanie(id);
			}
		}
		cyklGry->zakonczTure();
		break;
	case pokonaj:
		if(zadanie->getCzyWykonanoCzesc())
		{
			przydzielNagrode(gracz, zadanie->getNagroda(), false);
			gracz->usunKonkretneZadanie(id);
			panelAkcji->ustawZadania(mozliweZadania(aktualnyGracz));
			panelAkcji->wyswietl();
		}
		else
		{
			realizowaneZadanie = zadanie;
			walka(przeciwnikZZadania);
		}
		break;
	}
}

void MistrzGry::nowyTydzien()
{
	qDebug() <<QString::fromUtf8("Rozpoczęto nowy tydzień.");
	QMap<int, QList<Przedmiot*>* >::iterator it;
	for (it = towaryWMiastach.begin(); it != towaryWMiastach.end(); ++it)
		wylosujPrzedmiotyNaBazar(it.value());
	qDebug() <<"Wylosowano przedmioty";

	QMap<int, QList<Zadanie*>* >::iterator it2;
	for (it2 = zadaniaWMiastach.begin(); it2 != zadaniaWMiastach.end(); ++it2)
	{
		Pole* zajmowanePole = plansza->pokazPole(plansza->indeksToID(it2.key()));
		wylosujZadaniaDoTawerny(it2.value(), zajmowanePole->getFrakcja());
	}
	qDebug() <<"Wylosowano zadania";
}

void MistrzGry::rozpocznij()
{
		this->miasta = plansza->getMiasta();

		for(int i = 0; i < miasta->size(); ++i)
		{
			QList<Przedmiot*>* nowa = new QList<Przedmiot*>;
			towaryWMiastach.insert(miasta->at(i), nowa);
			QList<Zadanie*>* nowa2 = new QList<Zadanie*>;
			zadaniaWMiastach.insert(miasta->at(i), nowa2);
		}

		nowyTydzien();
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
			if(realizowaneZadanie->getPrzeciwnicy()->isEmpty())
			{
				if(realizowaneZadanie->getCzyPowrot())
				{
					realizowaneZadanie->setCzyWykonanoCzesc(true);
					realizowaneZadanie->setPoleCelu(realizowaneZadanie->getZleceniodawca());
				}
				else
				{
					Nagroda* nagroda = polaczNagrody(przeciwnik->getNagroda(), realizowaneZadanie->getNagroda());
					przydzielNagrode(aktualnyGracz, nagroda, true);
					delete nagroda;
					aktualnyGracz->usunKonkretneZadanie(realizowaneZadanie->getId());
					realizowaneZadanie = NULL;
					break;
				}
			}
		}
		przydzielNagrode(aktualnyGracz, przeciwnik->getNagroda(), true);
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
void MistrzGry::przydzielNagrode(Gracz *gracz, Nagroda *nagroda, bool czyKoniecTury)
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
		int suma = nagroda->getReputacja()[i] + gracz->getReputacja()[i];
		int nowaWartosc = qMin((int)MAX_REPUTACJA, suma);
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

	oknoNagrody = new OknoNagrody(aktualnyGracz, nagroda, przydzielonePrzedmioty, cyklGry, czyKoniecTury);
	oknoNagrody->setWindowModality(Qt::ApplicationModal);
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
	Przeciwnik* przeciwnik = NULL;

	switch(opcja) {
	case przeciwnikLatwy:
		przeciwnik = losujPrzeciwnika(poziomLatwy);
		aktualnyGracz->setOstatnioWalczyl(true);
		break;
	case przeciwnikTrudny:
		przeciwnik = losujPrzeciwnika(poziomLatwy + 1);
		aktualnyGracz->setOstatnioWalczyl(true);
		break;
	case przeciwnikZZadania:
		przeciwnik = realizowaneZadanie->getPrzeciwnicy()->front();
	default:
		qDebug() << QString::fromUtf8("Błędna opcja");
		//TODO: assert
	}

	oknoWalki = new Walka(aktualnyGracz, przeciwnik, this);
	oknoWalki->setWindowModality(Qt::ApplicationModal);
	oknoWalki->setAttribute(Qt::WA_DeleteOnClose);
	oknoWalki->rozpocznij();
}

/**
 * @brief MistrzGry::idzDoTawerny	Metoda losująca zadania w tawernie i wyświetlająca Okno Tawerny
 */
void MistrzGry::idzDoTawerny()
{
	int indeksPola = plansza->IDToIndeks(aktualnyGracz->getPozycja());
	oknoTawerny = new OknoTawerny(aktualnyGracz, plansza, oknoGracza, zadaniaWMiastach[indeksPola]);
	oknoTawerny->setWindowModality(Qt::ApplicationModal);
	oknoTawerny->setAttribute(Qt::WA_DeleteOnClose);
	oknoTawerny->show();
}

void MistrzGry::wylosujZadaniaDoTawerny(QList<Zadanie *> *lista, int frakcja)
{
	lista->clear();
	for(int i = 0; i < LICZBA_ZADAN_W_TAWERNIE; ++i)
	{
		int los = qrand() % zadania.size() + 1;
//		QMap<int, Zadanie*>::iterator iter = zadania.begin();
//		for (int j = 0; j < los; ++j)
//			++iter;
		if(lista->contains(zadania[los]) || (zadania[los]->getFrakcja() != frakcja && zadania[los]->getFrakcja() != -1))
			--i;
		else
			lista->push_back(zadania[los]);
	}
}

/**
 * @brief MistrzGry::handelNaBazarze	Metoda losująca przedmioty na bazarze i wyświetlająca Okno Bazaru
 */
void MistrzGry::handelNaBazarze()
{
	int indeksPola = plansza->IDToIndeks(aktualnyGracz->getPozycja());
	oknoBazaru = new OknoBazaru(aktualnyGracz, oknoGracza, towaryWMiastach[indeksPola]);
	oknoBazaru->setWindowModality(Qt::ApplicationModal);
	oknoBazaru->setAttribute(Qt::WA_DeleteOnClose);
	oknoBazaru->show();
}

void MistrzGry::wylosujPrzedmiotyNaBazar(QList<Przedmiot *> *lista)
{
	lista->clear();
	for(int i = 0; i < LICZBA_PRZEDMIOTOW_NA_BAZARZE; ++i)
	{
		int los = qrand() % przedmioty.size();

		//TODO: zmiana sposobu zarządzania miksturami
		if(przedmioty[los]->getRodzaj() == mikstura || lista->contains(przedmioty[los]))
			--i;
		else
			lista->push_back(przedmioty[los]);
	}
}

void MistrzGry::idzDoUzdrowiciela()
{
	oknoUzdrowiciela = new OknoUzdrowiciela(aktualnyGracz, oknoGracza);
	oknoUzdrowiciela->setWindowModality(Qt::ApplicationModal);
	oknoUzdrowiciela->setAttribute(Qt::WA_DeleteOnClose);
	oknoUzdrowiciela->show();
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
