#ifndef QUESTPARSER_H
#define QUESTPARSER_H

#include "Core/Containers/Enemy.h"
#include "Core/Containers/Field.h"
#include "Core/Containers/Quest.h"
#include "Core/GameMaster.h"

class GameMaster;

class QuestParser {
public:
	QuestParser(GameMaster *mistrz);
	bool bladWczytywania();
	QString trescBledu;
private:
	quint8 wysokoscPlanszy;
	quint8 szerokoscPlanszy;
	bool bylBlad;
	GameMaster *mistrzGry;
	bool wczytajWymiary(QTextStream *wejscie);
	bool wczytajDane(QTextStream *wejscie);
	QString nastepny(QTextStream *wejscie);

	struct informacje {
		int id;
		QuestType rodzaj;
		int frakcja;
		QString tytul;
		QString tresc;
		bool czyPowrot;
		FieldId cel;
		char kolorCzcionki;
		int idNagrody;
		QList <Enemy *> *idWrogow;
	};
};

#endif
