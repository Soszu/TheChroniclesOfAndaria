#include "oknogracza.h"

OknoGracza::OknoGracza(QFrame* rama)
{
	layoutGlowny = new QVBoxLayout();
	rama->setLayout(layoutGlowny);
//------------------------------
	pierwszaLinijka = new QLabel();
//------------------------------
	opisPrzedZdrowiem = new QLabel("Zdrowie:");
	wskaznikZdrowia = new MojPasek(0, 0, Qt::red, Qt::green);

	linijkaZdrowia = new QHBoxLayout();
	linijkaZdrowia->addWidget(opisPrzedZdrowiem);
	linijkaZdrowia->addWidget(wskaznikZdrowia);
//------------------------------
	opisPrzedDoswiadczeniem = new QLabel("Poziom: _");
	wskaznikDoswiadczenia = new MojPasek(0, Qt::blue);
	linijkaDoswiadczenia = new QHBoxLayout();
	linijkaDoswiadczenia->addWidget(opisPrzedDoswiadczeniem);
	linijkaDoswiadczenia->addWidget(wskaznikDoswiadczenia);
//------------------------------
	reputacja = new QHBoxLayout();
	for(int i = 0; i < LICZBA_KROLESTW; ++i)
	{
		slupkiLayouts[i] = new QVBoxLayout();
		slupki[i] = new MojPasek(MAX_REPUTACJA, 0, Qt::yellow);
		slupki[i]->setToolTip(QString::fromUtf8("Wskaźnik reputacji dla frakcji: ") + KROLESTWA[i]);
		podpisy[i] = new QLabel(KROLESTWA[i]);
		slupkiLayouts[i]->addWidget(slupki[i]);
		slupkiLayouts[i]->addWidget(podpisy[i]);

		reputacja->addLayout(slupkiLayouts[i]);
	}
//------------------------------
	obronaIkona = new QLabel();
	obronaIkona->setPixmap(IKONKA_OBRONA);
	obronaIkona->setToolTip(QString::fromUtf8("Wartość współczynnika obrony."));
	obrona = new QLabel();
	obrona->setToolTip(QString::fromUtf8("Wartość współczynnika obrony."));
	percepcjaIkona = new QLabel();
	percepcjaIkona->setPixmap(IKONKA_PERCEPCJA);
	percepcjaIkona->setToolTip(QString::fromUtf8("Wartość współczynnika percepcji."));
	percepcja = new QLabel();
	percepcja->setToolTip(QString::fromUtf8("Wartość współczynnika percepcji."));
	ruchIkona = new QLabel();
	ruchIkona->setPixmap(IKONKA_RUCH);
	ruchIkona->setToolTip(QString::fromUtf8("Ilość punktów ruchu."));
	ruch = new QLabel();
	ruch->setToolTip(QString::fromUtf8("Ilość punktów ruchu."));

	linijkaObrony = new QHBoxLayout();
	linijkaObrony->addWidget(obronaIkona);
	linijkaObrony->addWidget(obrona);
	linijkaObrony->addWidget(percepcjaIkona);
	linijkaObrony->addWidget(percepcja);
	linijkaObrony->addWidget(ruchIkona);
	linijkaObrony->addWidget(ruch);
//------------------------------
	wreczIkona = new QLabel();
	wreczIkona->setPixmap(IKONKA_WRECZ);
	wreczIkona->setToolTip(QString::fromUtf8("Wartość ataku wręcz."));
	wrecz = new QLabel();
	wrecz->setToolTip(QString::fromUtf8("Wartość ataku wręcz."));
	dystansIkona = new QLabel();
	dystansIkona->setPixmap(IKONKA_DYSTANSOWY);
	dystansIkona->setToolTip(QString::fromUtf8("Wartość ataku dystansowego."));
	dystans = new QLabel();
	dystans->setToolTip(QString::fromUtf8("Wartość ataku dystansowego."));
	magiaIkona = new QLabel();
	magiaIkona->setPixmap(IKONKA_MAGICZNY);
	magiaIkona->setToolTip(QString::fromUtf8("Wartość ataku magicznego."));
	magia = new QLabel();
	magia->setToolTip(QString::fromUtf8("Wartość ataku magicznego."));

	linijkaAtakow = new QHBoxLayout();
	linijkaAtakow->addWidget(wreczIkona);
	linijkaAtakow->addWidget(wrecz);
	linijkaAtakow->addWidget(dystansIkona);
	linijkaAtakow->addWidget(dystans);
	linijkaAtakow->addWidget(magiaIkona);
	linijkaAtakow->addWidget(magia);
//------------------------------
	zlotoIkona = new QLabel();
	zlotoIkona->setPixmap(IKONKA_ZLOTO);
	zlotoIkona->setToolTip(QString::fromUtf8("Ilość posiadanego złota."));
	zloto = new QLabel();
	zloto->setToolTip(QString::fromUtf8("Ilość posiadanego złota."));

	linijkaZlota = new QHBoxLayout();
	linijkaZlota->addWidget(zlotoIkona);
	linijkaZlota->addWidget(zloto);
//------------------------------
	linijkaPrzyciskow = new QHBoxLayout();
	zadania = new QPushButton(QString::fromUtf8("Przejrzyj zadania"));
	zadania->setToolTip(QString::fromUtf8("Wyświetla opis wykonywanych zadań."));
	ekwipunek = new QPushButton(QString::fromUtf8("Przejrzyj ekwipunek"));
	ekwipunek->setToolTip(QString::fromUtf8("Wyświetla opis posiadanego ekwipunku."));
	linijkaPrzyciskow->addWidget(ekwipunek);
	linijkaPrzyciskow->addWidget(zadania);

	connect(ekwipunek, SIGNAL(clicked()), this, SLOT(pokazEkwipunek()));
	connect(zadania, SIGNAL(clicked()), this, SLOT(pokazZadania()));

//------------------------------
	layoutGlowny->addWidget(pierwszaLinijka);
	layoutGlowny->addLayout(linijkaZdrowia);
	layoutGlowny->addLayout(linijkaDoswiadczenia);
	layoutGlowny->addLayout(reputacja);
	layoutGlowny->addLayout(linijkaObrony);
	layoutGlowny->addLayout(linijkaAtakow);
	layoutGlowny->addLayout(linijkaZlota);
	layoutGlowny->addLayout(linijkaPrzyciskow);
}

/**
 * @brief OknoGracza::wyswietlGracz	Wyświetla dane podanego gracza.
 * @param gracz
 */
void OknoGracza::wyswietlGracza(Gracz *gracz)
{
	aktualnyGracz = gracz;
	pierwszaLinijka->setText(gracz->getNazwa() + ", " + RASY[gracz->getRasa()] + " " + KLASY[gracz->getKlasa()]);
//------------------------------
	QString odmianaPunkty;
	switch(gracz->getRegeneracja()){
	case 1:
		odmianaPunkty = "punkt";
		break;
	case 2: case 3: case 4:
		odmianaPunkty = "punkty";
		break;
	default:
		odmianaPunkty = QString::fromUtf8("punktów");
		break;
	}

	wskaznikZdrowia->wypelnijPierwszy((qreal)gracz->getZdrowieAktualne() / gracz->getZdrowieMaks());
	wskaznikZdrowia->wypelnijDrugi((qreal)gracz->getRegeneracja() / gracz->getZdrowieMaks());
	wskaznikZdrowia->setToolTip(QString("Punkty zdrowia: ") + QString::number(gracz->getZdrowieAktualne()) + QString("/") + QString::number(gracz ->getZdrowieMaks())+
				    QString::fromUtf8("\nRegeneracja: ") + QString::number(gracz->getRegeneracja()) + QString(" ") + odmianaPunkty + QString::fromUtf8("/turę") );
//------------------------------
	opisPrzedDoswiadczeniem->setText(QString("Poziom: ") + QString::number(gracz->getPoziom()));
	int ileDoswNaAktualnyPoziom = GRANICE_POZIOMOW[gracz->getPoziom()] - GRANICE_POZIOMOW[gracz->getPoziom() - 1];
	int ileDoswZebranoNaAktPoziomie = gracz->getDoswiadczenie() - GRANICE_POZIOMOW[gracz->getPoziom() - 1];
	wskaznikDoswiadczenia->wypelnij((qreal)ileDoswZebranoNaAktPoziomie / ileDoswNaAktualnyPoziom );
	if(gracz->getPoziom() < MAKSYMALNY_POZIOM)
		wskaznikDoswiadczenia->setToolTip(QString::fromUtf8("Punkty doświadczenia: ") + QString::number(ileDoswZebranoNaAktPoziomie) + QString("/") + QString::number(ileDoswNaAktualnyPoziom));
	else
		wskaznikDoswiadczenia->setToolTip(QString::fromUtf8("Osiągnąłeś maksymalny poziom"));
//------------------------------
	for(int i = 0; i < LICZBA_KROLESTW; ++i)
		slupki[i]->ustaw(gracz->getReputacja()[i]);
//------------------------------
	obrona->setText(QString::number(gracz->getObrona()));
	percepcja->setText(QString::number(gracz->getPercepcja()));
	ruch->setText(QString::number(gracz->getPunktyRuchu()));
//------------------------------
	wrecz->setText(QString::number(gracz->getAtakWrecz()));
	dystans->setText(QString::number(gracz->getAtakDystansowy()));
	magia->setText(QString::number(gracz->getAtakMagiczny()));
//------------------------------
	zloto->setText(QString::number(gracz->getZloto()) + odmiana(gracz->getZloto()));
//------------------------------

	if(gracz->getCzyAI())
	{
		zadania->setEnabled(false);
		ekwipunek->setEnabled(false);
	}
	else
	{
		zadania->setEnabled(true);
		ekwipunek->setEnabled(true);
	}

	qDebug() <<"Okno Gracza wyswietlilo dane: " <<gracz->getNazwa();
}

/**
 * @brief OknoGracza::uaktualnijInformacje	Odświeża dane i powiadamia o zmianie
 */
void OknoGracza::uaktualnijInformacje()
{
	mistrz->poinformujPlansze();
	wyswietlGracza(aktualnyGracz);
}

void OknoGracza::setMistrzGry(MistrzGry *mistrz)
{
	this->mistrz = mistrz;
}

/**
 * @brief OknoGracza::odmiana Odmienia słowo "sztuka" zależnie od liczby sztuk złota
 * @param n ile sztuk
 * @return
 */
QString OknoGracza::odmiana(int n)
{
	if(n == 1)
		return QString(" sztuka");
	if(n > 1 && n < 5)
		return QString(" sztuki");
	return QString(" sztuk");
}

/**
 * @brief OknoGracza::pokazEkwipunek Wywołuje Okno Ekwipunek
 */
void OknoGracza::pokazEkwipunek()
{
	oknoEkwipunek = new OknoEkwipunek(aktualnyGracz, this);
	oknoEkwipunek->setWindowModality(Qt::ApplicationModal);
	oknoEkwipunek->setAttribute(Qt::WA_DeleteOnClose);
	oknoEkwipunek->show();
}

/**
 * @brief OknoGracza::pokazZadania	Wywołuje Okno Zadania
 */
void OknoGracza::pokazZadania()
{
	oknoZadania = new OknoZadania(aktualnyGracz, mistrz->getPlansza());
	oknoZadania->setWindowModality(Qt::ApplicationModal);
	oknoZadania->setAttribute(Qt::WA_DeleteOnClose);
	oknoZadania->show();
}
