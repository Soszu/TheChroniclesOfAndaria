#include "oknozadania.h"

OknoZadania::OknoZadania(Gracz *gracz, Plansza *plansza)
{
	this->plansza = plansza;
	this->gracz = gracz;

	layoutGlowny = new QVBoxLayout(this);
	setWindowTitle("Twoje zadania");

	listaZadan = new QListWidget();

	for(int i = 0; i < gracz->getZadania()->size(); ++i)
		listaZadan->addItem(gracz->getZadania()->at(i)->getTytul());

	layoutGorny = new QHBoxLayout();
	layoutGorny->addWidget(listaZadan);

	opisZadania = new QTextBrowser();
	layoutGorny->addWidget(opisZadania);
	layoutGlowny->addLayout(layoutGorny);

	przyciskPokazCel = new QPushButton(QString::fromUtf8("Pokaz hex z celem"));
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

void OknoZadania::wyswietlOpis(QModelIndex element)
{
	przyciskPokazCel->setEnabled(true);
	Zadanie* zadanie = gracz->getZadania()->at(element.row());
	wygenerujOpis(zadanie, opisZadania);
}

void OknoZadania::pokaz()
{
	Zadanie* zadanie = gracz->getZadania()->at(listaZadan->currentRow());
	plansza->pokazHex(zadanie->getPoleCelu());
}
