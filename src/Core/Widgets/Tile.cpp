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

Tile::Tile(const Terrain * terrain) :
	sideSize_(DefaultSideSize),
	terrain_(terrain)
{}

qreal Tile::sideSize() const
{
	return sideSize_;
}

qreal Tile::height() const
{
	if (sideSize_ <= 0)
		return 0;
	return sideSize_ * qSqrt(3);
}

qreal Tile::width() const
{
	if (sideSize_ <= 0)
		return 0;
	return sideSize_ * 2;
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

void Tile::setSideSize(qreal sideSize)
{
	sideSize_ = sideSize;
}

void Tile::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	if (terrain_ == nullptr) {
		painter->drawRect(sideSize_ / 2, sideSize_ / 2, sideSize_ / 2, sideSize_ / 2);
		return;
	}

	painter->setRenderHint(QPainter::SmoothPixmapTransform);
	painter->drawPixmap(boundingRect().toRect(),
	                    DataManager::pixmap(resolveTerrainPath(terrain_->pixmapName())));

}

const qreal Tile::DefaultSideSize = 30;
