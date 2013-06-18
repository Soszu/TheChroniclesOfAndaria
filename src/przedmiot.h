#ifndef PRZEDMIOT_H
#define PRZEDMIOT_H
#include <QString>
#include "gra.h"

class Przedmiot
{
public:
	Przedmiot(QString nazwa,
		  RodzajPrzedmiotu rodzaj,
		  quint8 bonusAWrecz,
		  quint8 bonusADystansowy,
		  quint8 bonusAMagiczny,
		  quint8 bonusObrona,
		  quint8 bonusPercepcja,
		  quint8 bonusHP,
		  quint8 bonusHPregen,
		  int ograniczenia,
		  quint8 wartosc,
		  bool czyMocny,
		  QColor kolorCzcionki);

	QString getNazwa();
	RodzajPrzedmiotu getRodzaj();
	quint8 getBonusAWrecz();
	quint8 getBonusADystansowy();
	quint8 getBonusAMagiczny();
	quint8 getBonusObrona();
	quint8 getBonusPercepcja();
	quint8 getBonusHP();
	quint8 getBonusHPregen();
	int getOgraniczenia();
	quint8 getWartosc();
	bool getCzyMocny();
	QColor getKolorCzcionki();

private:
	QString nazwa;
	RodzajPrzedmiotu rodzaj;
	quint8 bonusAWrecz;
	quint8 bonusADystansowy;
	quint8 bonusAMagiczny;
	quint8 bonusObrona;
	quint8 bonusPercepcja;
	quint8 bonusHP;
	quint8 bonusHPregen;
	int ograniczenia;
	quint8 wartosc;
	bool czyMocny;
	QColor kolorCzcionki;

};

#endif /* PRZEDMIOT_H */
