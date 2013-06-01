#ifndef PRZECIWNIK_H
#define PRZECIWNIK_H
#include <QString>
#include "nagroda.h"
class Przeciwnik
{
public:
	Przeciwnik(QString nazwa, QString nazwaObrazka, QString opis, quint8 atakMinimalny, quint8 atakMaksymalny, quint8 obrona, quint8 zdrowieMaks, Nagroda* nagroda);

	QString getNazwa();
	QString getNazwaObrazka();
	QString getOpis();
	quint8 getAtakMinimalny();
	quint8 getAtakMaksymalny();
	quint8 getObrona();
	quint8 getZdrowieMaks();
	quint8 getZdrowieAktualne();
	Nagroda* getNagroda();
private:
	QString nazwa;
	QString nazwaObrazka;
	QString opis;
	quint8 atakMinimalny;
	quint8 atakMaksymalny;
	quint8 obrona;
	quint8 zdrowieMaks;
	quint8 zdrowieAktualne;
	Nagroda* nagroda;
};

#endif // PRZECIWNIK_H
