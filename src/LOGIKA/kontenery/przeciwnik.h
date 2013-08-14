#ifndef PRZECIWNIK_H
#define PRZECIWNIK_H
#include <QString>
#include "nagroda.h"
class Przeciwnik
{
public:
	Przeciwnik(QString nazwa, QString nazwaObrazka, int atakMinimalny, int atakMaksymalny, int obrona, int percepcja, int zdrowieMaks, Nagroda* nagroda);

	QString getNazwa();
	QString getNazwaObrazka();
	int getAtakMinimalny();
	int getAtakMaksymalny();
	int getObrona();
	int getPercepcja();
	int getZdrowieMaks();
	Nagroda* getNagroda();
private:
	QString nazwa;
	QString nazwaObrazka;
	int atakMinimalny;
	int atakMaksymalny;
	int obrona;
	int percepcja;
	int zdrowieMaks;
	Nagroda* nagroda;
};

#endif // PRZECIWNIK_H
