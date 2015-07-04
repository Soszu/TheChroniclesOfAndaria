/*
Copyright (C) 2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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
#include "Core/Widgets/MapView.hpp"

#include "Core/Widgets/Tile.hpp"

MapView::MapView()
{
	setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
}

void MapView::wheelEvent(QWheelEvent * event)
{
	QPoint numDegrees = event->angleDelta() / 8;
	qreal steps = numDegrees.y() / 15;
	qreal newScale = 1 + (steps * 0.2);
	scale(newScale, newScale);

	QGraphicsView::wheelEvent(event);
}

void MapView::mouseReleaseEvent(QMouseEvent * event)
{
	Tile * tile = dynamic_cast<Tile *>(itemAt(event->pos()));
	if (tile == nullptr)
		return;

	emit tileClicked(tile);

	QGraphicsView::mouseReleaseEvent(event);
}
