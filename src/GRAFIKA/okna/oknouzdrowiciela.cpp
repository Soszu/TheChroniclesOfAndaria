#include "oknouzdrowiciela.h"

OknoUzdrowiciela::OknoUzdrowiciela(Gracz *gracz, OknoGracza *oknoGracza)
{
	this->gracz = gracz;
	this->oknoGracza = oknoGracza;

	rany = gracz->getZdrowieMaks() - gracz->getZdrowieAktualne();
	int maksymalnyKoszt = qMin((int)gracz->getZloto(), qCeil((qreal)rany / ODZYSKANE_ZDROWIE_ZA_SZTUKE_ZLOTA));

	this->setWindowTitle("Dom uzdrowiciela");
	layoutGlowny = new QVBoxLayout(this);
	layoutSuwaka = new QHBoxLayout();
	layoutPrzyciskow = new QHBoxLayout();

	wstep = new QLabel(QString::fromUtf8("Jesteś w domu uzdrowiciela, który może uleczyć Twoje rany.  \nMusisz jednak zapłacić za jego pracę i medykamenty. "));

	ustalenia = new QLabel();

	suwak = new QSlider(Qt::Horizontal);
	suwak->setToolTip(QString::fromUtf8("Przesuń suwak, aby zmienić warunki leczenia."));
	suwak->setRange(0, maksymalnyKoszt);
	connect(suwak, SIGNAL(valueChanged(int)), this, SLOT(uaktualnijUstalenia(int)));
	suwak->setValue(0);
	uaktualnijUstalenia(0);

	if(maksymalnyKoszt == 0)
	{
		suwak->setEnabled(false);
		ustalenia->setEnabled(false);
	}

	anuluj = new QPushButton("Anuluj", this);
	anuluj->setToolTip(QString::fromUtf8("Zrezygnuj z jakiejkolwiej pomocy."));
	connect(anuluj, SIGNAL(clicked()), this, SLOT(close()));

	ok = new QPushButton("OK", this);
	ok->setToolTip(QString::fromUtf8("Poproś o uzdrowienie zgodnie z ustaleniami."));
	connect(ok, SIGNAL(clicked()), this, SLOT(zatwierdz()));

	layoutGlowny->addWidget(wstep);
	layoutGlowny->addLayout(layoutSuwaka);
	layoutGlowny->addLayout(layoutPrzyciskow);

	layoutSuwaka->addWidget(suwak);
	layoutSuwaka->addWidget(ustalenia);

	layoutPrzyciskow->addStretch();
	layoutPrzyciskow->addWidget(anuluj);
	layoutPrzyciskow->addWidget(ok);
}

void OknoUzdrowiciela::zatwierdz()
{
	gracz->setZdrowieAktualne(zdrowiePoLeczeniu);
	gracz->setZloto(gracz->getZloto() - suwak->value());
	oknoGracza->wyswietlGracza(gracz);
	this->close();
}

void OknoUzdrowiciela::uaktualnijUstalenia(int wartosc)
{
	int poLeczeniu = gracz->getZdrowieAktualne() + ODZYSKANE_ZDROWIE_ZA_SZTUKE_ZLOTA * wartosc;
	zdrowiePoLeczeniu = qMin(gracz->getZdrowieMaks(), poLeczeniu);

	QString opis = QString::fromUtf8("Koszt w złocie: ");
	opis += QString::number(wartosc);

	opis += QString("\nZdrowie po leczeniu: ");
	opis += QString::number(zdrowiePoLeczeniu);
	opis += QString("/");
	opis += QString::number(gracz->getZdrowieMaks());

	ustalenia->setText(opis);
}
