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
	void setPoziom(quint8 poziom);
	quint8* getReputacja();
	void setKonkretnaReputacja(int wartosc, int indeks);
	quint8 getZdrowieMaks();
	void setZdrowieMaks(quint8 wartosc);
	quint8 getZdrowieAktualne();
	void setZdrowieAktualne(quint8 zdrowie);
	quint8 getRegeneracja();
	void setRegeneracja(quint8 wartosc);
	quint8 getAtakWrecz();
	void setAtakWrecz(quint8 wartosc);
	quint8 getAtakDystansowy();
	void setAtakDystansowy(quint8 wartosc);
	quint8 getAtakMagiczny();
	void setAtakMagiczny(quint8 wartosc);
	quint8 getObrona();
	void setObrona(quint8 wartosc);
	quint8 getPercepcja();
	void setPercepcja(quint8 wartosc);
	quint8 getPunktyRuchu();
	void setPunktyRuchu(quint8 wartosc);
	quint16 getZloto();
	void setZloto(quint16 wartosc);
	quint16 getDoswiadczenie();
	void setDoswiadczenie(quint16 wartosc);


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
