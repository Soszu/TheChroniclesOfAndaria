#ifndef OKNOBAZARU_H
#define OKNOBAZARU_H

#include <QList>
#include <QDialog>
#include "mistrzgry.h"
#include "gra.h"
#include "zarzadzanieekwipunkiem.h"
#include "przedmiot.h"

class MistrzGry;

class OknoBazaru : public QDialog
{
	Q_OBJECT
public:
	explicit OknoBazaru(Gracz *gracz, OknoGracza *okno, QList<Przedmiot*>* towary);

private:
	Gracz* gracz;
	OknoGracza* okno;
	QList<Przedmiot*>* towary;

	QVBoxLayout* layoutGlowny;

	QListWidget* listaPrzedmiotow;

	QList<Przedmiot*> dostepneTowary;
	QListWidget* listaTowarow;

	QTextBrowser* opisPrzedmiotu;

	QVBoxLayout* layoutLewy;
	QHBoxLayout* layoutGorny;
	QHBoxLayout* layoutDolny;

	QPushButton* przyciskZaloz;
	QPushButton* ok;

private slots:
	void wyswietlOpisDlaGracza(QModelIndex element);
	void wyswietlOpisDlaBazaru(QModelIndex element);
	void zaloz();
};

#endif // OKNOBAZARU_H
