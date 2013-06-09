#ifndef OKNOEKWIPUNEK_H
#define OKNOEKWIPUNEK_H

#include <QDialog>
#include <QtGui>
#include "gracz.h"

class OknoEkwipunek : public QDialog
{
	Q_OBJECT
public:
	explicit OknoEkwipunek(Gracz* gracz);

private:
	QVBoxLayout* layoutGlowny;
	QListWidget* listaPrzedmiotow;
	QTextBrowser* opisPrzedmiotu;

	QHBoxLayout* layoutGorny;
	QHBoxLayout* layoutDolny;

	QLabel* mikstury;
	QPushButton* przyciskZaloz;
	QPushButton* ok;

signals:

private slots:
	void zaloz();


};

#endif // OKNOEKWIPUNEK_H
