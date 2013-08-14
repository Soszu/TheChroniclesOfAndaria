#ifndef HEX_H
#define HEX_H

#include <QGraphicsItem>
#include <QPainter>
#include <QVector>
#include "obszarplanszy.h"
#include "pole.h"
#include "gra.h"

class ObszarPlanszy;

class Hex : public QGraphicsItem
{
public:
	explicit Hex(Pole* pole, qreal bok, ObszarPlanszy* obszar);
	QRectF boundingRect() const;
	QPainterPath shape();
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	void setBok(qreal bok);
	void setPodswietlenie(bool opcja);
	void zaznacz();
	void odznacz();
private:
	static const int MAX_SIZE_PRZED_SCISKANIEM = 8;
	qreal bok;
	qreal wysokosc;
	Pole* pole;
	ObszarPlanszy* obszarPlanszy;
	bool podswietlenie;
	bool zaznaczenie;
	QPainterPath ksztaltZaznaczenia();
	QVector<QPointF> podajWierzcholki();

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // HEX_H
