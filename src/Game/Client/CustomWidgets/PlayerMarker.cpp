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

#include "Game/Elements/PlayerMarker.h"

PlayerMarker::PlayerMarker(QColor color, QPointF srodek, qreal radius)
	: color_(color), radius_(radius)
{
	setPos(srodek);
}

QRectF PlayerMarker::boundingRect() const
{
	QPointF origin(-radius_, -radius_);
	QSizeF size(2 * radius_, 2 * radius_);
	return QRectF(origin, size);
}

void PlayerMarker::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setRenderHint(QPainter::Antialiasing);
	QRadialGradient radialGradient(QPointF(0,0), radius_);
	radialGradient.setColorAt(0, Qt::white);
	radialGradient.setColorAt(1, color_);
	painter->setBrush(QBrush(radialGradient));
	painter->setPen(color_);
	painter->drawEllipse(QPointF(0,0), radius_, radius_);
}

void PlayerMarker::setRadius(qreal radius)
{
	this->radius_ = radius;
}
