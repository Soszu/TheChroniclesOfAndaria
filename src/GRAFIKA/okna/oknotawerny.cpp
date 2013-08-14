#include "oknotawerny.h"

OknoTawerny::OknoTawerny(Gracz *gracz, Plansza* plansza, QList<Zadanie *> *dostepneZadania)
{
	this->plansza = plansza;
	this->gracz = gracz;
	this->dostepneZadania = dostepneZadania;

	layoutGlowny = new QVBoxLayout(this);
	setWindowTitle("Tawerna");

	tytulWlasnychZadan = new QLabel("Twoje dotychczasowe zadania");
	listaWlasnychZadan = new QListWidget();
	listaWlasnychZadan->setToolTip(QString::fromUtf8("Lista zadań, które aktualnie wykonujesz."));

	tytulMozliwychZadan = new QLabel(QString::fromUtf8("Zadania dostępne do przyjęcia\n(możesz jednocześnie wykonywać ") +
					 QString::number(MAKSYMALNA_LICZBA_ZADAN) +
					 QString::fromUtf8(" zadań)"));
	listaMozliwychZadan = new QListWidget();
	listaMozliwychZadan->setToolTip(QString::fromUtf8("Lista zadań, które możesz przyjąć w tym miejscu."));

	wypelnijListy();

	layoutLewy = new QVBoxLayout();
	layoutLewy->addWidget(tytulWlasnychZadan);
	layoutLewy->addWidget(listaWlasnychZadan);
	layoutLewy->addWidget(tytulMozliwychZadan);
	layoutLewy->addWidget(listaMozliwychZadan);
	layoutGorny = new QHBoxLayout();
	layoutGorny->addLayout(layoutLewy);

	opisZadania = new QTextBrowser();
	opisZadania->setToolTip(QString::fromUtf8("Dokładny opis zaznaczonego zadania"));
	layoutGorny->addWidget(opisZadania);
	layoutGlowny->addLayout(layoutGorny);

	przyciskPokazCel = new QPushButton(QString::fromUtf8("Pokaz hex z celem"));
	przyciskPokazCel->setToolTip(QString::fromUtf8("Wyszczególnia hex, do którego należy się aktualnie udać, aby wykonać zadanie."));
	przyciskPokazCel->setEnabled(false);
	przyciskPrzyjmij = new QPushButton("Przyjmij");
	przyciskPrzyjmij->setToolTip(QString::fromUtf8("Zależnie od sytuacji, przycisk pozwala przyjąć lub odrzucić zaznaczone zadanie"));
	przyciskPrzyjmij->setEnabled(false);
	ok = new QPushButton("Ok");

	layoutDolny = new QHBoxLayout();
	layoutDolny->addStretch();
	layoutDolny->addWidget(przyciskPokazCel);
	layoutDolny->addWidget(przyciskPrzyjmij);
	layoutDolny->addWidget(ok);
	layoutGlowny->addLayout(layoutDolny);

	connect(listaWlasnychZadan, SIGNAL(clicked(QModelIndex)), this, SLOT(wyswietlOpisDlaWlasnych(QModelIndex)));
	connect(listaMozliwychZadan, SIGNAL(clicked(QModelIndex)), this, SLOT(wyswietlOpisDlaMozliwych(QModelIndex)));

	connect(ok, SIGNAL(clicked()), this, SLOT(close()));
	connect(przyciskPokazCel, SIGNAL(clicked()), this, SLOT(pokaz()));
	connect(przyciskPrzyjmij, SIGNAL(clicked()), this, SLOT(przyjmij()));
}

/**
 * @brief OknoTawerny::wypelnijListy	Wypełnia listy własnych i oferowanych zadań nazwami.
 */
void OknoTawerny::wypelnijListy()
{
	listaWlasnychZadan->clear();
	for(int i = 0; i < gracz->getZadania()->size(); ++i)
		listaWlasnychZadan->addItem(gracz->getKonkretneZadanie(i)->getTytul());

	listaMozliwychZadan->clear();
	for(int i = 0; i < dostepneZadania->size(); ++i)
		listaMozliwychZadan->addItem(dostepneZadania->at(i)->getTytul());
}

/**
 * @brief OknoTawerny::wyswietlOpisDlaWlasnych		Wyświetla opis dla wykonywanego zadania.
 * @param element	dane zaznaczonego elementu
 */
void OknoTawerny::wyswietlOpisDlaWlasnych(QModelIndex element)
{
	listaMozliwychZadan->setCurrentRow(-1);

	Zadanie* zadanie = gracz->getKonkretneZadanie(element.row());
	ostatnioWyswietlone = zadanie;

	przyciskPokazCel->setEnabled(true);
	przyciskPrzyjmij->setEnabled(true);
	przyciskPrzyjmij->setText(QString::fromUtf8("Odrzuć"));

	wygenerujOpis(zadanie, opisZadania);
}

/**
 * @brief OknoTawerny::wyswietlOpisDlaMozliwych		Wyświetla opis dla zadania oferowanego.
 * @param element	dane zaznaczonego elementu
 */
void OknoTawerny::wyswietlOpisDlaMozliwych(QModelIndex element)
{
	listaWlasnychZadan->setCurrentRow(-1);

	Zadanie* zadanie = dostepneZadania->at(element.row());
	ostatnioWyswietlone = zadanie;

	przyciskPokazCel->setEnabled(true);
	bool czyMaks = gracz->getZadania()->size() == MAKSYMALNA_LICZBA_ZADAN;
	bool czyJuzJest;
	for(int i = 0; i < gracz->getZadania()->size(); ++i)
		if(zadanie->getId() == gracz->getKonkretneZadanie(i)->getId())
			czyJuzJest = true;
	przyciskPrzyjmij->setEnabled(!czyMaks && !czyJuzJest);
	przyciskPrzyjmij->setText(QString::fromUtf8("Przyjmij"));

	wygenerujOpis(zadanie, opisZadania);
}

/**
 * @brief OknoTawerny::przyjmij		Zależnie od zaznaczenia przyjmuje oferowane zadanie albo odrzuca jedno z podjętych
 */
void OknoTawerny::przyjmij()
{
	if(przyciskPrzyjmij->text() == "Przyjmij")
	{
		int indeks = listaMozliwychZadan->currentRow();

		gracz->getZadania()->push_back(new Zadanie(dostepneZadania->at(indeks)));
		gracz->getKonkretneZadanie(gracz->getZadania()->size() - 1)->setZeceniodawca(gracz->getPozycja());
		dostepneZadania->removeAt(indeks);
	}
	else
	{
		Zadanie* zad = gracz->getKonkretneZadanie(listaWlasnychZadan->currentRow());
		gracz->usunKonkretneZadanie(zad->getId());
	}
	wypelnijListy();
	przyciskPrzyjmij->setEnabled(false);
	przyciskPokazCel->setEnabled(false);
qDebug() <<gracz->getZadania()->back()->getCzyWykonanoCzesc();
}

/**
 * @brief OknoTawerny::pokaz	Wysyła do planszy żądanie podświetlenia przycisku.
 */
void OknoTawerny::pokaz()
{
	plansza->pokazHex(ostatnioWyswietlone->getPoleCelu());
}
