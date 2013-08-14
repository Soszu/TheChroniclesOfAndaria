#ifndef OKNOBAZARU_H
#define OKNOBAZARU_H

#include <QList>
#include <QDialog>
#include "mistrzgry.h"
#include "gra.h"
#include "zarzadzanieekwipunkiem.h"
#include "przedmiot.h"

class MistrzGry;
class OknoGracza;

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

	QLabel* tytulPrzedmiotow;
	QListWidget* listaPrzedmiotow;

	QLabel* tytulTowarow;
	QListWidget* listaTowarow;

	QTextBrowser* opisPrzedmiotu;

	QVBoxLayout* layoutLewy;
	QHBoxLayout* layoutGorny;
	QHBoxLayout* layoutDolny;

	QLabel* ikonaMalejMikstury;
	QLabel* iloscMalychMisktur;
	QPushButton* przyciskMalejMikstury;

	QLabel* ikonaDuzejMikstury;
	QLabel* iloscDuzychMisktur;
	QPushButton* przyciskDuzejMikstury;

	QPushButton* przyciskZaloz;
	QPushButton* przyciskKup;
	QPushButton* ok;

	void wypelnijListy();

private slots:
	void wyswietlOpisDlaGracza(QModelIndex element);
	void wyswietlOpisDlaBazaru(QModelIndex element);
	void kupMalaMiksture();
	void kupDuzaMiksture();
	void zaloz();
	void kup();
};

#endif // OKNOBAZARU_H
