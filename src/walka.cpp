#include "walka.h"

Walka::Walka(Gracz *gracz, Przeciwnik *przeciwnik, MistrzGry *mistrzGry)
{
	this->mistrzGry = mistrzGry;
	this->przeciwnik = przeciwnik;
	this->gracz = gracz;

	setWindowTitle("Walka");
//---PRZECIWNIK
	layoutGlowny = new QHBoxLayout(this);
	layoutPrzeciwnika = new QVBoxLayout();
	layoutGracza = new QVBoxLayout();

	layoutGlowny->addLayout(layoutPrzeciwnika);
	layoutGlowny->addLayout(layoutGracza);

	obrazekPrzeciwnika = new QLabel();
	obrazekPrzeciwnika->setAlignment(Qt::AlignCenter);
	obrazekPrzeciwnika->setPixmap(QString(PREFIX_PRZECIWNIKOW + przeciwnik->getNazwaObrazka()));
	//obrazekPrzeciwnika->setMaximumSize(QSize(320, 320));
	layoutPrzeciwnika->addWidget(obrazekPrzeciwnika);

	nazwaPrzeciwnika = new QLabel(przeciwnik->getNazwa());
	layoutPrzeciwnika->addWidget(nazwaPrzeciwnika);

	opisPrzeciwnika = new QLabel(przeciwnik->getOpis());
	layoutPrzeciwnika->addWidget(opisPrzeciwnika);
//---linjka zdrowia

	pasekZdrowiaPrzeciwnika = new MojPasek(1, Qt::darkRed);
	aktualneZdrowiePrzeciwnika = przeciwnik->getZdrowieMaks();
	punktyZdrowiaPrzeciwnika = new QLabel(QString::number(aktualneZdrowiePrzeciwnika) + "/" + QString::number(przeciwnik->getZdrowieMaks()));
	linijkaZdrowiaPrzeciwnika = new QHBoxLayout();
	linijkaZdrowiaPrzeciwnika->addWidget(pasekZdrowiaPrzeciwnika);
	linijkaZdrowiaPrzeciwnika->addWidget(punktyZdrowiaPrzeciwnika);
	layoutPrzeciwnika->addLayout(linijkaZdrowiaPrzeciwnika);

//linjka danych
	ikonkaAtakuPrzeciwnika = new QLabel();
	ikonkaAtakuPrzeciwnika->setPixmap(IKONKA_WRECZ);
	atakPrzeciwnika = new QLabel(QString::number(przeciwnik->getAtakMinimalny()) + " - " + QString::number(przeciwnik->getAtakMaksymalny()));
	ikonkaObronyPrzeciwnika = new QLabel();
	ikonkaObronyPrzeciwnika->setPixmap(IKONKA_OBRONA);
	obronaPrzeciwnika = new QLabel(QString::number(przeciwnik->getObrona()));
	ikonkaPercepcjiPrzeciwnika = new QLabel();
	ikonkaPercepcjiPrzeciwnika->setPixmap(IKONKA_PERCEPCJA);
	percepcjaPrzeciwnika = new QLabel(QString::number(przeciwnik->getPercepcja()));
	linijkaDanychPrzeciwnika = new QHBoxLayout();
	linijkaDanychPrzeciwnika->addWidget(ikonkaAtakuPrzeciwnika);
	linijkaDanychPrzeciwnika->addWidget(atakPrzeciwnika);
	linijkaDanychPrzeciwnika->addWidget(ikonkaObronyPrzeciwnika);
	linijkaDanychPrzeciwnika->addWidget(obronaPrzeciwnika);
	linijkaDanychPrzeciwnika->addWidget(ikonkaPercepcjiPrzeciwnika);
	linijkaDanychPrzeciwnika->addWidget(percepcjaPrzeciwnika);
	linijkaDanychPrzeciwnika->addStretch();
	layoutPrzeciwnika->addLayout(linijkaDanychPrzeciwnika);

//---GRACZ
	log = new QTextBrowser();
	log->insertPlainText(QString::fromUtf8("Rozpoczęto walkę\n"));
	layoutGracza->addWidget(log);

	nazwaGracza = new QLabel(gracz->getNazwa());

	pasekZdrowiaGracza = new MojPasek((qreal)gracz->getZdrowieAktualne() / gracz->getZdrowieMaks(), gracz->getRegeneracja() / gracz->getZdrowieMaks(), Qt::red, Qt::green);
	punktyZdrowiaGracza = new QLabel(QString::number(gracz ->getZdrowieAktualne()) + "/" + QString::number(gracz->getZdrowieMaks()));
	linijkaZdrowiaGracza = new QHBoxLayout();
	linijkaZdrowiaGracza->addWidget(nazwaGracza);
	linijkaZdrowiaGracza->addWidget(pasekZdrowiaGracza);
	linijkaZdrowiaGracza->addWidget(punktyZdrowiaGracza);
	layoutGracza->addLayout(linijkaZdrowiaGracza);

	ikonkaObronyGracza = new QLabel();
	ikonkaObronyGracza->setPixmap(IKONKA_OBRONA);
	obronaGracza = new QLabel(QString::number(gracz->getObrona()));

	ikonkaPercepcjiGracza = new QLabel();
	ikonkaPercepcjiGracza->setPixmap(IKONKA_PERCEPCJA);
	percepcjaGracza = new QLabel(QString::number(gracz->getPercepcja()));
	linijkaDanychGracza = new QHBoxLayout();
	linijkaDanychGracza->addWidget(ikonkaObronyGracza);
	linijkaDanychGracza->addWidget(obronaGracza);
	linijkaDanychGracza->addWidget(ikonkaPercepcjiGracza);
	linijkaDanychGracza->addWidget(percepcjaGracza);
	linijkaDanychGracza->addStretch();
	layoutGracza->addLayout(linijkaDanychGracza);

	przyciskAtakuWrecz = new QPushButton();
	przyciskAtakuWrecz->setIcon(QIcon(IKONKA_WRECZ) );
	przyciskAtakuWrecz->setText(QString::number(gracz->getAtakWrecz()));

	przyciskAtakuDystansowego = new QPushButton();
	przyciskAtakuDystansowego->setIcon(QIcon(IKONKA_DYSTANSOWY));
	przyciskAtakuDystansowego->setText(QString::number(gracz->getAtakDystansowy()));

	przyciskAtakuMagicznego = new QPushButton();
	przyciskAtakuMagicznego->setIcon(QIcon(IKONKA_MAGICZNY));
	przyciskAtakuMagicznego->setText(QString::number(gracz->getAtakMagiczny()));

	linijkaAtakowGracza = new QHBoxLayout();
	linijkaAtakowGracza->addWidget(przyciskAtakuWrecz);
	linijkaAtakowGracza->addWidget(przyciskAtakuDystansowego);
	linijkaAtakowGracza->addWidget(przyciskAtakuMagicznego);
	layoutGracza->addLayout(linijkaAtakowGracza);

	przyciskMalejMikstury = new QPushButton();
	przyciskMalejMikstury->setIcon(QIcon(IKONKA_MALA_MIKSTURA_ZDROWIA));
	przyciskMalejMikstury->setText(QString("(") + QString::number(gracz->getEkwipunek()->getMalePoty()) + QString(")"));
	if(gracz->getEkwipunek()->getMalePoty() == 0)
		przyciskMalejMikstury->setEnabled(false);
	przyciskDuzejMikstury = new QPushButton();
	przyciskDuzejMikstury->setIcon(QIcon(IKONKA_DUZA_MIKSTURA_ZDROWIA));
	przyciskDuzejMikstury->setText(QString("(") + QString::number(gracz->getEkwipunek()->getDuzePoty()) + QString(")"));
	if(gracz->getEkwipunek()->getDuzePoty() == 0)
		przyciskDuzejMikstury->setEnabled(false);
	przyciskUcieczki = new QPushButton("Uciekaj");
	linijkaPrzyciskowGracza = new QHBoxLayout();
	linijkaPrzyciskowGracza->addWidget(przyciskMalejMikstury);
	linijkaPrzyciskowGracza->addWidget(przyciskDuzejMikstury);
	linijkaPrzyciskowGracza->addWidget(przyciskUcieczki);
	layoutGracza->addLayout(linijkaPrzyciskowGracza);

	connect(przyciskAtakuWrecz, SIGNAL(clicked()), this, SLOT(atakWrecz()));
	connect(przyciskAtakuDystansowego, SIGNAL(clicked()), this, SLOT(atakDystansowy()));
	connect(przyciskAtakuMagicznego, SIGNAL(clicked()), this, SLOT(atakMagiczny()));
	connect(przyciskMalejMikstury, SIGNAL(clicked()), this, SLOT(uzyjMalejMikstury()));
	connect(przyciskDuzejMikstury, SIGNAL(clicked()), this, SLOT(uzyjDuzejMikstury()));
	connect(przyciskUcieczki, SIGNAL(clicked()), this, SLOT(uciekaj()));
}

/**
 * @brief Walka::ruchPrzeciwnika	Wykonuje atak przeciwnika, a po nim sprawdza czy koniec walki
 */
void Walka::ruchPrzeciwnika()
{
	qsrand( QDateTime::currentDateTime().toTime_t() );
	quint8 atak = qrand() % (przeciwnik->getAtakMaksymalny() - przeciwnik->getAtakMinimalny()) + przeciwnik->getAtakMinimalny();

	wpisPrzeciwnika(przeciwnik, QString::fromUtf8("atakuje z siłą ") + QString::number(atak));
	log->verticalScrollBar()->setSliderPosition(log->verticalScrollBar()->maximum());

	int obrazenia = qMax(atak - gracz->getObrona(), 0);

	log->insertPlainText(QString::fromUtf8("Zadane obrażenia: ") + QString::number(obrazenia) + QString("\n"));

	gracz->setZdrowieAktualne(qMax(gracz->getZdrowieAktualne() - obrazenia, 0));
	punktyZdrowiaGracza->setText(QString::number(gracz ->getZdrowieAktualne()) + "/" + QString::number(gracz->getZdrowieMaks()));
	pasekZdrowiaGracza->wypelnijPierwszy((qreal)gracz->getZdrowieAktualne() / gracz->getZdrowieMaks());
	this->repaint();

	if(gracz->getZdrowieAktualne() == 0)
	{
		QString tekst(przeciwnik->getNazwa() + QString::fromUtf8(" wygrał walkę"));
		QMessageBox::information(
			this,
			QString::fromUtf8("Zakończono walkę"),
			tekst);
		qDebug() <<gracz->getNazwa() <<" przegrywa walke.";
		close();
		mistrzGry->koniecWalki(przeciwnik, przegrana);
	}
}

/**
 * @brief Walka::atakGracza	Wykonuje atak gracza z daną siłą, a po nim sprawdza czy koniec walki
 * @param atak		siła z jaką atakuje gracz
 */
void Walka::atakGracza(int atak)
{
	int obrazenia = qMax(atak - przeciwnik->getObrona(), 0);

	log->insertPlainText(QString::fromUtf8("Zadane obrażenia: ") + QString::number(obrazenia) + QString("\n"));
	log->verticalScrollBar()->setSliderPosition(log->verticalScrollBar()->maximum());

	aktualneZdrowiePrzeciwnika = qMax(0, aktualneZdrowiePrzeciwnika - obrazenia);
	punktyZdrowiaPrzeciwnika->setText(QString::number(aktualneZdrowiePrzeciwnika) + "/" + QString::number(przeciwnik->getZdrowieMaks()));
	pasekZdrowiaPrzeciwnika->wypelnij((qreal)aktualneZdrowiePrzeciwnika / przeciwnik->getZdrowieMaks());
	this->repaint();

	if(aktualneZdrowiePrzeciwnika == 0)
	{
		QString tekst(gracz->getNazwa() + QString::fromUtf8(" wygrał walkę"));
		QMessageBox::information(
			this,
			QString::fromUtf8("Zakończono walkę"),
			tekst);
		qDebug() <<gracz->getNazwa() <<"Wygrywa walke.";
		close();
		mistrzGry->koniecWalki(przeciwnik, wygrana);
	}
	else
		ruchPrzeciwnika();

}

/**
 * @brief Walka::wpisGracza	Wpisuje czynność wykonaną przez gracza podaną jako tekst do loga.
 * @param gracz		Gracz, który wykonuje działanie.
 * @param tekst		tekst będący opisem czynności
 */
void Walka::wpisGracza(Gracz *gracz, QString tekst)
{
	log->setTextColor(QColor(Qt::green));
	log->setFontWeight(QFont::Bold);
	log->insertPlainText(QString("\n") + gracz->getNazwa());
	log->setFontWeight(QFont::Normal);
	log->setTextColor(QColor(Qt::black));
	log->insertPlainText(QString(" ") + tekst + "\n");
	log->verticalScrollBar()->setSliderPosition(log->verticalScrollBar()->maximum());

}

/**
 * @brief Walka::wpisPrzeciwnika	Wpisuje czynność wykonaną przez przeciwnika podaną jako tekst do loga.
 * @param przeciwnik	Przeciwnik który wykonuje działanie.
 * @param tekst		tekst będący opisem czynności
 */
void Walka::wpisPrzeciwnika(Przeciwnik *przeciwnik, QString tekst)
{
	log->setTextColor(QColor(Qt::red));
	log->setFontWeight(QFont::Bold);
	log->insertPlainText(QString("\n") + przeciwnik->getNazwa());
	log->setFontWeight(QFont::Normal);
	log->setTextColor(QColor(Qt::black));
	log->insertPlainText(QString(" ") + tekst + "\n");
	log->verticalScrollBar()->setSliderPosition(log->verticalScrollBar()->maximum());
}

/**
 * @brief Walka::rozpocznij	Rozpoczyna walkę wyświetlając informacje o rozpoczynającym.
 */
void Walka::rozpocznij()
{
	show();
	QMessageBox::information(
		this,
		QString::fromUtf8("Rozpoczynający"),
		przeciwnik->getPercepcja() > gracz->getPercepcja() ?
			QString::fromUtf8("Walkę rozpoczyna ") + przeciwnik->getNazwa() + QString(".") :
			QString::fromUtf8("Walkę rozpoczyna ") + gracz->getNazwa() + QString(".") );

	if(przeciwnik->getPercepcja() > gracz->getPercepcja())
		ruchPrzeciwnika();

}

/**
 * @brief Walka::atakWrecz	Zleca wykonanie ataku wręcz, jako następne działanie gracza.
 */
void Walka::atakWrecz()
{
	wpisGracza(gracz, QString::fromUtf8(" atakuje wręcz z siłą ") + QString::number(gracz->getAtakWrecz()));
	atakGracza(gracz->getAtakWrecz());
}

/**
 * @brief Walka::atakDystansowy		Zleca wykonanie ataku bronią dystansową, jako następne działanie gracza.
 */
void Walka::atakDystansowy()
{
	wpisGracza(gracz, QString::fromUtf8(" atakuje bronią dystansową z siłą ") + QString::number(gracz->getAtakDystansowy()));
	atakGracza(gracz->getAtakDystansowy());
}

/**
 * @brief Walka::atakMagiczny		Zleca wykonanie ataku magicznego, jako następne działanie gracza.
 */
void Walka::atakMagiczny()
{
	wpisGracza(gracz, QString::fromUtf8(" atakuje magicznie z siłą ") + QString::number(gracz->getAtakMagiczny()));
	atakGracza(gracz->getAtakMagiczny());
}

/**
 * @brief Walka::uciekaj	Wykonuje ucieczke gracza z walki i zamyka okno.
 */
void Walka::uciekaj()
{
	qDebug() <<gracz->getNazwa() <<"Ucieka z pola walki.";
	close();
	mistrzGry->koniecWalki(przeciwnik, ucieczka);
}

/**
 * @brief Walka::uzyjDuzejMikstury	Zleca użycie dużej mikstury zdrowia.
 */
void Walka::uzyjDuzejMikstury()
{
	wpisGracza(gracz, QString::fromUtf8("używa dużej mikstury zdrowia."));

	gracz->getEkwipunek()->setDuzePoty(gracz->getEkwipunek()->getDuzePoty() - 1);
	przyciskDuzejMikstury->setText(QString("(") + QString::number(gracz->getEkwipunek()->getDuzePoty()) + QString(")"));
	if(gracz->getEkwipunek()->getDuzePoty() == 0)
		przyciskDuzejMikstury->setEnabled(false);
	gracz->setZdrowieAktualne(qMin(gracz->getZdrowieMaks(), (quint8)(gracz->getZdrowieAktualne() + DZIALANIE_DUZYCH_POTOW)));
	ruchPrzeciwnika();
}

/**
 * @brief Walka::uzyjMalejMikstury	Zleca użycie małej mikstury zdrowia.
 */
void Walka::uzyjMalejMikstury()
{
	wpisGracza(gracz, QString::fromUtf8("używa małej mikstury zdrowia."));

	gracz->getEkwipunek()->setMalePoty(gracz->getEkwipunek()->getMalePoty() - 1);
	przyciskMalejMikstury->setText(QString("(") + QString::number(gracz->getEkwipunek()->getMalePoty()) + QString(")"));
	if(gracz->getEkwipunek()->getMalePoty() == 0)
		przyciskMalejMikstury->setEnabled(false);
	gracz->setZdrowieAktualne(qMin(gracz->getZdrowieMaks(), (quint8)(gracz->getZdrowieAktualne() + DZIALANIE_MALYCH_POTOW)));
	ruchPrzeciwnika();
}
