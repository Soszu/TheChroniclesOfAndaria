#ifndef PARSERNAGROD_H
#define PARSERNAGROD_H

#include <QMap>
#include "mistrzgry.h"
#include "gra.h"
#include "nagroda.h"

class MistrzGry;

class ParserNagrod
{
public:
	ParserNagrod(MistrzGry* mistrz);
	bool bladWczytywania();
	QString trescBledu;
private:
	bool bylBlad;
	MistrzGry* mistrzGry;
	bool wczytajDane(QTextStream* wejscie);
	QString nastepny(QTextStream* wejscie);

	struct informacje{
		int id;
		int* reputacja;
		int zloto;
		int doswiadczenie;
		QStringList grupy;
		QList<int>* przedmioty;
	};
};

#endif // PARSERNAGROD_H
