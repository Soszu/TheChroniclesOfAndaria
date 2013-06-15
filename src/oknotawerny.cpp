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

	tytulMozliwychZadan = new QLabel(QString::fromUtf8("Zadania dostępne do przyjęcia\n(możesz jednocześnie wykonywać ") +
					 QString::number(MAKSYMALNA_LICZBA_ZADAN) +
					 QString::fromUtf8(" zadań)"));
	listaMozliwychZadan = new QListWidget();

	wypelnijListy();

	layoutLewy = new QVBoxLayout();
	layoutLewy->addWidget(tytulWlasnychZadan);
	layoutLewy->addWidget(listaWlasnychZadan);
	layoutLewy->addWidget(tytulMozliwychZadan);
	layoutLewy->addWidget(listaMozliwychZadan);
	layoutGorny = new QHBoxLayout();
	layoutGorny->addLayout(layoutLewy);

	opisZadania = new QTextBrowser();
	layoutGorny->addWidget(opisZadania);
	layoutGlowny->addLayout(layoutGorny);

	przyciskPokazCel = new QPushButton(QString::fromUtf8("Pokaz hex z celem"));
	przyciskPokazCel->setEnabled(false);
	przyciskPrzyjmij = new QPushButton("Przyjmij");
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

void OknoTawerny::wypelnijListy()
{
	listaWlasnychZadan->clear();
	for(int i = 0; i < gracz->getZadania()->size(); ++i)
		listaWlasnychZadan->addItem(gracz->getKonkretneZadanie(i)->getTytul());

	listaMozliwychZadan->clear();
	for(int i = 0; i < dostepneZadania->size(); ++i)
		listaMozliwychZadan->addItem(dostepneZadania->at(i)->getTytul());
}

void OknoTawerny::wyswietlOpisDlaWlasnych(QModelIndex element)
{

	Zadanie* zadanie = gracz->getKonkretneZadanie(element.row());
	ostatnioWyswietlone = zadanie;

	przyciskPokazCel->setEnabled(true);
	przyciskPrzyjmij->setEnabled(true);
	przyciskPrzyjmij->setText(QString::fromUtf8("Odrzuć"));

	wygenerujOpis(zadanie, opisZadania);
}

void OknoTawerny::wyswietlOpisDlaMozliwych(QModelIndex element)
{
	Zadanie* zadanie = dostepneZadania->at(element.row());
	ostatnioWyswietlone = zadanie;

	przyciskPokazCel->setEnabled(true);
	bool czyMaks = gracz->getZadania()->size() == MAKSYMALNA_LICZBA_ZADAN;
	przyciskPrzyjmij->setEnabled(!czyMaks);
	przyciskPrzyjmij->setText(QString::fromUtf8("Przyjmij"));

	wygenerujOpis(zadanie, opisZadania);
}

void OknoTawerny::przyjmij()
{
	if(przyciskPrzyjmij->text() == "Przyjmij")
	{
		int indeks = listaMozliwychZadan->currentRow();

		gracz->getZadania()->push_back(*(dostepneZadania->at(indeks)));
		gracz->getKonkretneZadanie(gracz->getZadania()->size() - 1)->setZeceniodawca(gracz->getPozycja());
		dostepneZadania->removeAt(indeks);
	}
	else
		gracz->getZadania()->removeAt(listaWlasnychZadan->currentRow());
	wypelnijListy();
	przyciskPrzyjmij->setEnabled(false);
	przyciskPokazCel->setEnabled(false);
}

void OknoTawerny::pokaz()
{
	plansza->pokazHex(ostatnioWyswietlone->getPoleCelu());
}
