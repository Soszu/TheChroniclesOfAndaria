#ifndef OKNOZASAD_H
#define OKNOZASAD_H

#include <QtGui>
#include <QDialog>
#include "gra.h"

class OknoZasad : public QDialog
{
	Q_OBJECT
public:
	explicit OknoZasad(QWidget *parent = 0);
private:
	QVBoxLayout* layoutGlowny;
	QHBoxLayout* layoutDolny;
	QLabel* przypomnienie;
	QTabWidget* zakladki;
	QPushButton* ok;

	QTextBrowser* ogolne;
	QTextBrowser* ekwipunek;
	QTextBrowser* poruszanie;
	QTextBrowser* zadania;
	QTextBrowser* walka;
	QTextBrowser* awans;
	QTextBrowser* koniec;
	QTextBrowser* widok;
};

#endif // OKNOZASAD_H
