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

#include "Core/Containers/Field.h"
#include "Core/Enums.hpp"

#include "Core/Containers/Models/EnemyModel.h"
#include "Core/Containers/Models/ItemModel.h"

#include "Core/Containers/Prize.h"
#include "Core/Containers/Bases/EnemyBase.h"
#include "Core/Containers/Bases/ItemBase.h"

const bool LoadFromTxt = true;

//Mod, Variant, Rule(s), Option, Extension, Version, Chronicle, Guide, Set, Model, Story, Content
//Tale, Form, Adaptation,
class Mod
{
	friend class EnemyParser;
	friend class ItemParser;
	friend class PrizeParser;
	friend class QuestParser;
	friend class BoardParser;

public:
	Mod();
	~Mod();

	bool load(const QString &path);
	bool save(const QString &path);
	bool unsavedChanges() const;
	void reset();

	ItemModel * itemModel();
	EnemyModel * enemyModel();

	Coordinates initialPosition(Race playerRace) const;
	const QList<Field> & fields() const;
	quint8 boardHeight() const;
	quint8 boardWidth() const;

private:

	ItemModel itemModel_;
	EnemyModel enemyModel_;

	//TMP
	QMap<int, ItemBase*> items_;
	QMap<int, Prize*> prizes_;
	QMap<int, EnemyBase*> enemies_;

	QList <Field> fields_;
	QHash <Race, Coordinates> initialPositions_;
	quint8 boardHeight_;
	quint8 boardWidth_;
};
