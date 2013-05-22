#ifndef POLE_H
#define POLE_H
#include "gra.h"

class Pole
{
public:
	Pole(IDPola miejsce, QString nazwa, quint8 wspolczynnik, bool czyPoleZPrzeciwnikiem, QString plikZObrazkiem);
	IDPola getMiejsce();
	QString getNazwa();
	quint8 getWspolczynnik();
	bool getCzyPoleZPrzeciwnikiem();
	QString getPlikZObrazkiem();
private:
	IDPola miejsce;
	QString nazwa;
	quint8 wspolczynnik;
	bool czyPoleZPrzeciwnikiem;
	QString plikZObrazkiem;
};

#endif // POLE_H
