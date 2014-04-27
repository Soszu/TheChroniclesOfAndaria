/*
Copyright (C) 2013 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
This file is part of The Chronicles Of Andaria Project.

	The Chronicles of Andaria Project is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	The Chronicles of Andaria Project is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with The Chronicles Of Andaria.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TILE_H
#define TILE_H

#include <QtGui>
#include "Core/DataManager.h"
#include "Core/Containers/Field.h"
#include "Game/BoardArea.h"

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
	QString tilePath_;
};

#endif
