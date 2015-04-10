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
#pragma once

#include "Core/Containers/Terrain.hpp"
#include "Core/Enums.hpp"
#include "Core/Containers/Coordinates.hpp"

#include "Core/Utils/Serial.hpp"

//NOTE Keep size of board at least 1x1, so there can be always some initial positions set.
class BoardModel : public QObject
{
	Q_OBJECT
public:
	BoardModel();
	~BoardModel();

	const QSize & size() const;
	int columnCount() const;
	int rowCount() const;
	//FIXME by value due to QHash [] operator
	const Terrain * terrain(const Coordinates & coords) const;
	const Terrain * terrain(UID terrainUid) const;
	QList<UID> terrainUids() const;
	Kingdom ruler(const Coordinates & coords) const;
	Coordinates initialPosition(Race race) const;
	const QHash<Race, Coordinates> & initialPositions() const;
	QDataStream & toDataStream(QDataStream & out) const;

	bool setSize(const QSize & newSize);
	void addColumn();
	void addRow();
	bool removeColumn();
	bool removeRow();
	void reset();
	void setTerrain(const Coordinates & coords, UID terrainUid);
	void setRuler(const Coordinates & coords, Kingdom ruler);
	void setInitialPosition(Race race, Coordinates coords);
	void setInitialPositions(const QHash<Race, Coordinates> & initialPositions);
	QDataStream & fromDataStream(QDataStream & in);

	//TMP
	UID addTerrain(Terrain * terrain);
	void setModified();

private:
	static const UID NullTerrainUid;

	void insertNullField(const Coordinates & coords);
	void removeField(const Coordinates & coords);

	QSize size_;
	QHash<Coordinates, UID> fields_;
	QHash<Coordinates, Kingdom> rulers_;
	QHash<Race, Coordinates> initialPositions_;
	QHash<UID, Terrain *> terrains_;

	Serial terrainSerial_;
signals:
	void modelChanged();
};
QDataStream & operator<<(QDataStream & out, const BoardModel & board);
QDataStream & operator>>(QDataStream & in, BoardModel & board);
