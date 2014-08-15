/*
Copyright (C) 2013 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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

#include <QtCore>
#include <Core/Containers/Field.h>

enum class Race : quint8;

class DataKeeper
{
	friend class EnemyParser;
	friend class ItemParser;
	friend class PrizeParser;
	friend class QuestParser;
	friend class BoardParser;

public:
	static DataKeeper &instance();
	int initError();

	Coordinates initialPosition(Race playerRace) const;
	const QList<Field> & fields() const;
	quint8 boardHeight() const;
	quint8 boardWidth() const;

private:
	explicit DataKeeper();
	DataKeeper(const DataKeeper &) = delete;
	DataKeeper(DataKeeper &&) = delete;
	void operator=(const DataKeeper &) = delete;
	void operator=(DataKeeper &&) = delete;
	
	int initError_;

	QList <Field> fields_;
	QHash <Race, Coordinates> initialPositions_;
	quint8 boardHeight_;
	quint8 boardWidth_;
};
