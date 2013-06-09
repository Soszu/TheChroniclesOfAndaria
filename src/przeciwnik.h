#ifndef PRZECIWNIK_H
#define PRZECIWNIK_H
#include <QString>
#include "nagroda.h"
class Przeciwnik
{
public:
	Przeciwnik(QString nazwa, QString nazwaObrazka, QString opis, quint8 atakMinimalny, quint8 atakMaksymalny, quint8 obrona, quint8 percepcja, quint8 zdrowieMaks, Nagroda* nagroda);

	QString getNazwa();
	QString getNazwaObrazka();
	QString getOpis();
	quint8 getAtakMinimalny();
	quint8 getAtakMaksymalny();
	quint8 getObrona();
	quint8 getPercepcja();
	quint8 getZdrowieMaks();
	Nagroda* getNagroda();
private:
	QString nazwa;
	QString nazwaObrazka;
	QString opis;
	quint8 atakMinimalny;
	quint8 atakMaksymalny;
	quint8 obrona;
	quint8 percepcja;
	quint8 zdrowieMaks;
	Nagroda* nagroda;
};

#endif // PRZECIWNIK_H
