/*
 * Copyright (C) 2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
 * This file is part of The Chronicles Of Andaria Project.
 *
 *	The Chronicles of Andaria Project is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	The Chronicles of Andaria Project is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with The Chronicles Of Andaria.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "Core/Utils/BiHash.hpp"
#include "Core/Strings.h"

enum class Kingdom : quint8 {
	Neutral,
	Humans,
	Dwarfs,
	Elves,
	Halflings
};
Q_DECLARE_METATYPE(Kingdom)
uint qHash(Kingdom kingdom);
QDataStream & operator<<(QDataStream &out, Kingdom kingdom);
QDataStream & operator>>(QDataStream &in, Kingdom kingdom);
const BiHash <Kingdom, QString> KingdomLabels {
	{Kingdom::Neutral,   Labels::Kingdoms::Neutral},
	{Kingdom::Humans,    Labels::Kingdoms::Humans},
	{Kingdom::Dwarfs,    Labels::Kingdoms::Dwarfs},
	{Kingdom::Elves,     Labels::Kingdoms::Elves},
	{Kingdom::Halflings, Labels::Kingdoms::Halflings}
};

enum class Race : quint8 {
	Human,
	Dwarf,
	Elf,
	Halfling
};
Q_DECLARE_METATYPE(Race)
uint qHash(Race playerRace);
QDataStream & operator<<(QDataStream &out, const Race &playerRace);
QDataStream & operator>>(QDataStream &in, Race &playerRace);
const BiHash <Race, QString> RaceLabels {
	{Race::Human,    Labels::Races::Human},
	{Race::Dwarf,    Labels::Races::Dwarf},
	{Race::Elf,      Labels::Races::Elf},
	{Race::Halfling, Labels::Races::Halfling}
};

enum class Class : quint8 {
	Fighter,
	Hunter,
	Mage,
	Druid
};
Q_DECLARE_METATYPE(Class)
uint qHash(Class playerClass);
QDataStream & operator<<(QDataStream &out, const Class &playerClass);
QDataStream & operator>>(QDataStream &in, Class &playerClass);
const BiHash <Class, QString> ClassLabels {
	{Class::Fighter, Labels::Classes::Fighter},
	{Class::Hunter,  Labels::Classes::Hunter},
	{Class::Mage,    Labels::Classes::Mage},
	{Class::Druid,   Labels::Classes::Druid}
};

enum class Attack : quint8 {
	Melee,
	Ranged,
	Magical
};
Q_DECLARE_METATYPE(Attack)
uint qHash(Attack attack);
QDataStream & operator<<(QDataStream &out, const Attack &attack);
QDataStream & operator>>(QDataStream &in, Attack &attack);
const BiHash <Attack, QString> AttackLabels {
	{Attack::Melee,   Labels::Attacks::Melee},
	{Attack::Ranged,  Labels::Attacks::Ranged},
	{Attack::Magical, Labels::Attacks::Magical},
};

enum class Action : quint8 {
	GoToMarket,
	GoToTavern,
	FightWithMonster,
	EndTurn
};
Q_DECLARE_METATYPE(Action)
uint qHash(Action action);
QDataStream & operator<<(QDataStream &out, const Action &action);
QDataStream & operator>>(QDataStream &in, Action &action);
const BiHash <Action, QString> ActionLabels {
	{Action::GoToMarket,       Labels::Actions::GoToMarket},
	{Action::GoToTavern,       Labels::Actions::GoToTavern},
	{Action::FightWithMonster, Labels::Actions::FightWithMonster},
	{Action::EndTurn,          Labels::Actions::EndTurn},
};