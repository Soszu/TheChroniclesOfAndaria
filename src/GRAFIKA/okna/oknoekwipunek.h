#ifndef OKNOEKWIPUNEK_H
#define OKNOEKWIPUNEK_H

#include <QtGui>
#include <QDialog>
#include "zarzadzanieekwipunkiem.h"
#include "gracz.h"
#include "oknogracza.h"
#include "przedmiot.h"

class OknoGracza;

class OknoEkwipunek : public QDialog
{
	Q_OBJECT
public:
	explicit OknoEkwipunek(Gracz* gracz, OknoGracza* okno);

private:

	Gracz* gracz;
	OknoGracza* okno;
	QVBoxLayout* layoutGlowny;
	QListWidget* listaPrzedmiotow;
	QTextBrowser* opisPrzedmiotu;

	QHBoxLayout* layoutGorny;
	QHBoxLayout* layoutDolny;

	QPushButton* przyciskMalejMikstury;
	QPushButton* przyciskDuzejMikstury;

	QPushButton* przyciskZaloz;
	QPushButton* ok;

private slots:
	void uzyjDuzejMikstury();
	void uzyjMalejMikstury();
	void wyswietlOpis(QModelIndex element);
	void zaloz();
};

#endif // OKNOEKWIPUNEK_H
