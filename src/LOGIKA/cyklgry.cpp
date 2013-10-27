#include "cyklgry.h"

CyklGry::CyklGry(int* wynikParsowania)
{
	this->wynikParsowania = wynikParsowania;
	zrestartujZmienne();
	komunikatOBledzie = new QDialog;
}

CyklGry::~CyklGry()
{
	delete komunikatOBledzie;
	Gracz* it;
	foreach (it, gracze) {
		delete it;
	}
	QMap<int, SztucznaInteligencja*>::iterator it2;
	for (it2 = boty.begin(); it2 != boty.end(); ++it2)
		delete it2.value();
}

/**
 * @brief CyklGry::setGracze Przyjmuje dane graczy
 * @param gracze
 */
void CyklGry::setGracze(QList<Gracz *> gracze)
{
	liczbaAktywnych = gracze.size();
	this->gracze = gracze; //tu jest przekazywana przez przepisanie, bo lepiej jest, żeby lista była zapisana w cyklu.
	plansza->setGracze(&this->gracze);
	for(int i = 0; i < gracze.size(); ++i)
		if(gracze[i]->getCzyAI())
			boty.insert(i, new SztucznaInteligencja(gracze[i]));
	mistrzGry->setGracze(&this->gracze);
}

void CyklGry::setMainWindow(MainWindow *okno)
{
	this->mainWindow = okno;
}

MainWindow *CyklGry::getMainWindow()
{
	return mainWindow;
}

/**
 * @brief CyklGry::wystapilBlad	Metoda wywoływana przez Mistrza Gry lub Planszę, żeby zgłosić błąd i przerwać pracę.
 * @param komunikat	komunikat z opisem błądu który ma zostać wyświetlony
 * @param blad		numer błędu do zwrócenia przez program
 */
void CyklGry::wystapilBlad(QString komunikat, int blad)
{
	qDebug() <<komunikat;

	QMessageBox::critical(
		komunikatOBledzie,
		QString::fromUtf8("Napotkano błąd"),
		komunikat + QString::fromUtf8("\n\nNastąpi zamknięcie programu.") );

	*wynikParsowania = blad;
}

void CyklGry::setMistrzGry(MistrzGry *mistrz)
{
	this->mistrzGry = mistrz;
}

void CyklGry::setPlansza(Plansza *plansza)
{
	this->plansza = plansza;
}

QList<Gracz *> CyklGry::getGracze()
{
	return gracze;
}

/**
 * @brief CyklGry::wykreslGracza Wykreśla aktualnego gracza z listy, i sprawdza, czy nie został przypadkiem tylko 1 gracz - zwycięzca
 */
void CyklGry::wykreslAktualnego()
{
	QMessageBox::information(
		mainWindow,
		QString::fromUtf8("Przykro mi, ale ..."),
		gracze[indeksAktualnego]->getNazwa() + QString::fromUtf8(" wypadł z gry.") );

	gracze[indeksAktualnego]->setCzyAktywny(false);
	--liczbaAktywnych;

	if(liczbaAktywnych == 1)
	{
		wyznaczKolejnego();
		QMessageBox::information(
			mainWindow,
			QString::fromUtf8("Gratulacje!"),
					gracze[indeksAktualnego]->getNazwa() + QString::fromUtf8(" jest teraz jedynym żywym graczem i tym samym zwycięża.") );
		mainWindow->close();
	}
	else
		plansza->wykreslGracza(indeksAktualnego);
}

/**
 * @brief CyklGry::graczWygral	ogłasza Zwycięzcę i kończy grę.
 * @param gracz		dane zwycięzcy
 */
void CyklGry::graczWygral(Gracz *gracz)
{
	QMessageBox::information(
		mainWindow,
		QString::fromUtf8("Gratulacje!"),
		gracz->getNazwa() + QString::fromUtf8(" zwyciężył.") );
	mainWindow->close();
}

/**
 * @brief CyklGry::czySpelnionyWarunekZwyciestwa	Sprawdza, czy został spełniony warunek zwycięstwa.
 * @param gracz		dane gracza, który jest sprawdzany
 * @return	true jeśli warunek jest spełniony, w p.p. false
 */
bool CyklGry::czySpelnionyWarunekZwyciestwa(Gracz *gracz)
{
	int wymaksowaneReputacje = 0;
	for(int i = 0; i < LICZBA_KROLESTW; ++i)
		if(gracz->getReputacja()[i] == MAX_REPUTACJA)
			++wymaksowaneReputacje;

	return gracz->getPoziom() == MAKSYMALNY_POZIOM && wymaksowaneReputacje >= LICZBA_POTRZEBNYCH_REPUTACJI;
}

/**
 * @brief CyklGry::rozpocznij	Rozpoczyna rozgrywkę przez wykonanie ruchu pierwszego gracza
 */
void CyklGry::rozpocznij()
{
	zrestartujZmienne();
	qDebug() <<"Liczba graczy: " <<gracze.size();
	mainWindow->zmienDate(dzien, tydzien);
	mistrzGry->rozpocznij();
	plansza->rozpocznij();
	ruszGracza(indeksAktualnego);
}

/**
 * @brief CyklGry::ruszGracza	Przekazuje mistrzowi gry i planszy, że zaczyna się ruch gracza o zadanym indeksie
 * @param indeks	indeks poruszanego gracza na liście graczy
 */
void CyklGry::ruszGracza(int indeks)
{
	qDebug() << "Cykl Gry rusza gracza o indeksie: " <<indeksAktualnego;
	plansza->ruszGracza(indeks);
	mistrzGry->ruszGracza(indeks);
}

/**
 * @brief CyklGry::wyznaczKolejnego	Przestawia indeksAktualnego na kolejnego aktywnego gracza.
 */
void CyklGry::wyznaczKolejnego()
{
	do
	{
		++indeksAktualnego;
		if(indeksAktualnego >= gracze.size())
		{
			nowyDzien();
			indeksAktualnego = 0;
		}
	}
	while(!gracze[indeksAktualnego]->getCzyAktywny());
}

void CyklGry::nowyDzien()
{
	if(dzien < LICZBA_DNI_TYGODNIA)
		++dzien;
	else
	{
		dzien = 1;
		++tydzien;
		mistrzGry->nowyTydzien();
	}
	mainWindow->zmienDate(dzien, tydzien);
}

/**
 * @brief CyklGry::zakonczTure Kończy turę aktualnego gracza, sprawdza, czy spełnił warunek zwycięstwa, jeśli nie wyświetla następnego
 */
void CyklGry::zakonczTure()
{
	if(czySpelnionyWarunekZwyciestwa(gracze[indeksAktualnego]))
		graczWygral(gracze[indeksAktualnego]);

	wyznaczKolejnego();

	ruszGracza(indeksAktualnego);
}

void CyklGry::zrestartujZmienne()
{
	tydzien = 1;
	dzien = 1;
	indeksAktualnego = 0;
}
