#ifndef PRZEDMIOT_H
#define PRZEDMIOT_H
#include <QString>
#include "gra.h"

class Przedmiot
{
public:
	Przedmiot(QString nazwa,
		  RodzajPrzedmiotu rodzaj,
		  int bonusAWrecz,
		  int bonusADystansowy,
		  int bonusAMagiczny,
		  int bonusObrona,
		  int bonusPercepcja,
		  int bonusHP,
		  int bonusHPregen,
		  int ograniczenia,
		  int wartosc,
		  bool czyMocny,
		  QColor kolorCzcionki);

	QString getNazwa();
	RodzajPrzedmiotu getRodzaj();
	int getBonusAWrecz();
	int getBonusADystansowy();
	int getBonusAMagiczny();
	int getBonusObrona();
	int getBonusPercepcja();
	int getBonusHP();
	int getBonusHPregen();
	int getOgraniczenia();
	int getWartosc();
	bool getCzyMocny();
	QColor getKolorCzcionki();

private:
	QString nazwa;
	RodzajPrzedmiotu rodzaj;
	int bonusAWrecz;
	int bonusADystansowy;
	int bonusAMagiczny;
	int bonusObrona;
	int bonusPercepcja;
	int bonusHP;
	int bonusHPregen;
	int ograniczenia;
	int wartosc;
	bool czyMocny;
	QColor kolorCzcionki;

};

#endif /* PRZEDMIOT_H */
