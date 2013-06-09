#ifndef EKWIPUNEK_H
#define EKWIPUNEK_H
#include "przedmiot.h"
#include <QList>
#include "gra.h"

class Ekwipunek
{
public:
	Ekwipunek();

	quint8 getMalePoty();
	quint8 getDuzePoty();
	void setMalePoty(quint8 ilosc);
	void setDuzePoty(quint8 ilosc);

private:
	Przedmiot* glowa;
	Przedmiot* tulw;
	Przedmiot* lewaReka;
	Przedmiot* prawaReka;
	QList<Przedmiot> plecak;
	quint8 malePoty;
	quint8 duzePoty;
};

#endif // EKWIPUNEK_H
