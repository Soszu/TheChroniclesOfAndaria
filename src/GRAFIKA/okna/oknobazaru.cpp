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
	listaPrzedmiotow->setToolTip(QString::fromUtf8("Lista posiadanych przedmiotów."));
	tytulTowarow = new QLabel(QString::fromUtf8("Przedmioty dostępne na bazarze"));
	listaTowarow = new QListWidget();
	listaTowarow->setToolTip(QString::fromUtf8("Lista towarów dostępnych do kupienia na bazarze."));
	wypelnijListy();

	layoutLewy = new QVBoxLayout();
	layoutLewy->addWidget(tytulPrzedmiotow);
	layoutLewy->addWidget(listaPrzedmiotow);
	layoutLewy->addWidget(tytulTowarow);
	layoutLewy->addWidget(listaTowarow);
	layoutGorny = new QHBoxLayout();
	layoutGorny->addLayout(layoutLewy);

	opisPrzedmiotu = new QTextBrowser();
	opisPrzedmiotu->setToolTip(QString::fromUtf8("opis aktualnie zaznaczonego przedmiotu."));
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
	przyciskKup->setToolTip(QString::fromUtf8("Zależnie od okoliczności, przycisk pozwala na kupno albo sprzedaż aktualnie zaznaczonego przedmiotu."));
	przyciskKup->setVisible(false);
	przyciskZaloz = new QPushButton();
	przyciskZaloz->setToolTip(QString::fromUtf8("Zależnie od okoliczności, przycisk pozwala na założenie albo zdjęcie aktualnie zaznaczonego przedmiotu z Twojej postaci."));
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
}

/**
 * @brief OknoBazaru::wypelnijListy	Wypełnia listę przedmiotów własnych i do kupienia odpowiednimi nazwami.
 */
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

/**
 * @brief OknoBazaru::wyswietlOpisDlaGracza	Wyświetla opis przedmiotu z listy posiadanych przez gracza
 * @param element	dane wpisu, który został wybrany.
 */
void OknoBazaru::wyswietlOpisDlaGracza(QModelIndex element)
{
	listaTowarow->setCurrentRow(-1);

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

/**
 * @brief OknoBazaru::wyswietlOpisDlaBazaru	Wyświetla opis przedmiotu z listy dostępnych na bazarze.
 * @param element	dane wpisu, który został wybrany
 */
void OknoBazaru::wyswietlOpisDlaBazaru(QModelIndex element)
{
	listaPrzedmiotow->setCurrentRow(-1);

	Przedmiot* rzecz = towary->at(element.row());

	przyciskZaloz->setVisible(false);

	przyciskKup->setVisible(true);
	przyciskKup->setText("Kup");

	przyciskKup->setEnabled(gracz->getZloto() >= rzecz->getWartosc());

	przyciskZaloz->setVisible(false);
	wygenerujOpis(rzecz, gracz, opisPrzedmiotu);
}

/**
 * @brief OknoBazaru::kupMalaMiksture	Przeprowadza kupno małej mikstury zdrowia.
 */
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

/**
 * @brief OknoBazaru::kupDuzaMiksture	Przeprowadza kupno dużej mikstury zdrowia.
 */
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

/**
 * @brief OknoBazaru::zaloz	Odpowiednio zakłada lub zdejmuje aktualnie zaznaczony przedmiot z listy						przedmiotów gracza
 */
void OknoBazaru::zaloz()
{
	QList<Przedmiot*>* plecak = gracz->getEkwipunek()->getPlecak();
	Przedmiot* rzecz = plecak->at(listaPrzedmiotow->currentRow());

	if(przyciskZaloz->text() == "Zdejmij")
		zdejmijPrzedmiot(rzecz, gracz);
	else
		zalozPrzedmiot(rzecz, gracz);

	wygenerujOpis(rzecz, gracz, opisPrzedmiotu);
	okno->uaktualnijInformacje();

	if(czyZalozony(rzecz, gracz))
		przyciskZaloz->setText("Zdejmij");
	else
		przyciskZaloz->setText(QString::fromUtf8("Załóż"));
}

/**
 * @brief OknoBazaru::kup	Kupuje lub sprzedaje aktualnie zaznaczony przedmiot z listy przedmiotów na					bazarze.
 */
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
