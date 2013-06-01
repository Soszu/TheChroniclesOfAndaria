#ifndef POLE_H
#define POLE_H
#include "gra.h"

class Pole
{
public:
	Pole(IDPola miejsce, QString nazwa, quint8 wspolczynnik, bool czyPoleZPrzeciwnikiem, bool czyPoleZMiastem, QString plikZObrazkiem);
	IDPola getMiejsce();
	QString getNazwa();
	quint8 getWspolczynnik();
	bool getCzyPoleZPrzeciwnikiem();
	bool getCzyPoleZMiastem();
	QString getPlikZObrazkiem();
private:
	IDPola miejsce;
	QString nazwa;
	quint8 wspolczynnik;
	bool czyPoleZPrzeciwnikiem;
	bool czyPoleZMiastem;
	QString plikZObrazkiem;
};

#endif // POLE_H
