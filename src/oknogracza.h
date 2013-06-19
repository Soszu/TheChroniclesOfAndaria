#ifndef OKNOGRACZA_H
#define OKNOGRACZA_H

#include "gracz.h"
#include "gra.h"
#include <QFrame>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include "mojpasek.h"
#include "oknoekwipunek.h"
#include "oknozadania.h"

class OknoEkwipunek;
class OknoZadania;
class MistrzGry;

class OknoGracza : public QObject
{
	friend class OknoEkwipunek;
	Q_OBJECT

public:
	OknoGracza(QFrame *rama);
	void wyswietlGracza(Gracz* gracz);
	void uaktualnijInformacje();
	void setMistrzGry(MistrzGry* mistrz);
private:
	MistrzGry* mistrz;
	OknoEkwipunek* oknoEkwipunek;
	OknoZadania* oknoZadania;
	Gracz* aktualnyGracz;

	QVBoxLayout* layoutGlowny;
	QHBoxLayout* reputacja;
	QHBoxLayout* linijkaZdrowia;
	QHBoxLayout* linijkaDoswiadczenia;
	QHBoxLayout* linijkaObrony;
	QHBoxLayout* linijkaAtakow;
	QHBoxLayout* linijkaZlota;
	QHBoxLayout* linijkaPrzyciskow;

	QLabel* pierwszaLinijka;

	QLabel* opisPrzedZdrowiem;
	MojPasek* wskaznikZdrowia;
	QLabel* opisPoZdrowiu;

	QLabel* opisPrzedDoswiadczeniem;
	MojPasek* wskaznikDoswiadczenia;
	QLabel* opisPoDoswiadczeniu;

	QVBoxLayout* slupkiLayouts[LICZBA_KROLESTW];
	QLabel* podpisy[LICZBA_KROLESTW];
	MojPasek* slupki[LICZBA_KROLESTW];

	QLabel* obrona;
	QLabel* obronaIkona;
	QLabel* percepcja;
	QLabel* percepcjaIkona;
	QLabel* ruch;
	QLabel* ruchIkona;

	QLabel* wrecz;
	QLabel* wreczIkona;
	QLabel* dystans;
	QLabel* dystansIkona;
	QLabel* magia;
	QLabel* magiaIkona;

	QLabel* zloto;
	QLabel* zlotoIkona;

	QPushButton* ekwipunek;
	QPushButton* zadania;

	QString odmiana(int n);

private slots:
	void pokazEkwipunek();
	void pokazZadania();
};

#endif // OKNOGRACZA_H
