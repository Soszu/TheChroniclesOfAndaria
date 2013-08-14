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

	Przedmiot* getGlowa();
	void setGlowa(Przedmiot* rzecz);
	Przedmiot* getTuluw();
	void setTuluw(Przedmiot* rzecz);
	Przedmiot* getLewaReka();
	void setLewaReka(Przedmiot* rzecz);
	Przedmiot* getPrawaReka();
	void setPrawaReka(Przedmiot* rzecz);

	quint8 getMalePoty();
	void setMalePoty(quint8 ilosc);
	quint8 getDuzePoty();
	void setDuzePoty(quint8 ilosc);
	QList<Przedmiot*>* getPlecak();
	QList<Przedmiot*>* getZalozoneArtefakty();

private:
	Przedmiot* glowa;
	Przedmiot* tuluw;
	Przedmiot* lewaReka;
	Przedmiot* prawaReka;
	QList<Przedmiot*> zalozoneArtefakty;
	QList<Przedmiot*>* plecak;
	quint8 malePoty;
	quint8 duzePoty;
};

#endif // EKWIPUNEK_H
