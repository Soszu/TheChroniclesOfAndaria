#include "oknozadania.h"

OknoZadania::OknoZadania(Gracz *gracz, Plansza *plansza)
{
	this->plansza = plansza;
	this->gracz = gracz;

	layoutGlowny = new QVBoxLayout(this);
	setWindowTitle("Twoje zadania");

	listaZadan = new QListWidget();
	listaZadan->setToolTip(QString::fromUtf8("Lista zadań, które aktualnie wykonujesz."));

	for(int i = 0; i < gracz->getZadania()->size(); ++i)
		listaZadan->addItem(gracz->getKonkretneZadanie(i)->getTytul());

	layoutGorny = new QHBoxLayout();
	layoutGorny->addWidget(listaZadan);

	opisZadania = new QTextBrowser();
	opisZadania->setToolTip(QString::fromUtf8("Dokładny opis zaznaczonego zadania");
	layoutGorny->addWidget(opisZadania);
	layoutGlowny->addLayout(layoutGorny);

	przyciskPokazCel = new QPushButton(QString::fromUtf8("Pokaz hex z celem"));
	przyciskPrzyjmij->setToolTip(QString::fromUtf8("Zależnie od sytuacji, przycisk pozwala przyjąć lub odrzucić zaznaczone zadanie"));
	przyciskPokazCel->setEnabled(false);
	ok = new QPushButton("Ok");

	layoutDolny = new QHBoxLayout();
	layoutDolny->addStretch();
	layoutDolny->addWidget(przyciskPokazCel);
	layoutDolny->addWidget(ok);
	layoutGlowny->addLayout(layoutDolny);

	connect(listaZadan, SIGNAL(clicked(QModelIndex)), this, SLOT(wyswietlOpis(QModelIndex)));

	connect(ok, SIGNAL(clicked()), this, SLOT(close()));
	connect(przyciskPokazCel, SIGNAL(clicked()), this, SLOT(pokaz()));
}

/**
 * @brief OknoZadania::wyswietlOpis	Wyświetla opis podjętego zadania.
 * @param element	dane zaznaczonego elementu
 */
void OknoZadania::wyswietlOpis(QModelIndex element)
{
	przyciskPokazCel->setEnabled(true);
	Zadanie* zadanie = gracz->getKonkretneZadanie(element.row());
	wygenerujOpis(zadanie, opisZadania);
}

/**
 * @brief OknoZadania::pokaz	Wysyła planszy żądanie podświetlenia konkretnego hexa.
 */
void OknoZadania::pokaz()
{
	Zadanie* zadanie = gracz->getKonkretneZadanie(listaZadan->currentRow());
	plansza->pokazHex(zadanie->getPoleCelu());
}
