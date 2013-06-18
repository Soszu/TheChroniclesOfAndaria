#ifndef OBSZARPLANSZY_H
#define OBSZARPLANSZY_H

#include <QGraphicsScene>
#include <QPainter>
#include <QList>
#include <QPair>
#include <QKeyEvent>
#include <QtCore>
#include <QTimeLine>
#include "mainwindow.h"
#include "plansza.h"
#include "gracz.h"
#include "gra.h"
#include "pole.h"
#include "hex.h"
#include "pionek.h"

class Plansza;
class Hex;
class Pionek;
class MainWindow;

class ObszarPlanszy : public QGraphicsScene
{
	Q_OBJECT
public:
	explicit ObszarPlanszy(MainWindow* mainWindow);
	~ObszarPlanszy();
	void setPlansza(Plansza* plansza);
	void narysujPlansze(QList<Pole*>* pola, int kolumny, int wiersze, QList<QPair<QColor, IDPola> > *pozycjeGraczy);

	void kliknietoHex(IDPola id);
	void wykonajRuch(QList<IDPola> droga, int indeks);
	void podswietl(QList<IDPola> lista);
	void pokazHex(int indeks);
	bool animacjaTrwa();

	static QPointF podajSrodek(const IDPola id, const qreal bok);
	static qreal podajWysokosc(qreal bok);
private:
	MainWindow* mainWindow;

	qreal bokHexa;
	Plansza *plansza;
	int wiersze;
	int kolumny;

	QList<Pole*>* pola;
	QList<Hex*> hexy;
	QList<Pionek*> pionki;
	QList<int> podswietlone; //indeksy podswietlonych pol
	QList<QPair<QColor, IDPola> >* pozycjeGraczy;

	Hex* zaznaczony;

	QRectF podajOgraniczenie();
	void zmienRozmiar(int d);
	QPointF podajSrodekPionka(int indeks);

	QTimeLine* ticTac;
	QTimeLine* zegarPodswietlenia;
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
	void usunZaznaczenie();
};

#endif // OBSZARPLANSZY_H
