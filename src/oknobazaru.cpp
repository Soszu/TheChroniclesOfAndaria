#include "oknobazaru.h"

OknoBazaru::OknoBazaru(Gracz* gracz, OknoGracza *okno, QList<Przedmiot*> *towary)
{
	this->gracz = gracz;
	this->okno = okno;
	this->towary = towary;

	layoutGlowny = new QVBoxLayout(this);
	setWindowTitle("Bazar");

	tytulPrzedmiotow = new QLabel("Twoje przedmioty");
	listaPrzedmiotow = new QListWidget();
	tytulTowarow = new QLabel(QString::fromUtf8("Przedmioty dostępne na bazarze"));
	listaTowarow = new QListWidget();
	wypelnijListy();

	layoutLewy = new QVBoxLayout();
	layoutLewy->addWidget(tytulPrzedmiotow);
	layoutLewy->addWidget(listaPrzedmiotow);
	layoutLewy->addWidget(tytulTowarow);
	layoutLewy->addWidget(listaTowarow);
	layoutGorny = new QHBoxLayout();
	layoutGorny->addLayout(layoutLewy);

	opisPrzedmiotu = new QTextBrowser();
	layoutGorny->addWidget(opisPrzedmiotu);
	layoutGlowny->addLayout(layoutGorny);

	ikonaMalejMikstury = new QLabel();
	ikonaMalejMikstury->setPixmap(IKONKA_MALA_MIKSTURA_ZDROWIA);
	iloscMalychMisktur = new QLabel(QString::number(gracz->getEkwipunek()->getMalePoty()));
	przyciskMalejMikstury = new QPushButton(QString("Kup(") +
						QString::number(CENA_MALEJ_MIKSTURY) +
						QString(")"));
	przyciskMalejMikstury->setEnabled(gracz->getZloto() >= CENA_MALEJ_MIKSTURY);

	ikonaDuzejMikstury = new QLabel();
	ikonaDuzejMikstury->setPixmap(IKONKA_DUZA_MIKSTURA_ZDROWIA);
	iloscDuzychMisktur = new QLabel(QString::number(gracz->getEkwipunek()->getDuzePoty()));
	przyciskDuzejMikstury = new QPushButton(QString("Kup(") +
						QString::number(CENA_DUZEJ_MIKSTURY) +
						QString(")"));
	przyciskDuzejMikstury->setEnabled(gracz->getZloto() >= CENA_DUZEJ_MIKSTURY);

	przyciskKup = new QPushButton();
	przyciskKup->setVisible(false);
	przyciskZaloz = new QPushButton();
	przyciskZaloz->setVisible(false);
	ok = new QPushButton("Ok");

	layoutDolny = new QHBoxLayout();
	layoutDolny->addWidget(ikonaMalejMikstury);
	layoutDolny->addWidget(iloscMalychMisktur);
	layoutDolny->addWidget(przyciskMalejMikstury);
	layoutDolny->addWidget(ikonaDuzejMikstury);
	layoutDolny->addWidget(iloscDuzychMisktur);
	layoutDolny->addWidget(przyciskDuzejMikstury);
	layoutDolny->addStretch();
	layoutDolny->addWidget(przyciskKup);
	layoutDolny->addWidget(przyciskZaloz);
	layoutDolny->addWidget(ok);
	layoutGlowny->addLayout(layoutDolny);

	connect(listaTowarow, SIGNAL(clicked(QModelIndex)), this, SLOT(wyswietlOpisDlaBazaru(QModelIndex)));
	connect(listaPrzedmiotow, SIGNAL(clicked(QModelIndex)), this, SLOT(wyswietlOpisDlaGracza(QModelIndex)));

	connect(przyciskMalejMikstury, SIGNAL(clicked()), this, SLOT(kupMalaMiksture()));
	connect(przyciskDuzejMikstury, SIGNAL(clicked()), this, SLOT(kupDuzaMiksture()));
	connect(ok, SIGNAL(clicked()), this, SLOT(close()));
	connect(przyciskZaloz, SIGNAL(clicked()), this, SLOT(zaloz()));
	connect(przyciskKup, SIGNAL(clicked()), this, SLOT(kup()));

	zalozPrzedmiot(towary->front(), gracz);
}

void OknoBazaru::wypelnijListy()
{
	Ekwipunek* ekw = gracz->getEkwipunek();
	QList<Przedmiot*>* plecak = ekw->getPlecak();

	listaPrzedmiotow->clear();
	for(int i = 0; i < ekw->getPlecak()->size(); ++i)
		listaPrzedmiotow->addItem(plecak->at(i)->getNazwa());

	listaTowarow->clear();
	for(int i = 0; i < towary->size(); ++i)
		listaTowarow->addItem(towary->at(i)->getNazwa());
}

void OknoBazaru::wyswietlOpisDlaGracza(QModelIndex element)
{
	przyciskKup->setText("Sprzedaj");
	przyciskKup->setVisible(true);
	przyciskKup->setEnabled(true);

	Przedmiot* rzecz = gracz->getEkwipunek()->getPlecak()->at(element.row());

	przyciskZaloz->setVisible(true);
	if(czyZalozony(rzecz, gracz))
		przyciskZaloz->setText("Zdejmij");
	else
		przyciskZaloz->setText(QString::fromUtf8("Załóż"));

	przyciskZaloz->setEnabled(czyDozwolony(rzecz, gracz));

	wygenerujOpis(rzecz, gracz, opisPrzedmiotu);
}

void OknoBazaru::wyswietlOpisDlaBazaru(QModelIndex element)
{
	Przedmiot* rzecz = towary->at(element.row());

	przyciskZaloz->setVisible(false);

	przyciskKup->setVisible(true);
	przyciskKup->setText("Kup");

	przyciskKup->setEnabled(gracz->getZloto() >= rzecz->getWartosc());

	przyciskZaloz->setVisible(false);
	wygenerujOpis(rzecz, gracz, opisPrzedmiotu);
}

void OknoBazaru::kupMalaMiksture()
{
	Ekwipunek* ekw = gracz->getEkwipunek();
	ekw->setMalePoty(ekw->getMalePoty() + 1);
	gracz->setZloto(gracz->getZloto() - CENA_MALEJ_MIKSTURY);

	okno->uaktualnijInformacje();
	iloscMalychMisktur->setText(QString::number(gracz->getEkwipunek()->getMalePoty()));

	przyciskDuzejMikstury->setEnabled(gracz->getZloto() >= CENA_DUZEJ_MIKSTURY);
	przyciskMalejMikstury->setEnabled(gracz->getZloto() >= CENA_MALEJ_MIKSTURY);
}

void OknoBazaru::kupDuzaMiksture()
{

	Ekwipunek* ekw = gracz->getEkwipunek();
	ekw->setDuzePoty(ekw->getDuzePoty() + 1);
	gracz->setZloto(gracz->getZloto() - CENA_DUZEJ_MIKSTURY);

	okno->uaktualnijInformacje();
	iloscDuzychMisktur->setText(QString::number(gracz->getEkwipunek()->getDuzePoty()));

	przyciskDuzejMikstury->setEnabled(gracz->getZloto() >= CENA_DUZEJ_MIKSTURY);
	przyciskMalejMikstury->setEnabled(gracz->getZloto() >= CENA_MALEJ_MIKSTURY);
}

void OknoBazaru::zaloz()
{
	QList<Przedmiot*>* plecak = gracz->getEkwipunek()->getPlecak();

	if(przyciskZaloz->text() == "Zdejmij")
		zdejmijPrzedmiot(plecak->at(listaPrzedmiotow->currentRow()), gracz);
	else
		zalozPrzedmiot(plecak->at(listaPrzedmiotow->currentRow()), gracz);
	okno->uaktualnijInformacje();
}

void OknoBazaru::kup()
{
	QList<Przedmiot*>* plecak = gracz->getEkwipunek()->getPlecak();
	if(przyciskKup->text() == "Sprzedaj")
	{
		Przedmiot* rzecz = plecak->at(listaPrzedmiotow->currentRow());
		zdejmijPrzedmiot(rzecz, gracz);
		plecak->removeAt(plecak->indexOf(rzecz));
		towary->push_back(rzecz);
		gracz->setZloto(gracz->getZloto() + rzecz->getWartosc() / 2);

	}
	else
	{
		Przedmiot* rzecz = towary->at(listaTowarow->currentRow());
		if(gracz->getZloto() < rzecz->getWartosc())
			return;

		plecak->push_back(rzecz);
		towary->removeAt(towary->indexOf(rzecz));
		gracz->setZloto(gracz->getZloto() - rzecz->getWartosc());
	}
	wypelnijListy();
	okno->uaktualnijInformacje();
	przyciskDuzejMikstury->setEnabled(gracz->getZloto() >= CENA_DUZEJ_MIKSTURY);
	przyciskMalejMikstury->setEnabled(gracz->getZloto() >= CENA_MALEJ_MIKSTURY);
}
