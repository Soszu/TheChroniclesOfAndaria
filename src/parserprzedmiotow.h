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
		quint8 wrecz;
		quint8 dystans;
		quint8 magia;
		quint8 obrona;
		quint8 percepcja;
		quint8 HP;
		quint8 HPregen;
		int ograniczenie;
		bool czy1Reczna;
		bool czyOd5Poziom;
		quint8 wartosc;
		char kolorCzcionki;
	};
};

#endif // PARSERPRZEDMIOTOW_H
