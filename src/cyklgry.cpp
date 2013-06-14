#include "cyklgry.h"

CyklGry::CyklGry(int* wynikParsowania)
{
	this->wynikParsowania = wynikParsowania;
	indeksAktualnego = 0;
	komunikatOBledzie = new QDialog;
}

CyklGry::~CyklGry()
{
	delete komunikatOBledzie;
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

void CyklGry::setMainWindow(QMainWindow *okno)
{
	this->mainWindow = okno;
}

void CyklGry::wystapilBlad(QString komunikat, int blad)
{
	qDebug() <<komunikat;

	QMessageBox::critical(
		komunikatOBledzie,
		QString::fromUtf8("Napotkano błąd"),
		komunikat + QString::fromUtf8("\n\nNastąpi zamknięcie programu.") );

	*wynikParsowania = blad;
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

void CyklGry::wykreslGracza(Gracz *gracz)
{
	QMessageBox::information(
		mainWindow,
		QString::fromUtf8("Przykro mi, ale ..."),
		gracz->getNazwa() + QString::fromUtf8(" wypadł z gry.") );

	gracze.removeAt(indeksAktualnego);

	if(gracze.size() == 1)
	{
		QMessageBox::information(
			mainWindow,
			QString::fromUtf8("Gratulacje!"),
			gracze.first()->getNazwa() + QString::fromUtf8(" jest teraz jedynym żywym graczem i tym samym zwycięża.") );
		mainWindow->close();
	}

}

void CyklGry::graczWygral(Gracz *gracz)
{
	QMessageBox::information(
		mainWindow,
		QString::fromUtf8("Gratulacje!"),
		gracz->getNazwa() + QString::fromUtf8(" zwyciężył.") );
	mainWindow->close();
}

bool CyklGry::czySpelnionyWarunekZwyciestwa(Gracz *gracz)
{
	int wymaksowaneReputacje = 0;
	for(int i = 0; i < LICZBA_KROLESTW; ++i)
		if(gracz->getReputacja()[i] == MAX_REPUTACJA)
			++wymaksowaneReputacje;

	if(gracz->getPoziom() == MAKSYMALNY_POZIOM && wymaksowaneReputacje >= LICZBA_POTRZEBNYCH_REPUTACJI)
		return true;

}

/**
 * @brief CyklGry::rozpocznij Rozpoczyna rozgrywkę przez wykonanie ruchu pierwszego gracza
 */
void CyklGry::rozpocznij()
{
	qDebug() <<"Liczba graczy: " <<gracze.size();
	ruszGracza(indeksAktualnego);
}

/**
 * @brief CyklGry::ruszGracza
 * @param indeks
 */
void CyklGry::ruszGracza(int indeks)
{
	qDebug() << "Cykl Gry rusza gracza o indeksie: " <<indeksAktualnego;
	plansza->ruszGracza(gracze[indeks], indeks);
	mistrzGry->ruszGracza(gracze[indeks]);
}

/**
 * @brief CyklGry::zakonczTure Kończy turę aktualnego gracza, wyświetla następnego
 */
void CyklGry::zakonczTure()
{
	if(czySpelnionyWarunekZwyciestwa(gracze[indeksAktualnego]))
		graczWygral(gracze[indeksAktualnego]);

	++indeksAktualnego;
	if(indeksAktualnego >= gracze.size())
		indeksAktualnego = 0;
	ruszGracza(indeksAktualnego);
}
