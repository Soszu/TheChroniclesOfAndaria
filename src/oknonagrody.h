#ifndef OKNONAGRODY_H
#define OKNONAGRODY_H

#include <QDialog>
#include "gra.h"
#include "cyklgry.h"
#include "zarzadzanieekwipunkiem.h"
#include "gracz.h"
#include "oknogracza.h"

class OknoNagrody : public QDialog
{
	Q_OBJECT
public:
	explicit OknoNagrody(Gracz* gracz, Nagroda* nagroda, QList<Przedmiot*> przedmioty, CyklGry* cykl);

private:
	Gracz* gracz;
	Nagroda* nagroda;
	QList<Przedmiot*> przydzielonePrzedmioty;
	CyklGry* cykl;

	QVBoxLayout* layoutGlowny;

	QLabel* tytulOpisuNagrody;
	QTextBrowser* opisNagrody;

	QLabel* tytulListyPrzedmiotow;
	QListWidget* listaPrzedmiotow;

	QTextBrowser* opisPrzedmiotu;

	QLabel* tekstAwansu;

	QPushButton* ok;

	QHBoxLayout* layoutOpisow;
	QVBoxLayout* layoutOpisowLewy;
	QHBoxLayout* layoutAwansu;
	QHBoxLayout* layoutPrzyciskow;
	bool czyAwans;
	QList<QComboBox*> przydzieleniePunktow;//[LICZBA_PUNKTOW_NA_POZIOM];

	void zwiekszAtrybut(atrybut indeks);
	QString generujOpisNagrody();

public slots:
	void rozpocznij();

private slots:
	void wyswietlOpis(QModelIndex element);
	void zakoncz();
};

#endif // OKNONAGRODY_H
