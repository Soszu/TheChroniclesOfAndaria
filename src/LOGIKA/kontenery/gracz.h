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
	QList<Zadanie *> *getZadania();
	Zadanie* getKonkretneZadanie(int indeks);
	void usunKonkretneZadanie(int id);
	QList<IDPola> getPolaSzczegolne();
	quint8 getPoziom();
	void setPoziom(quint8 poziom);
	int* getReputacja();
	void setKonkretnaReputacja(int wartosc, int indeks);
	int getZdrowieMaks();
	void setZdrowieMaks(int wartosc);
	int getZdrowieAktualne();
	void setZdrowieAktualne(int zdrowie);
	int getRegeneracja();
	void setRegeneracja(int wartosc);
	int getAtakWrecz();
	void setAtakWrecz(int wartosc);
	int getAtakDystansowy();
	void setAtakDystansowy(int wartosc);
	int getAtakMagiczny();
	void setAtakMagiczny(int wartosc);
	int getObrona();
	void setObrona(int wartosc);
	int getPercepcja();
	void setPercepcja(int wartosc);
	quint8 getPunktyRuchu();
	void setPunktyRuchu(quint8 wartosc);
	quint16 getZloto();
	void setZloto(quint16 wartosc);
	quint16 getDoswiadczenie();
	void setDoswiadczenie(quint16 wartosc);
	bool getOstatnioWalczyl();
	void setOstatnioWalczyl(bool wartosc);
	void setCzyAktywny(bool wartosc);
	bool getCzyAktywny();

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
	int reputacja[LICZBA_KROLESTW];
	int zdrowieMaks;
	int zdrowieAktualne;
	int regeneracja;
	int atakWrecz;
	int atakDystansowy;
	int atakMagiczny;
	int obrona;
	int percepcja;
	quint8 punktyRuchu;
	quint16 zloto;
	quint16 doswiadczenie;
	bool ostatnioWalczyl;
	bool czyAktywny;
	void przepiszStaty(statystyka konkret);

};

#endif /* GRACZ_H */
