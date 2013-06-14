#ifndef OKNOTAWERNY_H
#define OKNOTAWERNY_H

#include <QDialog>
#include "zarzadzaniezadaniami.h"
#include "plansza.h"
#include "gracz.h"
#include "zadanie.h"
#include "gra.h"

class OknoTawerny : public QDialog
{
	Q_OBJECT
public:
	explicit OknoTawerny(Gracz* gracz, Plansza* plansza, QList<Zadanie *>* dostepneZadania);
private:
	Gracz* gracz;
	Plansza* plansza;

	QVBoxLayout* layoutGlowny;

	QLabel* tytulWlasnychZadan;
	QListWidget* listaWlasnychZadan;

	QList<Zadanie*>* dostepneZadania;
	QLabel* tytulMozliwychZadan;
	QListWidget* listaMozliwychZadan;

	QTextBrowser* opisZadania;

	QVBoxLayout* layoutLewy;
	QHBoxLayout* layoutGorny;
	QHBoxLayout* layoutDolny;

	QPushButton* przyciskPrzyjmij;
	QPushButton* przyciskPokazCel;
	QPushButton* ok;

	Zadanie* ostatnioWyswietlone;
	void wypelnijListy();

private slots:
	void wyswietlOpisDlaWlasnych(QModelIndex element);
	void wyswietlOpisDlaMozliwych(QModelIndex element);
	void przyjmij();
	void pokaz();

};

#endif // OKNOTAWERNY_H
