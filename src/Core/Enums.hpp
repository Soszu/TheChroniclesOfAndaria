/*
Copyright (C) 2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
+Copyright (C) 2015 by Marcin Parafiniuk <jessie [dot] inferno [at] gmail [dot] com>
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

#include "Core/Utils/BiHash.hpp"

// ========== KINGDOM ==========
enum class Kingdom : quint8 {
	Neutral,
	Humans,
	Dwarfs,
	Elves,
	Halflings,
};
Q_DECLARE_METATYPE(Kingdom)
uint qHash(Kingdom val);
const QVector<Kingdom> KingdomsForReputation {
	Kingdom::Humans,
	Kingdom::Dwarfs,
	Kingdom::Elves,
	Kingdom::Halflings,
};
QDataStream & operator<<(QDataStream & out, const Kingdom & val);
QDataStream & operator>>(QDataStream & in, Kingdom & val);
const BiHash <Kingdom, QString> KingdomLabels {
	{Kingdom::Neutral,   QObject::tr("Neutral")},
	{Kingdom::Humans,    QObject::tr("Humans")},
	{Kingdom::Dwarfs,    QObject::tr("Dwarfs")},
	{Kingdom::Elves,     QObject::tr("Elves")},
	{Kingdom::Halflings, QObject::tr("Halflings")}
};

// ========== RACE ==========
enum class Race : quint8 {
	Human,
	Dwarf,
	Elf,
	Halfling,
};
Q_DECLARE_METATYPE(Race)
uint qHash(Race playerRace);
QDataStream & operator<<(QDataStream & out, const Race & playerRace);
QDataStream & operator>>(QDataStream & in, Race & playerRace);
const BiHash <Race, QString> RaceLabels {
	{Race::Human,    QObject::tr("Human")},
	{Race::Dwarf,    QObject::tr("Dwarf")},
	{Race::Elf,      QObject::tr("Elf")},
	{Race::Halfling, QObject::tr("Halfling")}
};

// ========== CLASS ==========
enum class Class : quint8 {
	Fighter,
	Hunter,
	Mage,
	Druid,
};
Q_DECLARE_METATYPE(Class)
uint qHash(Class val);
QDataStream & operator<<(QDataStream & out, const Class & val);
QDataStream & operator>>(QDataStream & in, Class & val);
const BiHash <Class, QString> ClassLabels {
	{Class::Fighter, QObject::tr("Fighter")},
	{Class::Hunter,  QObject::tr("Hunter")},
	{Class::Mage,    QObject::tr("Mage")},
	{Class::Druid,   QObject::tr("Druid")}
};

// ========== ATTACK ==========
enum class Attack : quint8 {
	Melee,
	Ranged,
	Magical,
};
Q_DECLARE_METATYPE(Attack)
uint qHash(Attack val);
QDataStream & operator<<(QDataStream & out, const Attack & val);
QDataStream & operator>>(QDataStream & in, Attack & val);
const BiHash <Attack, QString> AttackLabels {
	{Attack::Melee,   QObject::tr("Melee")},
	{Attack::Ranged,  QObject::tr("Ranged")},
	{Attack::Magical, QObject::tr("Magical")},
};

// ========== ACTION ==========
enum class Action : quint8 {
	GoToHealer,
	GoToMarket,
	GoToTavern,
	FightWithMonster,
	EndTurn,
};
Q_DECLARE_METATYPE(Action)
uint qHash(Action val);
QDataStream & operator<<(QDataStream & out, const Action & val);
QDataStream & operator>>(QDataStream & in, Action & val);
const BiHash <Action, QString> ActionLabels {
	{Action::GoToMarket,       QObject::tr("Go to market")},
	{Action::GoToTavern,       QObject::tr("Go to tavern")},
	{Action::GoToHealer,       QObject::tr("Go to healer")},
	{Action::FightWithMonster, QObject::tr("Fight with monster")},
	{Action::EndTurn,          QObject::tr("End turn")},
};

// ========== DIFFICULTY ==========
enum class Difficulty : quint8 {
	Easy,
	Medium,
	Hard,
};
Q_DECLARE_METATYPE(Difficulty)
uint qHash(Difficulty val);
QDataStream & operator<<(QDataStream & out, const Difficulty & val);
QDataStream & operator>>(QDataStream & in, Difficulty & val);
const BiHash <Difficulty, QString> DifficultyLabels {
	{Difficulty::Easy,       QObject::tr("Easy")},
	{Difficulty::Medium,     QObject::tr("Medium")},
	{Difficulty::Hard,       QObject::tr("Hard")},
};
