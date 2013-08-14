#ifndef OKNOZADANIA_H
#define OKNOZADANIA_H

#include <QDialog>
#include "zarzadzaniezadaniami.h"
#include "plansza.h"
#include "gracz.h"
#include "zadanie.h"


class OknoZadania : public QDialog
{
	Q_OBJECT
public:
	explicit OknoZadania(Gracz* gracz, Plansza* plansza);

private:
	Gracz* gracz;
	Plansza* plansza;

	QVBoxLayout* layoutGlowny;

	QListWidget* listaZadan;

	QTextBrowser* opisZadania;

	QHBoxLayout* layoutGorny;
	QHBoxLayout* layoutDolny;

	QPushButton* przyciskPokazCel;
	QPushButton* ok;

private slots:
	void wyswietlOpis(QModelIndex element);
	void pokaz();
};

#endif // OKNOZADANIA_H
