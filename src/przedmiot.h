#ifndef PRZEDMIOT_H
#define PRZEDMIOT_H
#include <QString>

class Przedmiot
{
public:
	Przedmiot( QString nazwa, short wartosc, QString opis, bool czyPo5Lvlu, short ograniczenia, int rodzaj );

private:
	QString nazwa;
	short wartosc;
	QString opis;
	bool czyPo5Lvlu;

	short ograniczenia;
	int rodzaj;

	QString getNazwa();
	short getWartosc();
	QString getOpis();
	bool getCzyPo5Lvlu();
	short getOgraniczenia();
	int getRodzaj();
};

#endif /* PRZEDMIOT_H */
