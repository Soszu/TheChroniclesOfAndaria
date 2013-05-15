#include "cyklgry.h"

CyklGry::CyklGry()
{
	indeksAktualnego = 0;
}

/**
 * @brief CyklGry::setGracze Przyjmuje dane graczy
 * @param gracze
 */
void CyklGry::setGracze(QList<Gracz *> gracze)
{
	this->gracze = gracze;
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
	mistrzGry->ruszGracza(gracze[indeks]);
	plansza->ruszGracza(gracze[indeks]);
}

/**
 * @brief CyklGry::zakonczTure Kończy turę aktualnego gracza, wyświetla następnego
 */
void CyklGry::zakonczTure()
{
	qDebug() <<"Zakonczono ture, indeks aktualnego gracza: " <<indeksAktualnego;

	++indeksAktualnego;
	if(indeksAktualnego >= gracze.size())
		indeksAktualnego = 0;
	ruszGracza(indeksAktualnego);

}
