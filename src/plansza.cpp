#include "plansza.h"

Plansza::Plansza(CyklGry* cykl)
{
	this->cyklGry = cykl;

	graRozpoczeta = false;
	pozycjeGraczy = new QList<QPair<QColor, IDPola> >;
	pola = NULL;
	ParserUkladu pu(this);
	if(pu.bladWczytywania())
	{
		cyklGry->wystapilBlad(QString::fromUtf8("Wystąpił błąd przy wczytywaniu ustawienia planszy\n\n") + pu.trescBledu, blad_parsera_ustawienia_planszy);
		return;
	}
	qDebug() << QString::fromUtf8("Ustawienie planszy wczytano poprawnie");
}

Plansza::~Plansza()
{
	delete pozycjeGraczy;
	if(pola != NULL)
	{
		for(int i = 0; i < pola->size(); ++i)
			delete pola->at(i);
		delete pola;
	}
}

void Plansza::setObszarPlanszy(ObszarPlanszy *obszar)
{
	this->obszarPlanszy = obszar;
}

void Plansza::setMistrzGry(MistrzGry *mistrz)
{
	this->mistrzGry = mistrz;
}

void Plansza::setGracze(QList<Gracz *> *gracze)
{
	this->gracze = gracze;
}

/**
 * @brief Plansza::ruszGracza Rusza gracza podanego jako parametr. Rysuje planszę, jeśli jeszcze tego nie zrobiono.
 * @param gracz
 */
void Plansza::ruszGracza(Gracz *gracz, int indeks)
{
	qDebug() <<"Plansza obsluguje gracza: " <<gracz->getNazwa();
	this->indeksAktualnego = indeks;
	this->aktualnyGracz = gracz;
	if(!graRozpoczeta)
	{
		obszarPlanszy->narysujPlansze(pola, szerokoscPlanszy, wysokoscPlanszy, spiszPozycje()); //wykona się tylko raz
		graRozpoczeta = true;
	}
	graczWykonalRuch = false;
	ustalOsiagalne(gracz);
	obszarPlanszy->podswietl(pokazOsiagalne());
}


void Plansza::kliknietoHex(IDPola id)
{
	qDebug() <<"kliknieto: " <<id.x <<" "<<id.y;
	if(!graczWykonalRuch && poprzednie.contains(IDToIndeks(id)))
	{
		aktualnyGracz->setPozycja(id);
		obszarPlanszy->wykonajRuch(odtworzDroge(id), indeksAktualnego);
		mistrzGry->wykonanoRuch();
		graczWykonalRuch = true;
	}
	if(!poprzednie.contains(IDToIndeks(id)))
		qDebug() <<"nieosiągalny";
}

/**
 * @brief Plansza::ustalOsiagalne	Ustala pola osiągalne dla podanego gracza.
 *					Zapisuje wynik na prywatnej liście "osiągalne".
 * @param gracz
 */
void Plansza::ustalOsiagalne(Gracz *gracz)
{
	QQueue<QPair<int, IDPola> >doPrzejrzenia;

	poprzednie.clear();
	osiagalne.clear();
	if(graczWykonalRuch)
		return;

	doPrzejrzenia.push_back(qMakePair(0, gracz->getPozycja() ));

	while(!doPrzejrzenia.empty())
	{
		QPair<int, IDPola> badany = doPrzejrzenia.front();
		doPrzejrzenia.pop_front();
		QList<IDPola> najblizsze = sasiedniePola(badany.second);
		for(int i = 0; i < najblizsze.size(); ++i)
		{
			int indeks = IDToIndeks(najblizsze[i]);
			int koszt = badany.first + pola->at(indeks)->getWspolczynnik();
			if(koszt > gracz->getPunktyRuchu() || poprzednie.contains(indeks))
				continue;
			else
			{
				doPrzejrzenia.push_back(qMakePair(koszt, indeksToID(indeks)));
				poprzednie.insert(indeks, badany.second);
			}
		}
	}

	poprzednie.remove(IDToIndeks(gracz->getPozycja()));
	QList<int> indeksyOsiagalnych = poprzednie.keys();
	for (int i = 0; i < indeksyOsiagalnych.size(); ++i)
		osiagalne.push_back(indeksToID(indeksyOsiagalnych[i]));
}

/**
 * @brief Plansza::uaktualnijOsiagalne	Metoda wywoływana z zewnątrz.
 *					Uaktualnia i podświetla na nowo osiągalne pola.
 */
void Plansza::uaktualnijOsiagalne()
{
	ustalOsiagalne(aktualnyGracz);
	obszarPlanszy->podswietl(pokazOsiagalne());
}

void Plansza::wykreslGracza(int indeks)
{
	obszarPlanszy->usunPionek(indeks);
}

/**
 * @brief Plansza::pokazPole	Pokazuje na życzenie pole spod podanego indeksu.
 * @param pole		Indeks pola do pokazania
 * @return Kopia	pola z podanego indeksu
 */
Pole*	 Plansza::pokazPole(IDPola pole)
{
	return pola->at(IDToIndeks(pole));
}

/**
 * @brief Plansza::czyTrwaAnimacja	Podaje informację, czy ruch jest własnie animowany.
 * @return	Jeśli ruch jest właśnie animowany, to zwraca true, w.p.p false.
 */
bool Plansza::czyTrwaAnimacja()
{
	return obszarPlanszy->animacjaTrwa();
}

/**
 * @brief Plansza::pokazOsiagalne	Pokazuje listę osiągalnych pól dla aktualnego gracza.
 * @return	Zwraca kopię listy osiągalnych pól. (Żeby nie można jej było podmienić)
 */
QList<IDPola> Plansza::pokazOsiagalne()
{
	return osiagalne;
}

/**
 * @brief Plansza::odtworzDroge		Odtwarza drogę od osiągalnego hexa do pozycji aktualnego gracza.
 * @param pole
 * @return
 */
QList<IDPola> Plansza::odtworzDroge(IDPola pole)
{
	QList<IDPola> droga;
	IDPola aktualny = pole;
	droga.push_back(aktualny);

	while(poprzednie.contains(IDToIndeks(aktualny)))
	{
		aktualny = poprzednie[IDToIndeks(aktualny)];
		droga.push_back(aktualny);
	}
	droga.pop_back(); //usuwam hex na którym teraz znajduje się pionek, a który został dodany

	return droga;
}

/**
 * @brief Plansza::spiszPozycje		Spisuje pozycje graczy jako listę par <kolor, pozycja>.
 *					Zapamiętuje wynik w zmiennej pozycjeGraczy.
 * @return	Zwraca adres do listy z wynikiem.
 */
QList<QPair<QColor, IDPola> > *Plansza::spiszPozycje()
{
	pozycjeGraczy->clear();

	for(int i = 0; i < gracze->size(); ++i )
		pozycjeGraczy->push_back(QPair<QColor, IDPola>(gracze->at(i)->getKolor(),gracze->at(i)->getPozycja()));

	return pozycjeGraczy;
}

/**
 * @brief Plansza::ruchAI	Obsługuje decyzję AI o ruchu.
 * @param pole		pole na które chce się ruszyć AI
 */
void Plansza::ruchAI(IDPola pole)
{
	kliknietoHex(pole);
}

/**
 * @brief Plansza::pokazHex	Przekazuje obszarowi planszy żadanie pokazania hexa o danym id.
 * @param id
 */
void Plansza::pokazHex(IDPola id)
{
	obszarPlanszy->pokazHex(IDToIndeks(id));
}

/**
 * @brief Plansza::blokujRuch	Metoda wywoływana z zewnątrz. Blokuje możliwość ruchu aktualnemu graczowi.
 */
void Plansza::blokujRuch()
{
	graczWykonalRuch = true;

	ustalOsiagalne(aktualnyGracz);
	obszarPlanszy->podswietl(pokazOsiagalne());
}

/**
 * @brief Plansza::IdToIndeks	Zamienia ID pola zapisane w 2 intach na indeks pola na liście pól czyli 1 int.
 *				Efekt uboczny zapisania ID jako 2 x int.
 * @param pole		ID pola do zamiany
 * @return		indeks pola na liście pól (numerowanie od 0)
 */
int Plansza::IDToIndeks(IDPola pole)
{
	return pole.y * szerokoscPlanszy + pole.x;
}

/**
 * @brief Plansza::indeksToID	Zamienia indeks na struct IDPola.
 * @param indeks	indeks do zamiany
 * @return		IDPola odpowiadające danemu indeksowi
 */
IDPola Plansza::indeksToID(int indeks)
{
	IDPola tmp;
	tmp.x = indeks % szerokoscPlanszy;
	tmp.y = indeks / szerokoscPlanszy;

	return tmp;
}

/**
 * @brief Plansza::sasiedniePola Zwraca listę pól sąsiadujących z zadanym polem.
 * @param pole
 * @return
 */
QList<IDPola> Plansza::sasiedniePola(IDPola pole)
{
	QList<IDPola> wynik;
	IDPola tmp = pole;
	if(pole.x > 0)
	{
		tmp.x = pole.x - 1;
			wynik.push_back(tmp);
	}
	if(pole.x < szerokoscPlanszy - 1)
	{
		tmp.x = pole.x + 1;
			wynik.push_back(tmp);
	}
	tmp.x = pole.x;

	if(pole.y < wysokoscPlanszy - 1)
	{
		tmp.y = pole.y + 1;
		wynik.push_back(tmp);
		if(pole.y % 2 == 1)
		{
			if(pole.x < szerokoscPlanszy - 1)
			{
				tmp.x = pole.x + 1;
				wynik.push_back(tmp);
			}
		}
		else
			if(pole.x > 0)
			{
				tmp.x = pole.x - 1;
				wynik.push_back(tmp);
			}
	}
	tmp.x = pole.x;
	if(pole.y > 0)
	{
		tmp.y = pole.y - 1;
		wynik.push_back(tmp);
		if(pole.y % 2 == 1)
		{
			if(pole.x < szerokoscPlanszy - 1)
			{
				tmp.x = pole.x + 1;
				wynik.push_back(tmp);
			}
		}
		else
			if(pole.x > 0)
			{
				tmp.x = pole.x - 1;
				wynik.push_back(tmp);
			}
	}

	return wynik;
}
