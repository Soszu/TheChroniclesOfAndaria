#include "plansza.h"

Plansza::Plansza()
{
	ParserUkladu pu(this);
	if(pu.bladWczytywania())
	{
		qDebug() << QString::fromUtf8("Wystąpił błąd przy wczytywaniu ustawienia planszy");
		//zrób coś
		return;
	}
	qDebug() << QString::fromUtf8("Ustawienie planszy wczytano poprawnie");
	graRozpoczeta = false;
	pozycjeGraczy = new QList<QPair<QColor, IDPola> >;
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
	if(!graczWykonalRuch) //i osiągalny
	{
		aktualnyGracz->setPozycja(id);
		obszarPlanszy->wykonajRuch(odtworzDroge(id), indeksAktualnego);
		mistrzGry->wykonanoRuch();
		graczWykonalRuch = true;
	}
}

void Plansza::ustalOsiagalne(Gracz *gracz)
{
	//TODO
	osiagalne.clear();
	//BFS
	//tymczasowo
	/*
	IDPola start = gracz->getPozycja();
	IDPola tmp1 = {start.x + 1, start.y};
	IDPola tmp2 = {start.x - 1, start.y};
	IDPola tmp3 = {start.x, start.y + 1};
	IDPola tmp4 = {start.x, start.y - 1};
	osiagalne->push_back(QPair<IDPola, IDPola>(tmp1, start));
	osiagalne->push_back(QPair<IDPola, IDPola>(tmp2, start));
	osiagalne->push_back(QPair<IDPola, IDPola>(tmp3, start));
	osiagalne->push_back(QPair<IDPola, IDPola>(tmp4, start));
	*/
}

QList<IDPola> Plansza::pokazOsiagalne()
{
	//TODO
	QList<IDPola> tmp;
	tmp.push_back(aktualnyGracz->getPozycja());
	return tmp;
}

QList<IDPola> Plansza::odtworzDroge(IDPola pole)
{
	//TODO
	QList<IDPola> droga;
	droga.push_back(pole);
	return droga;
}

/**
 * @brief Plansza::spiszPozycje Spisuje pozycje graczy jako listę par <kolor, pozycja>. Zapamiętuje wynik w zmiennej pozycjeGraczy.
 * @return Zwraca adres do listy z wynikiem.
 */
QList<QPair<QColor, IDPola> > *Plansza::spiszPozycje()
{
	pozycjeGraczy->clear();

	for(int i = 0; i < gracze->size(); ++i )
		pozycjeGraczy->push_back(QPair<QColor, IDPola>(gracze->at(i)->getKolor(),gracze->at(i)->getPozycja()));

	return pozycjeGraczy;
}

/**
 * @brief Plansza::ruchAI Obsługuje decyzję AI o ruchu.
 * @param pole pole na które chce się ruszyć AI
 */
void Plansza::ruchAI(IDPola pole)
{
	kliknietoHex(pole);
}
