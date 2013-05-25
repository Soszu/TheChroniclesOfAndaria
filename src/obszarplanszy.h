#ifndef OBSZARPLANSZY_H
#define OBSZARPLANSZY_H

#include <QGraphicsScene>
#include <QPainter>
#include <QList>
#include <QPair>
#include <QKeyEvent>
#include <QtCore>
#include <QTimeLine>
#include "plansza.h"
#include "gracz.h"
#include "gra.h"
#include "pole.h"
#include "hex.h"
#include "pionek.h"

class Plansza;
class Hex;
class Pionek;

class ObszarPlanszy : public QGraphicsScene
{
	Q_OBJECT
public:
	explicit ObszarPlanszy();
	void setPlansza(Plansza* plansza);
	void narysujPlansze(QList<Pole*>* pola, int kolumny, int wiersze, QList<QPair<QColor, IDPola> > *pozycjeGraczy);

	void kliknietoHex(IDPola id);
	void wykonajRuch(QList<IDPola> droga, int indeks);
	void podswietl(QList<IDPola> lista);
	bool animacjaTrwa();

	static QPointF podajSrodek(const IDPola id, const qreal bok);
	static qreal podajWysokosc(qreal bok);
private:
	static const qreal POCZATKOWY_ROZMIAR_HEXA = 20;
	static const qreal MAKSYMALNY_ROZMIAR_HEXA = 80;
	static const qreal MINIMALNY_ROZMIAR_HEXA = 10;

	qreal bokHexa;
	Plansza *plansza;
	int wiersze;
	int kolumny;

	QList<Pole*>* pola;
	QList<Hex*> hexy;
	QList<Pionek*> pionki;
	QList<int> podswietlone; //indeksy podswietlonych pol
	QList<QPair<QColor, IDPola> >* pozycjeGraczy;

	QRectF podajOgraniczenie();
	void zmienRozmiar(int d);
	QPointF podajSrodekPionka(int indeks);

	QTimeLine* ticTac;
	int indeksAnimowanego;
	QList<IDPola> doAnimacji;
	QPointF poczatekAnimacji;
	QPointF koniecAnimacji;

protected:
	void keyReleaseEvent(QKeyEvent *event);
signals:

private slots:
	void kolejnePrzejscie();
	void krokAnimacji(int faza);

};

#endif // OBSZARPLANSZY_H
