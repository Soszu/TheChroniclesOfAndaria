#include "oknonowejgry.h"

OknoNowejGry::OknoNowejGry(QWidget *parent) : QDialog(parent)
{
	komunikat = new QMessageBox(this);
	komunikat->setWindowTitle(QString::fromUtf8("Błąd"));

	this->setWindowTitle("Ustalanie graczy");
	this->setSizeGripEnabled(false);

	layoutGlowny = new QVBoxLayout(this);
	layoutGlowny->setSizeConstraint( QLayout::SetFixedSize );

	for(int i = 0; i < MAX_GRACZY; ++i)
	{
		layoutyWierszy[i] = new QHBoxLayout;
		layoutNaWierszeWyboru.addLayout(layoutyWierszy[i]);
	}

	dodajGracza = new QPushButton("Dodaj gracza", this);
	dodajGracza->setToolTip("Dodaj kolejnego gracza do rozgrywki.<br>"
				"Limit to 8 graczy.");
	connect(dodajGracza, SIGNAL(clicked()),this,SLOT(dodajWiersz()));

	usunGracza = new QPushButton(QString::fromUtf8("Usuń gracza"), this);
	usunGracza->setToolTip(QString::fromUtf8("Usun ostatniego gracza.<br>"
						 "Musi być conajmniej 2 graczy."));
	connect(usunGracza, SIGNAL(clicked()),this,SLOT(usunWiersz()));

	anuluj = new QPushButton("Anuluj", this);
	anuluj->setToolTip(QString::fromUtf8("Anuluj wpisywanie graczy i wyjdź z programu."));
	connect(anuluj, SIGNAL(clicked()), this, SLOT(close()));

	ok = new QPushButton("OK", this);
	ok->setToolTip(QString::fromUtf8("Zatwierdź ustawienia i rozpocznij rozgrywkę."));
	connect(ok, SIGNAL(clicked()), this, SLOT(przekazDane()));

	layoutNaPrzyciski.addWidget(dodajGracza);
	layoutNaPrzyciski.addWidget(usunGracza);
	layoutNaPrzyciski.addStretch();
	layoutNaPrzyciski.addWidget(anuluj);
	layoutNaPrzyciski.addWidget(ok);

	liczbaGraczy = MIN_GRACZY;

	for(int i = 0; i < liczbaGraczy; ++i)
	{
		wierszWyboru tmp;
		wypelnij(&tmp, i);
		gracze.push_back(tmp);

	}

	layoutGlowny->addLayout(&layoutNaWierszeWyboru);
	layoutGlowny->addStretch();
	layoutGlowny->addLayout(&layoutNaPrzyciski);

}

OknoNowejGry::~OknoNowejGry()
{
	while(!gracze.empty())
	{
		delete gracze.back().nazwa;
		delete gracze.back().klasa;
		delete gracze.back().rasa;
		delete gracze.back().kolor;
		delete gracze.back().ai;

		gracze.pop_back();
	}
}

void OknoNowejGry::setCyklGry(CyklGry *cykl)
{
	this->cyklGry = cykl;
}

void OknoNowejGry::setMainWindow(QMainWindow *mainWindow)
{
	this->mainWindow = mainWindow;
}

/**
 * @brief OknoNowejGry::wypelnij Wypełnia zadany wiersz w formularzu opcjami do wyboru.
 * @param wiersz struct ze wskaźnikami na elementy do wypełnienia
 * @param numer numer aktualnego wiersza
 */
void OknoNowejGry::wypelnij(OknoNowejGry::wierszWyboru *wiersz, int numer)
{
	wiersz->nazwa = new QLineEdit("Gracz"+QString::number(numer + 1));
	wiersz->nazwa->setToolTip(QString::fromUtf8("Wpisz nazwę postaci.<br>"
						    "Nie więcej niż 20 znaków."));
	wiersz->rasa = new QComboBox();
	wiersz->rasa->setToolTip(QString::fromUtf8("Wybierz rasę postaci."));
	wiersz->klasa = new QComboBox();
	wiersz->klasa->setToolTip(QString::fromUtf8("Wybierz klasę postaci."));
	wiersz->kolor = new QComboBox();
	wiersz->kolor->setToolTip(QString::fromUtf8("Wybierz kolor pionka."));
	wiersz->ai = new QCheckBox();
	wiersz->ai->setToolTip(QString::fromUtf8("Czy ruchami gracza ma sterować komputer?"));

	for(int i = 0; i < LICZBA_RAS; ++i)
		wiersz->rasa->addItem(RASY[i]);

	for(int i = 0; i < LICZBA_KLAS; ++i)
		wiersz->klasa->addItem(KLASY[i]);

	for(int i = 0; i < LICZBA_MOZLIWYCH_KOLOROW; ++i)
		wiersz->kolor->addItem(MOZLIWE_KOLORY[i]);

	wiersz->kolor->setCurrentIndex(numer);

	wiersz->ai->setText("Komputer?");

	layoutyWierszy[numer]->addWidget(wiersz->nazwa);
	layoutyWierszy[numer]->addWidget(wiersz->rasa);
	layoutyWierszy[numer]->addWidget(wiersz->klasa);
	layoutyWierszy[numer]->addWidget(wiersz->kolor);
	layoutyWierszy[numer]->addWidget(wiersz->ai);
}

/**
 * @brief OknoNowejGry::przekazDane Sprawdza poprawnośc danych, przepisuje dane z formularza i wypycha je dalej
 */
void OknoNowejGry::przekazDane()
{
	for(int i = 0; i < liczbaGraczy; ++i) //czy poprawne
	{
		if(gracze[i].nazwa->text().size() == 0)
		{
			komunikat->setText(QString::fromUtf8("Nazwa conajmniej jednego z graczy nie została wpisana poprawnie."));
			komunikat->show();
			return;
		}
		if(gracze[i].nazwa->text().size() > MAKSYMALNA_DLUGOSC_NAZWY)
		{
			komunikat->setText(QString::fromUtf8("Nazwa conajmniej jednego z graczy jest za długa. Limit to ") + QString::number(MAKSYMALNA_DLUGOSC_NAZWY)+ QString::fromUtf8("znaków."));
			komunikat->show();
			return;
		}
		for(int j = i + 1; j < liczbaGraczy; ++j)
			if(gracze[i].kolor->currentText() == gracze[j].kolor->currentText())
			{
				komunikat->setText(QString::fromUtf8("Conajmniej jeden kolor się powtarza."));
				komunikat->show();
				return;
			}
	}

	QList<Gracz*> dane;

	for(int i = 0; i < liczbaGraczy; ++i ){
		dane.push_back(new Gracz(gracze[i].nazwa->text(),
					 (Rasa)gracze[i].rasa->currentIndex(),
					 (Klasa)gracze[i].klasa->currentIndex(),
					 KOLORY[gracze[i].kolor->currentIndex()],
					 gracze[i].ai->checkState()));
	}
	//korzystam tutaj z faktu, że pola w przyciskach są w takiej kolejności jak w tablicy,
	//a tam, są w takiej kolejności jak w enumach

	cyklGry->setGracze(dane);
	cyklGry->rozpocznij();
	mainWindow->showMaximized();
	this->close();
}

/**
 * @brief OknoNowejGry::dodajWiersz Dodaje na końcu wiersz do wprowadzenia danych gracza
 */
void OknoNowejGry::dodajWiersz()
{
	if(liczbaGraczy >= MAX_GRACZY)
		return;

	wierszWyboru tmp;
	wypelnij(&tmp, liczbaGraczy);
	gracze.push_back(tmp);
	++liczbaGraczy;

}

/**
 * @brief OknoNowejGry::usunWiersz Usuwa ostatni wiersz z danymi gracza.
 */
void OknoNowejGry::usunWiersz()
{
	if(liczbaGraczy <= MIN_GRACZY)
		return;

	--liczbaGraczy;
	wierszWyboru tmp = gracze.back();

	layoutyWierszy[liczbaGraczy]->removeWidget(tmp.nazwa);
	layoutyWierszy[liczbaGraczy]->removeWidget(tmp.rasa);
	layoutyWierszy[liczbaGraczy]->removeWidget(tmp.klasa);
	layoutyWierszy[liczbaGraczy]->removeWidget(tmp.kolor);
	layoutyWierszy[liczbaGraczy]->removeWidget(tmp.ai);

	delete tmp.nazwa;
	delete tmp.klasa;
	delete tmp.rasa;
	delete tmp.kolor;
	delete tmp.ai;

	gracze.pop_back();
}
