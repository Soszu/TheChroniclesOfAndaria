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
#include "Core/Containers/Board.hpp"

const Terrain Board::NullTerrain;

Board::Board() :
	size_(QSize(1, 1))
{
	Coordinates coords(0, 0);
	fields_.insert(coords, NullTerrainUid);
	rulers_.insert(coords, Kingdom::Neutral);
	for (Race &race : RaceLabels.leftKeys())
		initialPositions_[race] = coords;
}

const QSize & Board::size() const
{
	return size_;
}

int Board::columnCount() const
{
	return size_.width();
}

int Board::rowCount() const
{
	return size_.height();
}

Terrain Board::terrain(const Coordinates coords) const
{
	if (fields_[coords] == NullTerrainUid)
		return NullTerrain;

	return terrains_[fields_[coords]];
}

Kingdom Board::ruler(const Coordinates coords) const
{
	return rulers_[coords];
}

Coordinates Board::initialPosition(Race race) const
{
	return initialPositions_[race];
}

const QHash<Race, Coordinates> & Board::initialPositions() const
{
	return initialPositions_;
}

QDataStream & Board::toDataStream(QDataStream &out) const
{
	return out << size_ << fields_ << rulers_ << initialPositions_ << terrains_ << terrainSerial_;
}

bool Board::setSize(const QSize &newSize)
{
	if (newSize.width() < 1 || newSize.height() < 1)
		return false;

	while (size_.width() > newSize.width())
		removeColumn();
	while (size_.width() < newSize.width())
		addColumn();

	while (size_.height() > newSize.height())
		removeRow();
	while (size_.height() < newSize.height())
		addRow();

	return true;
}

void Board::addColumn()
{
	int column = columnCount();
	for (int row = 0; row < rowCount(); ++row)
		insertNullField(Coordinates(row, column));

	size_ += QSize(1, 0);
}

void Board::addRow()
{
	int row = rowCount();
	for (int column = 0; column < columnCount(); ++column)
		insertNullField(Coordinates(row, column));

	size_ += QSize(0, 1);
}

bool Board::removeColumn()
{
	if (columnCount() == 1)
		return false;

	int column = columnCount() - 1;
	for (int row = 0; row < rowCount(); ++row)
		removeField(Coordinates(row, column));

	size_ -= QSize(1, 0);
	return true;
}

bool Board::removeRow()
{
	if (rowCount() == 1)
		return false;

	int row = rowCount() - 1;
	for (int column = 0; column < columnCount(); ++column)
		removeField(Coordinates(row, column));

	size_ -= QSize(0, 1);
	return true;
}

void Board::setInitialPosition(Race race, Coordinates coords)
{
	initialPositions_[race] = coords;
}

void Board::setInitialPositions(const QHash<Race, Coordinates> &initialPositions)
{
	initialPositions_ = initialPositions;
}

UID Board::addTerrain(Terrain &terrain)
{
	UID uid = terrainSerial_.next();
	terrain.setUid(uid);
	terrains_.insert(uid, terrain);

	return uid;
}

QDataStream & Board::fromDataStream(QDataStream &in)
{
	return in >> size_ >> fields_ >> rulers_ >> initialPositions_ >> terrains_ >> terrainSerial_;
}

const UID Board::NullTerrainUid = Serial::EmptyUid;

void Board::insertNullField(const Coordinates& coords)
{
	fields_.insert(coords, NullTerrainUid);
	rulers_.insert(coords, Kingdom::Neutral);
}

void Board::removeField(const Coordinates& coords)
{
	fields_.remove(coords);
	rulers_.remove(coords);

	for (auto &race : initialPositions_.keys())
		if (initialPositions_[race] == coords)
			initialPositions_[race] = Coordinates(0, 0);
}


QDataStream & operator<<(QDataStream &out, const Board &board)
{
	return board.toDataStream(out);
}

QDataStream & operator>>(QDataStream &in, Board &board)
{
	return board.fromDataStream(in);
}
