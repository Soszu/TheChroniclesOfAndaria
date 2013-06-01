#ifndef PARSERPRZEDMIOTOW_H
#define PARSERPRZEDMIOTOW_H

#include <QMap>
#include "mistrzgry.h"

class MistrzGry;

class ParserPrzedmiotow
{
public:
	ParserPrzedmiotow(MistrzGry* mistrz);
	bool bladWczytywania();
private:
	bool bylBlad;
	MistrzGry* mistrzGry;
	bool wczytajDane(QTextStream* wejscie);
	QString nastepny(QTextStream* wejscie);
	QString aktualnaGrupa;

	struct informacje{

	};
};

#endif // PARSERPRZEDMIOTOW_H
