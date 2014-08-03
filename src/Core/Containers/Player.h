/*
Copyright (C) 2013 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
Copyright (C) 2013 Łukasz Piesiewicz <wookesh [at] gmail [dot] com>
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

#include "Core/Containers/Equipment.h"
#include "Core/Containers/Field.h"
#include "Core/Containers/Quest.h"
#include "Core/Containers/FightParticipant.h"
#include "Core/Game.h"
#include "Core/Util/BiHash.hpp"
#include "Core/Strings.h"

static const quint8 PlayerRaceCount = 4;
static const quint8 PlayerClassCount = 4;

EnumClass(Race, quint8, Human, Dwarf, Elf, Halfling);
const static BiHash <Race, QString> raceLabels {
	{Race::Human, Names::Human},
	{Race::Dwarf, Names::Dwarf},
	{Race::Elf, Names::Elf},
	{Race::Halfling, Names::Halfling}
};

EnumClass(Class, quint8, Fighter, Ranger, Mage, Druid);
const static BiHash <Class, QString> classLabels {
	{Class::Fighter, Names::Fighter},
	{Class::Ranger, Names::Ranger},
	{Class::Mage, Names::Mage},
	{Class::Druid, Names::Druid},
};

//TODO CFiend te rozne rodzaje ataku to moze tez powinien byc enum?
//TODO CFiend i atrybuty tak samo


class Player : public FightParticipant {

public:
	struct CharacterStats {
		BattleStats battleStats_;
		qint8 regeneration_;
		qint8 movePoints_;
	};
	
	Player(QString name, Race playerRace, Class playerClass, QColor color, bool isAI);
	virtual ~Player();

	QString name() const;
	Race playerRace() const;
	Class playerClass() const;
	QColor color() const;
	bool isAI() const;
	FieldId position() const;
	void setPosition(FieldId id);
	Equipment * equipment() const;
	QList <Quest *> * quests();
	Quest * quest(int index) const;
	void removeQuest(int questId);
	quint8 level() const;
	void setLevel(quint8 level);
	int * reputation(); //TODO CFiend moze lepiej, zeby to bylo cos mocniejszego niz int *
	void setReputation(int value, int index);
	int healthMax() const;
	void setHealthMax(int value);
	int healthCurrent() const;
	void setHealthCurrent(int value);
	int regeneration() const;
	void setRegeneration(int value);
	int attackMelee() const;
	void setAttackMelee(int value);
	int attackRanged() const;
	void setAttackRanged(int value);
	int attackMagical() const;
	void setAttackMagical(int value);
	int defence() const;
	void setDefence(int value);
	int perception() const;
	void setPerception(int value);
	quint8 movePoints() const;
	void setMovePoints(quint8 value);
	quint16 gold() const;
	void setGold(quint16 value);
	quint16 experience() const;
	void setExperience(quint16 value);
	bool hasFoughtRecently() const;
	void setHasFoughtRecently(bool value);
	bool isActive() const;
	void setIsActive(bool value);

	static const quint8 StartingExperience = 0;
	static const quint8 StartingGold = 3;
	static const quint8 StartingLevel = 1;
	static const quint8 StartingMovePoints = 8;
	static const quint8 StartingReputation = 0;

	static const quint8 MaxLevel = 5;

	// NOTE should it be here? Maybe GameInitSettings later on?
	static const QHash <QPair <Class, Race>, CharacterStats> & baseClassStats();

	//NOTE Wookesh Changed old array into QMap with new enum
	//TODO CFiend KILL IT WITH FIRE
	// should be solved by decent content editor or by reading with board setup
	static const QHash <Race, FieldId> & raceStartingPosition();

private:

	Race playerRace_;
	Class playerClass_;
	QColor color_;
	bool isAI_;
	CharacterStats baseStats_;
	FieldId position_;
	Equipment *equipment_; //TODO CFiend sprawdzic czy nie lepiej dac twardy obiekt
	QList <Quest *> quests_;
	QList <FieldId> importantFields_;
	quint8 level_;
	int reputation_[KingdomCount];
	quint16 gold_;
	quint16 experience_;
	bool hasFoughtRecently_;
	bool isActive_;
};
