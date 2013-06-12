#include "oknonagrody.h"

OknoNagrody::OknoNagrody(Gracz *gracz, Nagroda *nagroda, QList<Przedmiot *> przedmioty, CyklGry *cykl)
{
	this->gracz = gracz;
	this->nagroda = nagroda;
	this->cykl = cykl;
	this->przydzielonePrzedmioty = przedmioty;
	layoutGlowny = new QVBoxLayout(this);

	//czy Awans
	if(gracz->getPoziom() < MAKSYMALNY_POZIOM &&
	   gracz->getDoswiadczenie() >= GRANICE_POZIOMOW[gracz->getPoziom()])
	{
		gracz->setPoziom(gracz->getPoziom() + 1);
		czyAwans = true;
	}
	else
		czyAwans = false;

	tytulListyPrzedmiotow = new QLabel(QString::fromUtf8("Otrzymujesz następujące przedmioty:"));
	listaPrzedmiotow = new QListWidget();
	for(int i = 0; i < przydzielonePrzedmioty.size(); ++i)
		listaPrzedmiotow->addItem(przydzielonePrzedmioty[i]->getNazwa());

	tytulOpisuNagrody = new QLabel(QString::fromUtf8("Otrzymujesz również:"));
	opisNagrody = new QTextBrowser();
	opisNagrody->setText(generujOpisNagrody());


	layoutOpisowLewy = new QVBoxLayout();
	layoutOpisowLewy->addWidget(tytulListyPrzedmiotow);
	layoutOpisowLewy->addWidget(listaPrzedmiotow);
	layoutOpisowLewy->addWidget(tytulOpisuNagrody);
	layoutOpisowLewy->addWidget(opisNagrody);

	opisPrzedmiotu = new QTextBrowser();

	layoutOpisow = new QHBoxLayout();
	layoutOpisow->addLayout(layoutOpisowLewy);
	layoutOpisow->addWidget(opisPrzedmiotu);
	layoutGlowny->addLayout(layoutOpisow);

	layoutAwansu = new QHBoxLayout();
	tekstAwansu = new QLabel(QString::fromUtf8("Awansowałeś na kolejny poziom, przydziel punkty:"));
	layoutAwansu->addWidget(tekstAwansu);
	for(int i = 0; i < LICZBA_PUNKTOW_NA_POZIOM; ++i)
	{
		przydzieleniePunktow.push_back(new QComboBox());
		for(int j = 0; j < LICZBA_ATRYBOTOW_DO_AWANSU; ++j)
			przydzieleniePunktow[i]->addItem(MOZLIWE_AWANSE[j]);
		przydzieleniePunktow[i]->setVisible(czyAwans);
		layoutAwansu->addWidget(przydzieleniePunktow[i]);
	}
	layoutAwansu->addStretch();

	tekstAwansu->setVisible(czyAwans);
	layoutGlowny->addLayout(layoutAwansu);


	layoutPrzyciskow = new QHBoxLayout();
	ok = new QPushButton("Ok");
	layoutPrzyciskow->addStretch();
	layoutPrzyciskow->addWidget(ok);
	layoutGlowny->addLayout(layoutPrzyciskow);


	connect(ok, SIGNAL(clicked()), this, SLOT(zakoncz()));
	connect(listaPrzedmiotow, SIGNAL(clicked(QModelIndex)), this, SLOT(wyswietlOpis(QModelIndex)));
}

void OknoNagrody::zwiekszAtrybut(int indeks)
{
	switch (indeks) {
	case Awrecz:
		gracz->setAtakWrecz(gracz->getAtakWrecz() + 1);
		break;
	case Adystansowy:
		gracz->setAtakDystansowy(gracz->getAtakDystansowy() + 1);
		break;
	case Amagiczny:
		gracz->setAtakMagiczny(gracz->getAtakMagiczny() + 1);
		break;
	case obrona:
		gracz->setObrona(gracz->getObrona() + 1);
		break;
	case percepcja:
		gracz->setPercepcja(gracz->getPercepcja() + 1);
		break;
	case zdrowie:
		gracz->setZdrowieMaks(gracz->getZdrowieMaks() + BONUS_DO_HP_PRZY_AWANSIE);
		gracz->setZdrowieAktualne(gracz->getZdrowieAktualne() + BONUS_DO_HP_PRZY_AWANSIE);
		break;

	}
}

QString OknoNagrody::generujOpisNagrody()
{
	QString wynik;
	if(nagroda->getDoswiadczenie() != 0)
		wynik += QString::fromUtf8("Zdobyte doświadczenie: ") +
			 QString::number(nagroda->getDoswiadczenie());
	if(nagroda->getZloto() != 0)
		wynik += QString::fromUtf8("\n\nZdobyte złoto: ") +
			 QString::number(nagroda->getZloto()) +
			 QString("\n\n");
	for(int i = 0; i < LICZBA_KROLESTW; ++i)
	{
		int zmiana = nagroda->getReputacja()[i];
		if(zmiana > 0)
			wynik += QString("+");
		if(zmiana < 0)
			wynik += QString("-");
		if(zmiana != 0)
			wynik += QString::number(zmiana) +
				 QString(" reputacja (") +
				 KROLESTWA[i] +
				 QString(")\n");
	}
	return wynik;
}

void OknoNagrody::wyswietlOpis(QModelIndex element)
{
	Przedmiot* rzecz = przydzielonePrzedmioty[element.row()];
	opisPrzedmiotu->setText(wygenerujOpis(rzecz, gracz));
}

void OknoNagrody::zakoncz()
{
	if(czyAwans)
		for(int i = 0; i < LICZBA_PUNKTOW_NA_POZIOM; ++i)
			zwiekszAtrybut(przydzieleniePunktow[i]->currentIndex());
	cykl->zakonczTure();
	close();
}
