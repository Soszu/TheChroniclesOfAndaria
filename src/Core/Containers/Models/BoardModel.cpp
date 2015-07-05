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
#include "Core/Containers/Models/BoardModel.hpp"
#include "Core/Utils/Debug.hpp"

#include "Core/Enums.hpp"

BoardModel::BoardModel()
{
	reset();
}

BoardModel::~BoardModel()
{
	qDeleteAll(terrains_);
}

const QSize & BoardModel::size() const
{
	return size_;
}

int BoardModel::columnCount() const
{
	return size_.width();
}

int BoardModel::rowCount() const
{
	return size_.height();
}

const Terrain * BoardModel::terrain(const Coordinates & coords) const
{
	if (fields_[coords] == NullTerrainUid)
		return nullptr;

	return terrains_[fields_[coords]];
}

const Terrain * BoardModel::terrain(UID terrainUid) const
{
	if (terrainUid == NullTerrainUid)
		return nullptr;

	return terrains_[terrainUid];
}

QList<UID> BoardModel::terrainUids() const
{
	return terrains_.keys();
}

Kingdom BoardModel::ruler(const Coordinates & coords) const
{
	return rulers_[coords];
}

Coordinates BoardModel::initialPosition(Race race) const
{
	return initialPositions_[race];
}

const QHash<Race, Coordinates> & BoardModel::initialPositions() const
{
	return initialPositions_;
}

QDataStream & BoardModel::toDataStream(QDataStream & out) const
{
	datalog("BoardModel::toDataStream: saving data...");
	out << size_ << fields_ << rulers_ << initialPositions_;

	out << terrainSerial_ << static_cast<UID>(terrains_.count());
	for (const Terrain * terrain : terrains_)
		out << terrain->uid() << *terrain;

	datalog("BoardModel::toDataStream: done");
	return out;
}

bool BoardModel::setSize(const QSize & newSize)
{
	if (newSize == size_)
		return false;

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

	emit modelChanged();

	return true;
}

void BoardModel::addColumn()
{
	int column = columnCount();
	for (int row = 0; row < rowCount(); ++row)
		insertNullField(Coordinates(row, column));

	size_ += QSize(1, 0);
	emit modelChanged();
}

void BoardModel::addRow()
{
	int row = rowCount();
	for (int column = 0; column < columnCount(); ++column)
		insertNullField(Coordinates(row, column));

	size_ += QSize(0, 1);
	emit modelChanged();
}

bool BoardModel::removeColumn()
{
	if (columnCount() == 1)
		return false;

	int column = columnCount() - 1;
	for (int row = 0; row < rowCount(); ++row)
		removeField(Coordinates(row, column));

	size_ -= QSize(1, 0);
	emit modelChanged();
	return true;
}

bool BoardModel::removeRow()
{
	if (rowCount() == 1)
		return false;

	int row = rowCount() - 1;
	for (int column = 0; column < columnCount(); ++column)
		removeField(Coordinates(row, column));

	size_ -= QSize(0, 1);
	emit modelChanged();
	return true;
}

void BoardModel::reset()
{
	qDeleteAll(terrains_);

	Coordinates coords(0, 0);

	size_ = QSize(1, 1);
	fields_.insert(coords, NullTerrainUid);
	rulers_.insert(coords, Kingdom::Neutral);

	for (Race &race : RaceLabels.leftKeys())
		initialPositions_[race] = coords;
	emit modelChanged();
}

void BoardModel::setTerrain(const Coordinates & coords, UID terrainUid)
{
	fields_[coords] = terrainUid;
	//WARNING Temporary commented out due to loading from txt
// 	emit modelChanged();
}

void BoardModel::setRuler(const Coordinates & coords, Kingdom ruler)
{
	rulers_[coords] = ruler;
	emit modelChanged();
}

void BoardModel::setInitialPosition(Race race, Coordinates coords)
{
	initialPositions_[race] = coords;
	emit modelChanged();
}

void BoardModel::setInitialPositions(const QHash<Race, Coordinates> & initialPositions)
{
	initialPositions_ = initialPositions;
	emit modelChanged();
}

UID BoardModel::addTerrain(Terrain * terrain)
{
	UID uid = terrainSerial_.next();
	terrain->setUid(uid);
	terrains_.insert(uid, terrain);

	//WARNING Temporary commented out due to loading from txt
// 	emit modelChanged();
	return uid;
}

void BoardModel::setModified()
{
	emit modelChanged();
}

QDataStream & BoardModel::fromDataStream(QDataStream & in)
{
	datalog("BoardModel::fromDataStream: loading data...");

	in >> size_ >> fields_ >> rulers_ >> initialPositions_;


	ldatalog("width = " + QString::number(size_.width()) + ", height = " + QString::number(size_.height()));
	QString strFields;
	for (const Coordinates &c : fields_.keys()) {
		if (!strFields.isEmpty())
			strFields += ", ";
		strFields += c.toString();
	}
	ldatalog("fields = " + strFields);

	QString strRulers;
	for (const Coordinates &c : rulers_.keys()) {
		if (!strRulers.isEmpty())
			strRulers += ", ";
		strRulers += c.toString();
	}
	ldatalog("rulers = " + strRulers);

	QString strInitialPositions;
	for (const Coordinates &c : initialPositions_) {
		if (!strInitialPositions.isEmpty())
			strInitialPositions += ", ";
		strInitialPositions += c.toString();
	}
	ldatalog("initialPositions = " + strInitialPositions);


	UID count;
	in >> terrainSerial_ >> count;
	for (UID i = 0; i < count; ++i) {
		Terrain * terrain = new Terrain;
		UID uid;
		in >> uid >> *terrain;
		terrains_[uid] = terrain;
	}
	datalog("BoardModel::fromDataStream: emit modelChanged signal");
	emit modelChanged();

	datalog("BoardModel::fromDataStream: done");
	return in;
}

const UID BoardModel::NullTerrainUid = Serial::EmptyUid;

void BoardModel::insertNullField(const Coordinates & coords)
{
	fields_.insert(coords, NullTerrainUid);
	rulers_.insert(coords, Kingdom::Neutral);
}

void BoardModel::removeField(const Coordinates & coords)
{
	fields_.remove(coords);
	rulers_.remove(coords);

	for (auto & race : initialPositions_.keys())
		if (initialPositions_[race] == coords)
			initialPositions_[race] = Coordinates(0, 0);
}


QDataStream & operator<<(QDataStream & out, const BoardModel & board)
{
	return board.toDataStream(out);
}

QDataStream & operator>>(QDataStream & in, BoardModel & board)
{
	return board.fromDataStream(in);
}
