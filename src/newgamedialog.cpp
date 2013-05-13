#include "newgamedialog.h"

NewGameDialog::NewGameDialog(QWidget *parent) : QDialog(parent)
{
	komunikat = new QMessageBox;
	komunikat->setWindowTitle(QString::fromUtf8("Błąd"));

	liczbaGraczy = MIN_GRACZY;
	layoutGlowny = new QVBoxLayout(this);
	for(int i = 0; i < MAX_GRACZY; ++i)
		layoutNaWierszeWyboru.addLayout(&layoutyWierszy[i]);
	//bez tego się nie wyświetla, ale też nie robi błędów

	dodajGracza = new QPushButton("Dodaj gracza", this);
	connect(dodajGracza, SIGNAL(clicked()),this,SLOT(dodajWiersz()));

	usunGracza = new QPushButton(QString::fromUtf8("Usuń gracza"), this);
	connect(usunGracza, SIGNAL(clicked()),this,SLOT(usunWiersz()));

	anuluj = new QPushButton("Anuluj", this);
	connect(anuluj, SIGNAL(clicked()), this, SLOT(close()));

	ok = new QPushButton("OK", this);
	connect(ok, SIGNAL(clicked()), this, SLOT(przekazDane()));

	layoutNaPrzyciski.addWidget(dodajGracza);
	layoutNaPrzyciski.addWidget(usunGracza);
	layoutNaPrzyciski.addStretch();
	layoutNaPrzyciski.addWidget(anuluj);
	layoutNaPrzyciski.addWidget(ok);

	for(int i = 0; i < liczbaGraczy; ++i)
	{
		wierszWyboru tmp;
		wypelnij(&tmp, i);
		gracze.push_back(tmp);

	}
	layoutGlowny->addLayout(&layoutNaWierszeWyboru);
	layoutGlowny->addStretch();
	layoutGlowny->addLayout(&layoutNaPrzyciski);
}

NewGameDialog::~NewGameDialog()
{
	while(!gracze.empty())
	{
		delete gracze.back().nazwa;
		delete gracze.back().klasa;
		delete gracze.back().rasa;
		delete gracze.back().kolor;

		gracze.pop_back();
	}
}

void NewGameDialog::wypelnij(NewGameDialog::wierszWyboru *wiersz, int numer)
{
	wiersz->nazwa = new QLineEdit("Gracz "+QString::number(numer + 1));
	wiersz->rasa = new QComboBox();
	wiersz->klasa = new QComboBox();
	wiersz->kolor = new QComboBox();

	wiersz->rasa->addItem(QString::fromUtf8("Człowiek"));
	wiersz->rasa->addItem(QString::fromUtf8("Elf"));
	wiersz->rasa->addItem(QString::fromUtf8("Krasnolud"));
	wiersz->rasa->addItem(QString::fromUtf8("Niziołek"));

	wiersz->klasa->addItem(QString::fromUtf8("Wojownik"));
	wiersz->klasa->addItem(QString::fromUtf8("Mag"));
	wiersz->klasa->addItem(QString::fromUtf8("Łucznik"));
	wiersz->klasa->addItem(QString::fromUtf8("Druid"));

	wiersz->kolor->addItem(QString::fromUtf8("Zielony"));
	wiersz->kolor->addItem(QString::fromUtf8("Czerwony"));
	wiersz->kolor->addItem(QString::fromUtf8("Żólty"));
	wiersz->kolor->addItem(QString::fromUtf8("Niebieski"));
	wiersz->kolor->addItem(QString::fromUtf8("Czarny"));
	wiersz->kolor->addItem(QString::fromUtf8("Biały"));
	wiersz->kolor->addItem(QString::fromUtf8("Pomarańczowy"));
	wiersz->kolor->addItem(QString::fromUtf8("Fioletowy"));
	wiersz->kolor->addItem(QString::fromUtf8("Brązowy"));
	wiersz->kolor->addItem(QString::fromUtf8("Różowy"));

	wiersz->kolor->setCurrentIndex(numer);

	layoutyWierszy[numer].addWidget(wiersz->nazwa);
	layoutyWierszy[numer].addWidget(wiersz->rasa);
	layoutyWierszy[numer].addWidget(wiersz->klasa);
	layoutyWierszy[numer].addWidget(wiersz->kolor);
}

Gracz *NewGameDialog::dajGracza(int indeks)
{
	//TODO
	//można też możliwe wartości ująć w tabele
	return new Gracz(Qt::red, "graczTestowy", krasnolud, mag);

}

void NewGameDialog::przekazDane()
{
	for(int i = 0; i < liczbaGraczy; ++i) //czy poprawne
	{
		if(gracze[i].nazwa->text().size() == 0)
		{
			komunikat->setText(QString::fromUtf8("Nazwa conajmniej jednego z graczy nie została wpisana poprawnie."));
			komunikat->show();
			return;
		}
		if(gracze[i].nazwa->text().size() > 20)
		{
			komunikat->setText(QString::fromUtf8("Nazwa conajmniej jednego z graczy jest za długa. Limit to 20 znaków."));
			komunikat->show();
			return;
		}
		for(int j = i + 1; j < liczbaGraczy; ++j)
			if(gracze[i].kolor->currentText() == gracze[j].kolor->currentText())
			{
				komunikat->setText(QString::fromUtf8("Conajmniej jeden kolor się powtarza."));
				komunikat->show();
				return;
			}
	}

	QList<Gracz*> dane;

	for(int i = 0; i < liczbaGraczy; ++i )
		dane.push_back(dajGracza(i));

	this->close();
}

void NewGameDialog::dodajWiersz()
{
	if(liczbaGraczy < MAX_GRACZY)
	{
		wierszWyboru tmp;
		wypelnij(&tmp, liczbaGraczy);
		gracze.push_back(tmp);
		++liczbaGraczy;
	}
}

void NewGameDialog::usunWiersz()
{
	if(liczbaGraczy > MIN_GRACZY)
	{
		--liczbaGraczy;
		wierszWyboru tmp = gracze.back();

		layoutyWierszy[liczbaGraczy].removeWidget(tmp.nazwa);
		layoutyWierszy[liczbaGraczy].removeWidget(tmp.rasa);
		layoutyWierszy[liczbaGraczy].removeWidget(tmp.klasa);
		layoutyWierszy[liczbaGraczy].removeWidget(tmp.kolor);


		delete tmp.nazwa;
		delete tmp.klasa;
		delete tmp.rasa;
		delete tmp.kolor;

		gracze.pop_back();
	}
}
