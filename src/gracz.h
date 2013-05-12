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
	Gracz(QColor kolor, QString nazwa, Rasa rasa, Klasa klasa);
	virtual ~Gracz();

	QColor kolor;
	QString nazwa;
	Rasa rasa;
	Klasa klasa;
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

private:
	void przepiszStaty(statystyka konkret);

};

#endif /* GRACZ_H */
