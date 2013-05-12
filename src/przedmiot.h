#ifndef PRZEDMIOT_H
#define PRZEDMIOT_H
#include <QString>
#include "gra.h"

class Przedmiot
{
public:
	Przedmiot( QString nazwa, quint8 wartosc, QString opis, bool czyPo5Lvlu, quint8 ograniczenia, RodzajPrzedmiotu rodzaj );

	QString getNazwa();
	quint8 getWartosc();
	QString getOpis();
	bool getCzyPo5Lvlu();
	quint8 getOgraniczenia();
	RodzajPrzedmiotu getRodzaj();

private:
	QString nazwa;
	quint8 wartosc;
	QString opis;
	bool czyPo5Lvlu;
	quint8 ograniczenia;
	RodzajPrzedmiotu rodzaj;

};

#endif /* PRZEDMIOT_H */
