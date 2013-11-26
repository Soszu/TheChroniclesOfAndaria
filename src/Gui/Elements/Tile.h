#ifndef TILE_H
#define TILE_H

#include <QtGui>
#include "Core/Containers/Field.h"
#include "Gui/BoardArea.h"

class BoardArea;

class Tile : public QGraphicsItem {

public:
	Tile(Field *field, qreal side, BoardArea *boardArea);
	QRectF boundingRect() const;
	QPainterPath shape() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	void setSide(qreal side);
	void setHighlighted(bool highlighted);
	void select();
	void deselect();

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
	void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
	static const int MaxSizeBeforeSqueeze = 8;

	QPainterPath selectionShape();
	QVector <QPointF> tileVertices(qreal x) const;

	qreal side_;
	qreal height_;
	Field *field_;
	BoardArea *boardArea_;
	bool highlighted_;
	bool selected_;
	bool framed_;
};

#endif
