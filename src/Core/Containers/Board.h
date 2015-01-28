#pragma once

#include "Core/Containers/Terrain.h"
#include "Core/Enums.hpp"
#include "Core/Containers/Coordinates.hpp"

#include "Core/Utils/Serial.hpp"

//NOTE Keep size of board at least 1x1, so there can be always some initial positions set.
class Board {

public:
	static const Terrain NullTerrain;

	Board();

	const QSize & size() const;
	int columnCount() const;
	int rowCount() const;
	//FIXME by value due to QHash [] operator
	Terrain terrain(const Coordinates coords) const;
	Kingdom ruler(const Coordinates coords) const;
	Coordinates initialPosition(Race race) const;
	const QHash<Race, Coordinates> & initialPositions() const;
	QDataStream & toDataStream(QDataStream &out) const;

	bool setSize(const QSize & newSize);
	void addColumn();
	void addRow();
	bool removeColumn();
	bool removeRow();
	void setInitialPosition(Race race, Coordinates coords);
	void setInitialPositions(const QHash<Race, Coordinates> &initialPositions);
	QDataStream & fromDataStream(QDataStream &in);

	//TMP
	UID addTerrain(Terrain &terrain);

private:
	static const UID NullTerrainUid;

	void insertNullField(const Coordinates &coords);
	void removeField(const Coordinates &coords);

	QSize size_;
	QHash<Coordinates, UID> fields_;
	QHash<Coordinates, Kingdom> rulers_;
	QHash<Race, Coordinates> initialPositions_;
	QHash<UID, Terrain> terrains_;

	Serial terrainSerial_;
};
QDataStream & operator<<(QDataStream &out, const Board &board);
QDataStream & operator>>(QDataStream &in, Board &board);
