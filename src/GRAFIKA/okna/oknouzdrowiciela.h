#ifndef OKNOUZDROWICIELA_H
#define OKNOUZDROWICIELA_H

#include <QDialog>
#include "gracz.h"
#include "gra.h"
#include "oknogracza.h"

class OknoUzdrowiciela : public QDialog
{
	Q_OBJECT
public:
	explicit OknoUzdrowiciela(Gracz* gracz, OknoGracza* oknoGracza);

private:
	OknoGracza* oknoGracza;
	Gracz* gracz;
	int rany;
	int zdrowiePoLeczeniu;

	QVBoxLayout* layoutGlowny;
	QHBoxLayout* layoutSuwaka;
	QHBoxLayout* layoutPrzyciskow;

	QLabel* wstep;
	QLabel* ustalenia;
	QSlider* suwak;
	QPushButton* anuluj;
	QPushButton* ok;

signals:

private slots:
	void zatwierdz();
	void uaktualnijUstalenia(int wartosc);

};

#endif // OKNOUZDROWICIELA_H
