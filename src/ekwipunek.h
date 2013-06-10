#ifndef EKWIPUNEK_H
#define EKWIPUNEK_H
#include "przedmiot.h"
#include <QList>
#include "gra.h"

class Ekwipunek
{
public:
	Ekwipunek();
	~Ekwipunek();

	quint8 getMalePoty();
	void setMalePoty(quint8 ilosc);
	quint8 getDuzePoty();
	void setDuzePoty(quint8 ilosc);
	QList<Przedmiot*>* getPlecak();


private:
	Przedmiot* glowa;
	Przedmiot* tulw;
	Przedmiot* lewaReka;
	Przedmiot* prawaReka;
	QList<Przedmiot*>* plecak;
	quint8 malePoty;
	quint8 duzePoty;
};

#endif // EKWIPUNEK_H
