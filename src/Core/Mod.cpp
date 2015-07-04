/*
Copyright (C) 2013-2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
+Copyright (C) 2015 by Piotr Majcherczyk <fynxor [at] gmail [dot] com>
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
#include "Core/Mod.hpp"

#include "Core/Enums.hpp"
#include "Core/Parsers/BoardParser.hpp"
#include "Core/Parsers/ItemParser.hpp"
#include "Core/Parsers/PrizeParser.hpp"
#include "Core/Parsers/EnemyParser.hpp"
#include "Core/Parsers/QuestParser.hpp"
#include "Core/Containers/Bases/ItemBase.hpp"
#include "Core/Utils/Debug.hpp"

Mod::Mod()
{}

Mod::~Mod()
{
	qDeleteAll(prizes_);
}

bool Mod::hasUnsavedChanges() const
{
	bool changed = (itemModel_.isChanged() || enemyModel_.isChanged());
	if (changed)
		log("Mod::hasUnsavedChanges yes");
	else
		log("Mod::hasUnsavedChanges no");
	return changed;
}

void Mod::loadFromTxt()
{
	info("Loading text data");
	// TODO Parsers should be replaced with models

	ItemParser itemParser(this);
		qDebug() << itemParser.trescBledu << "items" << items_.size();

	PrizeParser prizeParser(this);
		qDebug() << prizeParser.trescBledu << "prizes" << prizes_.size();

	EnemyParser enemyParser(this);
		qDebug() << enemyParser.trescBledu << "enemies: " << enemies_.size();

	QuestParser questParser(this);
		qDebug() << questParser.trescBledu << "quests: " << quests_.size();
	for (auto &quest : quests_)
		qDebug() << quest->objectives()[0].testData.data();

	for (auto & item : items_)
		itemModel_.addItemBase(item);

	for (auto & enemy : enemies_)
		enemyModel_.addEnemyBase(enemy);

	for (auto & quest : quests_)
		questModel_.addQuestBase(quest);

	//it fills boardModel_ in constructor
	BoardParser boardParser(this);

	qDebug() << boardParser.trescBledu << boardModel_.size() << boardModel_.terrainUids().size();
}


//TODO something entirely wrong FIX FIX FIX this feature
bool Mod::load(const QString & path)
{
	info("Loading from ", Logging::NoEndline);
	info(path, Logging::NoEndline | Logging::NoColour);
	info(" (binary data)");

	if (path.isEmpty()) {
		info("Mod::load: unable to load, empty path.");
		return false;
	}

	QFile file(path);
	if (!file.open(QIODevice::ReadOnly)) {
		info("Mod::load: unable to load, cannot open file.");
		return false;
	}

	log("Mod::load: reading file");
	QDataStream in(&file);
	log("Mod::load: done");

	log("Mod::load: loading models");
	datalog("Mod::load: loading boardModel");
	in >> boardModel_;
	datalog("Mod::load: loading itemModel");
	in >> itemModel_;
	datalog("Mod::load: loading enemyModel");
	in >> enemyModel_;
	datalog("Mod::load: loading questModel");
	in >> questModel_;
	log("Mod::load: done");

	file.close();

	return true;
}

bool Mod::save(const QString & path)
{
	info("Saving...");

	if (path.isEmpty()) {
		info("Unable to save, path is empty.");
		return false;
	}

	QFile file(path);
	if (!file.open(QIODevice::WriteOnly)) {
		info("Unable to open file.");
		return false;
	}

	QDataStream out(&file);

	log("Mod::save: saving models");
	out << boardModel_ << itemModel_ << enemyModel_ << questModel_;

	itemModel_.setChanged(false);
	enemyModel_.setChanged(false);

	log("Mod::save: done");

	file.close();
	info("Done!");
	return true;
}

void Mod::reset()
{
	log("Mod::reset");

	itemModel_.reset();
	enemyModel_.reset();
	boardModel_.reset();
}

BoardModel * Mod::boardModel()
{
	return &boardModel_;
}

ItemModel * Mod::itemModel()
{
	return &itemModel_;
}

EnemyModel * Mod::enemyModel()
{
	return &enemyModel_;
}

QuestModel * Mod::questModel()
{
	return &questModel_;
}

const BoardModel & Mod::boardModel() const
{
	return boardModel_;
}

const ItemModel & Mod::itemModel() const
{
	return itemModel_;
}

const EnemyModel & Mod::enemyModel() const
{
	return enemyModel_;
}

const QuestModel & Mod::questModel() const
{
	return questModel_;
}
