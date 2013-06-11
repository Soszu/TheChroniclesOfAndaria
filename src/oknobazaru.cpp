#include "oknobazaru.h"

OknoBazaru::OknoBazaru(Gracz* gracz, OknoGracza *okno, QList<Przedmiot*> *towary)
{
	this->gracz = gracz;
	this->okno = okno;
	this->towary = towary;
	Ekwipunek* ekwipunek = gracz->getEkwipunek();
	QList<Przedmiot*>* plecak = ekwipunek->getPlecak();

	layoutGlowny = new QVBoxLayout(this);
	setWindowTitle("Bazar");

	listaPrzedmiotow = new QListWidget();
	for(int i = 0; i < ekwipunek->getPlecak()->size(); ++i)
		listaPrzedmiotow->addItem(plecak->at(i)->getNazwa());

	listaTowarow = new QListWidget();
	for(int i = 0; i < towary->size(); ++i)
		listaTowarow->addItem(towary->at(i)->getNazwa());

	layoutLewy = new QVBoxLayout();
	layoutLewy->addWidget(listaPrzedmiotow);
	layoutLewy->addWidget(listaTowarow);
	layoutGorny = new QHBoxLayout();
	layoutGorny->addLayout(layoutLewy);

	opisPrzedmiotu = new QTextBrowser();
	layoutGorny->addWidget(opisPrzedmiotu);
	layoutGlowny->addLayout(layoutGorny);

	przyciskZaloz = new QPushButton(QString::fromUtf8("Załóż przedmiot"));
	przyciskZaloz->setEnabled(false);
	ok = new QPushButton("Ok");

	layoutDolny = new QHBoxLayout();
//layoutDolny->addWidget(przyciskMalejMikstury);
//layoutDolny->addWidget(przyciskDuzejMikstury);
	layoutDolny->addStretch();
	layoutDolny->addWidget(przyciskZaloz);
	layoutDolny->addWidget(ok);
	layoutGlowny->addLayout(layoutDolny);

	connect(listaTowarow, SIGNAL(clicked(QModelIndex)), this, SLOT(wyswietlOpisDlaBazaru(QModelIndex)));
	connect(listaPrzedmiotow, SIGNAL(clicked(QModelIndex)), this, SLOT(wyswietlOpisDlaGracza(QModelIndex)));

//	connect(przyciskMalejMikstury, SIGNAL(clicked()), this, SLOT(uzyjMalejMikstury()));
//	connect(przyciskDuzejMikstury, SIGNAL(clicked()), this, SLOT(uzyjDuzejMikstury()));
	connect(ok, SIGNAL(clicked()), this, SLOT(close()));
	connect(przyciskZaloz, SIGNAL(clicked()), this, SLOT(zaloz()));
}

void OknoBazaru::wyswietlOpisDlaGracza(QModelIndex element)
{
	Przedmiot* rzecz = gracz->getEkwipunek()->getPlecak()->at(element.row());
	if(czyZalozony(rzecz, gracz))
		przyciskZaloz->setEnabled(false);
	else
		przyciskZaloz->setEnabled(true);

	opisPrzedmiotu->setText(wygenerujOpis(rzecz, gracz));
}

void OknoBazaru::wyswietlOpisDlaBazaru(QModelIndex element)
{
	przyciskZaloz->setEnabled(false);
	opisPrzedmiotu->setText(wygenerujOpis(towary->at(element.row()), gracz));
}

void OknoBazaru::zaloz()
{
	int aktualny = listaPrzedmiotow->currentRow();
	zalozPrzedmiot(gracz->getEkwipunek()->getPlecak()->at(aktualny), gracz);
}
