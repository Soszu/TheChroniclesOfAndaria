#ifndef PIONEK_H
#define PIONEK_H

#include <QGraphicsItem>
#include <QPainter>

class Pionek : public QGraphicsItem
{
public:
	explicit Pionek(QColor kolor, QPointF srodek, qreal promien);
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	void setPromien(qreal promien);
private:
	QColor kolor;
	qreal promien;
signals:

public slots:

};

#endif // PIONEK_H
