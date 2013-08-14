#ifndef PARSERZADAN_H
#define PARSERZADAN_H

#include <QtCore>
#include "gra.h"
#include "mistrzgry.h"
#include "zadanie.h"
#include "przeciwnik.h"

class MistrzGry;

class ParserZadan
{
public:
	ParserZadan(MistrzGry* mistrz);
	bool bladWczytywania();
	QString trescBledu;
private:
	quint8 wysokoscPlanszy;
	quint8 szerokoscPlanszy;
	bool bylBlad;
	MistrzGry* mistrzGry;
	bool wczytajWymiary(QTextStream* wejscie);
	bool wczytajDane(QTextStream* wejscie);
	QString nastepny(QTextStream* wejscie);

	struct informacje{
		int id;
		RodzajZadania rodzaj;
		QString tytul;
		QString tresc;
		bool czyPowrot;
		IDPola cel;
		char kolorCzcionki;
		int idNagrody;
		QList<Przeciwnik*>* idPrzeciwnikow;
	};
};

#endif // PARSERZADAN_H
