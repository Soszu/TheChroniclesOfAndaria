#ifndef BOARDPARSER_H
#define BOARDPARSER_H

#include <QtCore>

#include "Core/Board.h"

class Board;

class BoardParser {
public:
	BoardParser(Board* plansza);
	bool bladWczytywania();
	QString trescBledu;
private:
	bool bylBlad;
	Board* plansza;

	quint8 szerokosc;
	quint8 wysokosc;

	bool wczytajWymiary(QTextStream* wejscie);
	bool wczytajLegende(QTextStream* wejscie);
	bool wczytajUstawienie(QTextStream* wejscie);

	QString nastepny(QTextStream* wejscie);

	struct info{
		QString name;
		QString plik;
		bool czyPoleZEnemyiem;
		bool czyPoleZMiastem;
		int wspolczynnik;
		int frakcja;
	};
	QMap<QString, info> legenda;
};

#endif
