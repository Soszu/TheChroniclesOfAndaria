#ifndef PLAYERMARKER_H
#define PLAYERMARKER_H

#include <QtWidgets>

class PlayerMarker : public QGraphicsItem {

public:
	PlayerMarker(QColor color, QString description, QPointF center, qreal radius);
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	void setRadius(qreal radius);

private:
	QColor color_;
	qreal radius_;
};

#endif
