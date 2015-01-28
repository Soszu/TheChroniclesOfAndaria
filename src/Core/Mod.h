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

#include "Core/Containers/Coordinates.hpp"
#include "Core/Enums.hpp"

#include "Core/Containers/Models/EnemyModel.h"
#include "Core/Containers/Models/ItemModel.h"
#include "Core/Containers/Board.h"

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

	bool unsavedChanges() const;

	bool load(const QString &path);
	bool save(const QString &path);
	void reset();
	Board * board();
	EnemyModel * enemyModel();
	ItemModel * itemModel();

	const Board & board() const;
	const EnemyModel & enemyModel() const;
	const ItemModel & itemModel() const;
	Coordinates initialPosition(Race race) const;

private:
	EnemyModel enemyModel_;
	ItemModel itemModel_;
	Board board_;

	//TMP
	QMap<int, ItemBase*> items_;
	QMap<int, Prize*> prizes_;
	QMap<int, EnemyBase*> enemies_;
};
