#include "oknonagrody.h"

OknoNagrody::OknoNagrody(Gracz *gracz, Nagroda *nagroda, QList<Przedmiot *> przedmioty, CyklGry *cykl, bool czyKoniecTury)
{
	this->gracz = gracz;
	this->nagroda = nagroda;
	this->cykl = cykl;
	this->przydzielonePrzedmioty = przedmioty;
	this->czyKoniecTury = czyKoniecTury;
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

/**
 * @brief OknoNagrody::zwiekszAtrybut	Zwiększa odpowiedni atrybut w statystykach gracza.
 * @param indeks	wartosc enumeratora atrybut (opisany w gra.h)
 */
void OknoNagrody::zwiekszAtrybut(atrybut indeks)
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
	default:
		break;
	}
}

/**
 * @brief OknoNagrody::generujOpisNagrody	Generuje opis nagrody, zapisanej w atrybucie prywatnym klasy
 * @return	QString z opisem nagrody
 */
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

/**
 * @brief OknoNagrody::rozpocznij	Ustala czy jednocześnie nastąpił awans oraz wyświetla okno.
 */
void OknoNagrody::rozpocznij()
{
	if(czyAwans)
	QMessageBox::information(
		this,
		QString("Awans"),
		QString::fromUtf8("Awansowałeś na kolejny poziom.\nPamiętaj o rozdzieleniu punktów."));
	show();
}

/**
 * @brief OknoNagrody::wyswietlOpis	Wyświetla opis zdobytego przedmiotu.
 * @param element	aktualnie zaznaczony element
 */
void OknoNagrody::wyswietlOpis(QModelIndex element)
{
	Przedmiot* rzecz = przydzielonePrzedmioty[element.row()];
	wygenerujOpis(rzecz, gracz, opisPrzedmiotu);
}

/**
 * @brief OknoNagrody::zakoncz	Powiększa wybrane atrybuty i kończy turę.
 */
void OknoNagrody::zakoncz()
{
	if(czyAwans)
	{
		for(int i = 0; i < LICZBA_PUNKTOW_NA_POZIOM; ++i)
			zwiekszAtrybut((atrybut)przydzieleniePunktow[i]->currentIndex());
		gracz->setZdrowieMaks(gracz->getZdrowieMaks() + BONUS_DO_HP_PRZY_AWANSIE);
		gracz->setZdrowieAktualne(gracz->getZdrowieAktualne() + BONUS_DO_HP_PRZY_AWANSIE);
	}
	if(czyKoniecTury)
		cykl->zakonczTure();
	close();
}
