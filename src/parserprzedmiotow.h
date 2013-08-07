#ifndef PARSERPRZEDMIOTOW_H
#define PARSERPRZEDMIOTOW_H

#include <QMap>
#include <QList>
#include "mistrzgry.h"
#include "przedmiot.h"
#include "gra.h"

class MistrzGry;

class ParserPrzedmiotow
{
public:
	ParserPrzedmiotow(MistrzGry* mistrz);
	bool bladWczytywania();
	QString trescBledu;
private:
	bool bylBlad;
	MistrzGry* mistrzGry;
	bool wczytajDane(QTextStream* wejscie);
	QString nastepny(QTextStream* wejscie);
	QString aktualnaGrupa;

	struct informacje{
		int id;
		QString nazwa;
		char typ;
		int wrecz;
		int dystans;
		int magia;
		int obrona;
		int percepcja;
		int HP;
		int HPregen;
		int ograniczenie;
		bool czy1Reczna;
		bool czyMocny;
		int wartosc;
		char kolorCzcionki;
	};
};

#endif // PARSERPRZEDMIOTOW_H
