#include "cyklgry.h"

CyklGry::CyklGry()
{
	indeksAktualnego = 0;
}

CyklGry::~CyklGry()
{
	Gracz* it;
	foreach (it, gracze) {
		delete it;
	}
}

/**
 * @brief CyklGry::setGracze Przyjmuje dane graczy
 * @param gracze
 */
void CyklGry::setGracze(QList<Gracz *> gracze)
{
	this->gracze = gracze; //tu jest przekazywana przez przepisanie, bo lepiej jest, żeby lista była zapisana w cyklu.
	plansza->setGracze(&this->gracze);
}

void CyklGry::wystapilBlad(QString komunikat)
{
	qDebug() <<komunikat;
	//zakonczGre(); zakoncz Gre -> koniec(1), wystapilBlad -> koniec(0)
}

/**
 * @brief CyklGry::setMistrzGry Ustawia mistrza gry
 * @param mistrz
 */
void CyklGry::setMistrzGry(MistrzGry *mistrz)
{
	this->mistrzGry = mistrz;
}

/**
 * @brief CyklGry::setPlansza Ustawia planszę.
 * @param plansza
 */
void CyklGry::setPlansza(Plansza *plansza)
{
	this->plansza = plansza;
}

/**
 * @brief CyklGry::getGracze Metoda dająca dostęp do danych graczy
 * @return
 */
QList<Gracz *> CyklGry::getGracze()
{
	return gracze;
}

/**
 * @brief CyklGry::rozpocznij Rozpoczyna rozgrywkę przez wykonanie ruchu pierwszego gracza
 */
void CyklGry::rozpocznij()
{
	qDebug() <<"Liczba graczy: " <<gracze.size();
	ruszGracza(indeksAktualnego);
}

void CyklGry::zakonczGre()
{
}

/**
 * @brief CyklGry::ruszGracza
 * @param indeks
 */
void CyklGry::ruszGracza(int indeks)
{
	qDebug() << "Cykl Gry rusza gracza o indeksie: " <<indeksAktualnego;
	mistrzGry->ruszGracza(gracze[indeks]);
	plansza->ruszGracza(gracze[indeks], indeks);
}

/**
 * @brief CyklGry::zakonczTure Kończy turę aktualnego gracza, wyświetla następnego
 */
void CyklGry::zakonczTure()
{
	++indeksAktualnego;
	if(indeksAktualnego >= gracze.size())
		indeksAktualnego = 0;
	ruszGracza(indeksAktualnego);

}
