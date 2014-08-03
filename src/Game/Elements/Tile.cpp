/*
Copyright (C) 2013-2014 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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

#include "Game/Elements/Tile.h"

Tile::Tile(const Field *field, qreal side)
	: side_(side), height_(BoardArea::calcHeight(side_)), field_(field), boardArea_(boardArea),
	highlighted_(false), selected_(false), framed_(false), tilePath_(Paths::HexesPrefix + field_->imageFile())
{
	setPos(BoardArea::calcCenter(field_->fieldId(), side_));
	setAcceptHoverEvents(true);
}

QRectF Tile::boundingRect() const
{
	QPointF origin(-height_, -side_);
	QSizeF size(2 * height_, 2 * side_);
	return QRectF(origin, size);
}

QPainterPath Tile::shape() const
{
	QPainterPath result;
	result.addPolygon(QPolygonF(tileVertices(1)));
	result.closeSubpath();
	return result;
}

void Tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setRenderHint(QPainter::SmoothPixmapTransform);
	painter->drawPixmap(boundingRect().toRect(), DataManager::pixmap(tilePath_));

	if (field_->hasEnemy()) {
		QPointF swordShift(height_ * 0.7, side_ * 0.3);
		QRectF swordRect(boundingRect().topLeft() + swordShift, boundingRect().size() * 0.3);

		painter->drawPixmap(swordRect.toRect(), DataManager::pixmap(Paths::IconFightSymbol));
	}

	if (field_->hasCity()) {
		QPointF textShift(0, side_ * 1.24);
		QRectF textRect(boundingRect().topLeft() + textShift, boundingRect().size());

		QFont font("OldEnglish", side_ * 0.2, QFont::Bold);
		if (field_->name().size() >= MaxSizeBeforeSqueeze)
			font.setStretch(100 * MaxSizeBeforeSqueeze / field_->name().size()); //squeeze font for long city names
		painter->setFont(font);
		painter->setPen(QPen(QColor(Qt::red)));
		painter->drawText(textRect, Qt::AlignHCenter, field_->name());
	}

	if (highlighted_)
		painter->fillPath(shape(), QBrush(Qt::gray, Qt::Dense7Pattern));

	if (framed_) {
		QPainterPath figura;
		figura.addPolygon(QPolygonF(tileVertices(0.9)));
		figura.closeSubpath();
		painter->setPen(QPen(QBrush(Qt::white), side_ / 5));
		painter->drawPath(figura);
	}

	if (selected_) {
		painter->setPen(QPen(QBrush(Qt::white), side_ / 10));
		painter->drawPath(selectionShape());
	}
}

void Tile::setSide(qreal side)
{
	this->side_ = side;
	this->height_ = BoardArea::calcHeight(side);
	setPos(BoardArea::calcCenter(field_->fieldId(), side));
}

void Tile::setHighlighted(bool highlighted)
{
	this->highlighted_ = highlighted;
	update(boundingRect());
}

QVector<QPointF> Tile::tileVertices(qreal x) const
{
	QVector<QPointF> wierzcholki;
	wierzcholki << QPointF(0, -side_ * x) << QPointF(height_ * x, (-side_ / 2) * x)
	            << QPointF( height_ * x, (side_ / 2) * x) << QPointF(0, side_ * x)
	            << QPointF(-height_ * x, (side_ / 2) * x) << QPointF(-height_ * x, (-side_/ 2) * x);
	return wierzcholki;
}

void Tile::select()
{
	selected_ = true;
	update(boundingRect());
}

void Tile::deselect()
{
	selected_ = false;
	update(boundingRect());
}

void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	emit clicked(field_->fieldId());
}

void Tile::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
	//TODO: make it work
	/*
	QMenu menu;
	menu.addAction("Informacje o polu");
	if(pole->hasCity())
		menu.addAction(QString::fromUtf8("Zawartość bazaru"));
	QAction *a = menu.exec(event->screenPos());
	qDebug("User clicked %s", qPrintable(a->text()));
	*/
}

void Tile::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
	framed_ = true;
	emit mouseEntered(field_->fieldId());
	update();
}

void Tile::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
	framed_ = false;
	update();
}

QPainterPath Tile::selectionShape()
{
	QPainterPath cross;
	cross.moveTo(QPointF(0, -side_));
	cross.lineTo(QPointF(0,  side_));
	cross.moveTo(QPointF( height_, -side_ / 2));
	cross.lineTo(QPointF(-height_,  side_ / 2));
	cross.moveTo(QPointF( height_,  side_ / 2));
	cross.lineTo(QPointF(-height_, -side_ / 2));

	return cross;
}
