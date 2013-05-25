#ifndef GRACZ_H
#define GRACZ_H
#include <QColor>
#include <QString>
#include <QList>
#include <QDebug>
#include "gra.h"
#include "zadanie.h"
#include "ekwipunek.h"

class Gracz
{
public:
	Gracz(QString nazwa, Rasa rasa, Klasa klasa, QColor kolor, bool czyAI);
	virtual ~Gracz();
	QString getNazwa();
	Rasa getRasa();
	Klasa getKlasa();
	QColor getKolor();
	bool getCzyAI();
	IDPola getPozycja();
	void setPozycja(IDPola id);
	Ekwipunek* getEkwipunek();
	QList<Zadanie*> getZadania();
	QList<IDPola> getPolaSzczegolne();
	quint8 getPoziom();
	quint8* getReputacja();
	quint8 getZdrowieMaks();
	quint8 getZdrowieAktualne();
	quint8 getRegeneracja();
	quint8 getAtakWrecz();
	quint8 getAtakDystansowy();
	quint8 getAtakMagiczny();
	quint8 getObrona();
	quint8 getPercepcja();
	quint8 getPunktyRuchu();
	quint16 getZloto();
	quint16 getDoswiadczenie();


private:
	QString nazwa;
	Rasa rasa;
	Klasa klasa;
	QColor kolor;
	bool czyAI;
	IDPola pozycja;
	Ekwipunek* ekwipunek;
	QList<Zadanie*> zadania;
	QList<IDPola> polaSzczegolne;
	quint8 poziom;
	quint8 reputacja[LICZBA_KROLESTW];
	quint8 zdrowieMaks;
	quint8 zdrowieAktualne;
	quint8 regeneracja;
	quint8 atakWrecz;
	quint8 atakDystansowy;
	quint8 atakMagiczny;
	quint8 obrona;
	quint8 percepcja;
	quint8 punktyRuchu;
	quint16 zloto;
	quint16 doswiadczenie;
	void przepiszStaty(statystyka konkret);

};

#endif /* GRACZ_H */
