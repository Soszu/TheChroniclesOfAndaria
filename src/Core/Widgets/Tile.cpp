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
#include "Tile.hpp"

#include "Core/Containers/Terrain.hpp"
#include "Core/Paths.hpp"
#include "Core/DataManager.hpp"

const qreal Tile::SideSize = 32;

Tile::Tile(const Coordinates & coords, const Terrain * terrain) :
	coords_(coords),
	terrain_(terrain)
{}

qreal Tile::height() const
{
	return SideSize * qSqrt(3);
}

qreal Tile::width() const
{
	return SideSize * 2;
}

const Coordinates & Tile::coords() const
{
	return coords_;
}

QVector<QPointF> Tile::nodes()
{
// 	qreal h = height();
// 	qreal w = width();
	//TODO rewrite rotated
// 	return {{w / 4, 0}, {w - (w / 4), 0}, {w, h / 2}, {w - (w / 4), h}, {w / 4, h}, {0, h / 2}};
	return {};
}

QRectF Tile::boundingRect() const
{
	return QRectF(0, 0, width(), height());
}

void Tile::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	if (terrain_ == nullptr) {
		painter->drawRect(SideSize / 2, SideSize / 2, SideSize / 2, SideSize / 2);
		return;
	}

	painter->setRenderHint(QPainter::SmoothPixmapTransform);
	painter->drawPixmap(boundingRect().toRect(),
	                    DataManager::pixmap(resolveTerrainPath(terrain_->pixmapName())));
}

