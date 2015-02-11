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
#include "Core/Widgets/Map.hpp"

#include "Core/Containers/Models/BoardModel.hpp"
#include "Core/Widgets/Tile.hpp"

Map::Map(BoardModel * board) :
	board_(board)
{
	repaint();
}

void Map::repaint()
{
	clear();

	for (int row = 0; row < board_->rowCount(); ++row)
		for (int column = 0; column < board_->columnCount(); ++column) {
			Tile * tile = new Tile(board_->terrain(Coordinates(row, column)));

			qreal xPos = column * tile->boundingRect().width();
			if (row % 2 == 1) xPos += tile->width() / 2;

			qreal yPos = row * tile->boundingRect().height();
			yPos -= row * tile->height() / 4;

			tile->setPos(xPos, yPos);

			addItem(tile);
		}
}
