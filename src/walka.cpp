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
	obrazekPrzeciwnika->setPixmap(QString(":/przeciwnicy/" + przeciwnik->getNazwaObrazka()));
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
	ikonkaAtakuPrzeciwnika->setPixmap(QString(":/ikonki/wrecz.png"));
	atakPrzeciwnika = new QLabel(QString::number(przeciwnik->getAtakMinimalny()) + " - " + QString::number(przeciwnik->getAtakMaksymalny()));
	ikonkaObronyPrzeciwnika = new QLabel();
	ikonkaObronyPrzeciwnika->setPixmap(QString(":/ikonki/obrona.png"));
	obronaPrzeciwnika = new QLabel(QString::number(przeciwnik->getObrona()));
	ikonkaPercepcjiPrzeciwnika = new QLabel();
	ikonkaPercepcjiPrzeciwnika->setPixmap(QString(":ikonki/percepcja.png"));
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
	ikonkaObronyGracza->setPixmap(QString(":/ikonki/obrona.png"));
	obronaGracza = new QLabel(QString::number(gracz->getObrona()));

	ikonkaPercepcjiGracza = new QLabel();
	ikonkaPercepcjiGracza->setPixmap(QString(":/ikonki/percepcja.png"));
	percepcjaGracza = new QLabel(QString::number(gracz->getPercepcja()));
	linijkaDanychGracza = new QHBoxLayout();
	linijkaDanychGracza->addWidget(ikonkaObronyGracza);
	linijkaDanychGracza->addWidget(obronaGracza);
	linijkaDanychGracza->addWidget(ikonkaPercepcjiGracza);
	linijkaDanychGracza->addWidget(percepcjaGracza);
	linijkaDanychGracza->addStretch();
	layoutGracza->addLayout(linijkaDanychGracza);

	przyciskAtakuWrecz = new QPushButton();
	przyciskAtakuWrecz->setIcon(QIcon(":/ikonki/wrecz.png") );
	przyciskAtakuWrecz->setText(QString::number(gracz->getAtakWrecz()));

	przyciskAtakuDystansowego = new QPushButton();
	przyciskAtakuDystansowego->setIcon(QIcon(":/ikonki/dystans.png"));
	przyciskAtakuDystansowego->setText(QString::number(gracz->getAtakDystansowy()));

	przyciskAtakuMagicznego = new QPushButton();
	przyciskAtakuMagicznego->setIcon(QIcon(":/ikonki/magia.png"));
	przyciskAtakuMagicznego->setText(QString::number(gracz->getAtakMagiczny()));

	linijkaAtakowGracza = new QHBoxLayout();
	linijkaAtakowGracza->addWidget(przyciskAtakuWrecz);
	linijkaAtakowGracza->addWidget(przyciskAtakuDystansowego);
	linijkaAtakowGracza->addWidget(przyciskAtakuMagicznego);
	layoutGracza->addLayout(linijkaAtakowGracza);

	przyciskMalejMikstury = new QPushButton();
	przyciskMalejMikstury->setIcon(QIcon(":/ikonki/mala_mikstura.png"));
	przyciskMalejMikstury->setText(QString("(") + QString::number(gracz->getEkwipunek()->getMalePoty()) + QString(")"));
	if(gracz->getEkwipunek()->getMalePoty() == 0)
		przyciskMalejMikstury->setEnabled(false);
	przyciskDuzejMikstury = new QPushButton();
	przyciskDuzejMikstury->setIcon(QIcon(":/ikonki/duza_mikstura.png"));
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

void Walka::ruchPrzeciwnika()
{
	qsrand( QDateTime::currentDateTime().toTime_t() );
	quint8 atak = qrand() % (przeciwnik->getAtakMaksymalny() - przeciwnik->getAtakMinimalny()) + przeciwnik->getAtakMinimalny();

	log->insertPlainText(QString::fromUtf8("Przeciwnik atakuje z siłą ") + QString::number(atak) + QString("\n"));

	int obrazenia = qMax(atak - gracz->getObrona(), 0);

	log->insertPlainText(QString::fromUtf8("Obrażenia gracza: ") + QString::number(obrazenia) + QString("\n"));

	gracz->setZdrowieAktualne(qMax(gracz->getZdrowieAktualne() - obrazenia, 0));
	punktyZdrowiaGracza->setText(QString::number(gracz ->getZdrowieAktualne()) + "/" + QString::number(gracz->getZdrowieMaks()));
	pasekZdrowiaGracza->wypelnijPierwszy((qreal)gracz->getZdrowieAktualne() / gracz->getZdrowieMaks());
	this->repaint();

	if(gracz->getZdrowieAktualne() == 0)
	{
		mistrzGry->koniecWalki(przeciwnik, przegrana);
	close();
	}
}

void Walka::atakGracza(int atak)
{
	int obrazenia = qMax(atak - przeciwnik->getObrona(), 0);

	log->insertPlainText(QString::fromUtf8("Zadane obrażenia: ") + QString::number(obrazenia) + QString("\n"));

	aktualneZdrowiePrzeciwnika = qMax(0, aktualneZdrowiePrzeciwnika - obrazenia);
	punktyZdrowiaPrzeciwnika->setText(QString::number(aktualneZdrowiePrzeciwnika) + "/" + QString::number(przeciwnik->getZdrowieMaks()));
	pasekZdrowiaPrzeciwnika->wypelnij((qreal)aktualneZdrowiePrzeciwnika / przeciwnik->getZdrowieMaks());
	this->repaint();

	if(aktualneZdrowiePrzeciwnika == 0)
	{
		mistrzGry->koniecWalki(przeciwnik, wygrana);
		close();
	}
	else
		ruchPrzeciwnika();
}

void Walka::atakWrecz()
{
	log->insertPlainText(QString::fromUtf8("Gracz atakuje wręcz z siłą ") + QString::number(gracz->getAtakWrecz()) + QString("\n"));

	atakGracza(gracz->getAtakWrecz());
}

void Walka::atakDystansowy()
{
	log->insertPlainText(QString::fromUtf8("Gracz atakuje bronią dystansową z siłą ") + QString::number(gracz->getAtakDystansowy()) + QString("\n"));

	atakGracza(gracz->getAtakDystansowy());
}

void Walka::atakMagiczny()
{
	log->insertPlainText(QString::fromUtf8("Gracz atakuje magicznie z siłą ") + QString::number(gracz->getAtakMagiczny()) + QString("\n"));

	atakGracza(gracz->getAtakMagiczny());
}

void Walka::uciekaj()
{
	close();
	mistrzGry->koniecWalki(przeciwnik, ucieczka);
}

void Walka::uzyjDuzejMikstury()
{
	gracz->getEkwipunek()->setDuzePoty(gracz->getEkwipunek()->getDuzePoty() - 1);
	przyciskDuzejMikstury->setText(QString("(") + QString::number(gracz->getEkwipunek()->getDuzePoty()) + QString(")"));
	if(gracz->getEkwipunek()->getDuzePoty() == 0)
		przyciskDuzejMikstury->setEnabled(false);
	gracz->setZdrowieAktualne(qMin(gracz->getZdrowieMaks(), (quint8)(gracz->getZdrowieAktualne() + DZIALANIE_DUZYCH_POTOW)));
	ruchPrzeciwnika();
}

void Walka::uzyjMalejMikstury()
{
	gracz->getEkwipunek()->setMalePoty(gracz->getEkwipunek()->getMalePoty() - 1);
	przyciskMalejMikstury->setText(QString("(") + QString::number(gracz->getEkwipunek()->getMalePoty()) + QString(")"));
	if(gracz->getEkwipunek()->getMalePoty() == 0)
		przyciskMalejMikstury->setEnabled(false);
	gracz->setZdrowieAktualne(qMin(gracz->getZdrowieMaks(), (quint8)(gracz->getZdrowieAktualne() + DZIALANIE_MALYCH_POTOW)));
	ruchPrzeciwnika();
}
