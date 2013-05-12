#ifndef PRZECIWNIK_H
#define PRZECIWNIK_H
#include <QString>
#include "nagroda.h"
class Przeciwnik
{
public:
	Przeciwnik(QString nazwa, quint8 atak, quint8 obrona, quint8 zdrowieMaks, quint8 zdrowieAktualne, Nagroda* nagroda);

	QString getNazwa();
	quint8 getAtak();
	quint8 getObrona();
	quint8 getZdrowieMaks();
	quint8 getZdrowieAktualne();
	Nagroda* getNagroda();

private:
	QString nazwa;
	quint8 atak;
	quint8 obrona;
	quint8 zdrowieMaks;
	quint8 zdrowieAktualne;
	Nagroda* nagroda;

};

#endif // PRZECIWNIK_H
