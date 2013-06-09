#include "oknoekwipunek.h"

OknoEkwipunek::OknoEkwipunek(Gracz *gracz)
{
	layoutGlowny = new QVBoxLayout(this);
	setWindowTitle("Ekwipunek");

	listaPrzedmiotow = new QListWidget();
	opisPrzedmiotu = new QTextBrowser();
	layoutGorny = new QHBoxLayout();
	layoutGorny->addWidget(listaPrzedmiotow);
	layoutGorny->addWidget(opisPrzedmiotu);
	layoutGlowny->addLayout(layoutGorny);

	mikstury = new QLabel(gracz->getNazwa());
	przyciskZaloz = new QPushButton(QString::fromUtf8("Załóż przedmiot"));
	ok = new QPushButton("Ok");

	layoutDolny = new QHBoxLayout();
	layoutDolny->addWidget(mikstury);
	layoutDolny->addStretch();
	layoutDolny->addWidget(przyciskZaloz);
	layoutDolny->addWidget(ok);
	layoutGlowny->addLayout(layoutDolny);

	connect(ok, SIGNAL(clicked()), this, SLOT(close()));
	connect(przyciskZaloz, SIGNAL(clicked()), this, SLOT(zaloz()));
}

void OknoEkwipunek::zaloz()
{

}
