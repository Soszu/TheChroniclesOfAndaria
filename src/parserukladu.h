#ifndef PARSERUKLADU_H
#define PARSERUKLADU_H

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QStringList>
#include <QMap>
#include <QList>
#include "plansza.h"
#include "pole.h"

class Plansza;

class ParserUkladu
{
public:
	ParserUkladu(Plansza* plansza);
	qint8 GetSzerokoscPlanszy();
	qint8 getWysokoscPlanszy();
	bool bladWczytywania();

private:
	bool bylBlad;
	Plansza* plansza;

	quint8 szerokosc;
	quint8 wysokosc;

	bool wczytajWymiary(QTextStream* wejscie);
	bool wczytajLegende(QTextStream* wejscie);
	bool wczytajUstawienie(QTextStream* wejscie);

	QString nastepny(QTextStream* wejscie);

	struct info{
		QString nazwa;
		QString plik;
		bool czyPoleZPrzeciwnikiem;
		quint8 wspolczynnik;
	};
	QMap<QString, info> legenda;
};

#endif // PARSERUKLADU_H
