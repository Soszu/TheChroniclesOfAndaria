#ifndef OKNOEKWIPUNEK_H
#define OKNOEKWIPUNEK_H

#include <QDialog>
#include <QtGui>
#include "gracz.h"
#include "oknogracza.h"

class OknoGracza;

class OknoEkwipunek : public QDialog
{
	Q_OBJECT
public:
	explicit OknoEkwipunek(Gracz* gracz, OknoGracza* okno);

private:
	Gracz* gracz;
	OknoGracza* oknoGracza;

	QVBoxLayout* layoutGlowny;
	QListWidget* listaPrzedmiotow;
	QTextBrowser* opisPrzedmiotu;

	QHBoxLayout* layoutGorny;
	QHBoxLayout* layoutDolny;

	QPushButton* przyciskMalejMikstury;
	QPushButton* przyciskDuzejMikstury;

	QPushButton* przyciskZaloz;
	QPushButton* ok;

	void dezaktywujBonusy(Przedmiot* przedmiot);
	void aktywujBonusy(Przedmiot* przedmiot);

signals:

private slots:
	void zaloz();
	void wygenerujOpis(QModelIndex element);
	void uzyjDuzejMikstury();
	void uzyjMalejMikstury();


};

#endif // OKNOEKWIPUNEK_H
