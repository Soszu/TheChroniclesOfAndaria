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

#include "Core/Containers/Player.h"

Player::Player(QString name, Race playerRace,Class playerClass, QColor color, bool isAI)
	: FightParticipant(name),
	  playerRace_(playerRace),
	  playerClass_(playerClass),
	  color_(color),
	  isAI_(isAI),
	  baseStats_(Player::baseClassStats()[qMakePair(playerClass, playerRace)]),
	  position_(Player::raceStartingPosition()[this->playerRace_]),
	  equipment_(new Equipment),
	  level_(StartingLevel),
	  gold_(StartingGold),
	  experience_(StartingExperience),
	  hasFoughtRecently_(false),
	  isActive_(true)
{
	for(int i = 0; i < KingdomCount; ++i)
		this->reputation_[i] = StartingReputation;
	healthCurrent_ = baseStats_.battleStats_.healthMax_;
}

Player::~Player()
{
	delete equipment_;
}

const QHash <QPair <Class, Race>, Player::CharacterStats> & Player::baseClassStats()
{
	//NOTE rebalance basic damage stats due to new mechanics
	static const QHash <QPair <Class, Race>, Player::CharacterStats> baseClassStats_{
		//{Class, Race}, {{healthMax, defence, perception, {{meleDmgMin, meleDmgRange}, {rangeDmgMin, rangeDmgRange}, {magicalDmgMin, magicalDmgRAnge}}}, regeneration, movePoints }
		{{Class::Fighter, Race::Human}, {{15, 10, 1, {{AttackType::Melee, {10, 0}}, {AttackType::Ranged, {3, 0}}, {AttackType::Magical, { 1, 0}}}}, 2, StartingMovePoints}},
		{{Class::Ranger,  Race::Human}, {{13,  8, 7, {{AttackType::Melee, { 5, 0}}, {AttackType::Ranged, {9, 0}}, {AttackType::Magical, { 1, 0}}}}, 3, StartingMovePoints}},
		{{Class::Mage,    Race::Human}, {{11,  7, 5, {{AttackType::Melee, { 2, 0}}, {AttackType::Ranged, {1, 0}}, {AttackType::Magical, {11, 0}}}}, 3, StartingMovePoints}},
		{{Class::Druid,   Race::Human}, {{13, 10, 3, {{AttackType::Melee, { 2, 0}}, {AttackType::Ranged, {2, 0}}, {AttackType::Magical, { 8, 0}}}}, 5, StartingMovePoints}},
		
		{{Class::Fighter, Race::Dwarf}, {{15, 10, 1, {{AttackType::Melee, {10, 0}}, {AttackType::Ranged, {5, 0}}, {AttackType::Magical, { 1, 0}}}}, 2, StartingMovePoints}},
		{{Class::Ranger,  Race::Dwarf}, {{13,  8, 7, {{AttackType::Melee, { 5, 0}}, {AttackType::Ranged, {9, 0}}, {AttackType::Magical, { 1, 0}}}}, 3, StartingMovePoints}},
		{{Class::Mage,    Race::Dwarf}, {{11,  7, 5, {{AttackType::Melee, { 2, 0}}, {AttackType::Ranged, {1, 0}}, {AttackType::Magical, {11, 0}}}}, 3, StartingMovePoints}},
		{{Class::Druid,   Race::Dwarf}, {{13,  9, 3, {{AttackType::Melee, { 2, 0}}, {AttackType::Ranged, {2, 0}}, {AttackType::Magical, { 8, 0}}}}, 5, StartingMovePoints}},
		
		{{Class::Fighter, Race::Elf}, {{15, 10, 1, {{AttackType::Melee, {10, 0}}, {AttackType::Ranged, {5, 0}}, {AttackType::Magical, { 1, 0}}}}, 2, StartingMovePoints}},
		{{Class::Ranger,  Race::Elf}, {{13,  8, 7, {{AttackType::Melee, { 5, 0}}, {AttackType::Ranged, {9, 0}}, {AttackType::Magical, { 1, 0}}}}, 3, StartingMovePoints}},
		{{Class::Mage,    Race::Elf}, {{11,  7, 5, {{AttackType::Melee, { 2, 0}}, {AttackType::Ranged, {1, 0}}, {AttackType::Magical, {11, 0}}}}, 3, StartingMovePoints}},
		{{Class::Druid,   Race::Elf}, {{13,  9, 3, {{AttackType::Melee, { 2, 0}}, {AttackType::Ranged, {2, 0}}, {AttackType::Magical, { 8, 0}}}}, 5, StartingMovePoints}},
		
		{{Class::Fighter, Race::Halfling}, {{15, 10, 1, {{AttackType::Melee, {10, 0}}, {AttackType::Ranged, {5, 0}}, {AttackType::Magical, { 1, 0}}}}, 2, StartingMovePoints}},
		{{Class::Ranger,  Race::Halfling}, {{13,  8, 7, {{AttackType::Melee, { 5, 0}}, {AttackType::Ranged, {9, 0}}, {AttackType::Magical, { 1, 0}}}}, 3, StartingMovePoints}},
		{{Class::Mage,    Race::Halfling}, {{11,  7, 5, {{AttackType::Melee, { 2, 0}}, {AttackType::Ranged, {1, 0}}, {AttackType::Magical, {11, 0}}}}, 3, StartingMovePoints}},
		{{Class::Druid,   Race::Halfling}, {{13,  9, 3, {{AttackType::Melee, { 2, 0}}, {AttackType::Ranged, {2, 0}}, {AttackType::Magical, { 8, 0}}}}, 5, StartingMovePoints}},
	};
	return baseClassStats_;
}

const QHash <Race, FieldId> & Player::raceStartingPosition()
{
	static QHash <Race, FieldId> raceStartingPosition_{
		{Race::Human, {18,3}},
		{Race::Dwarf, {14,18}},
		{Race::Elf, {28,8}},
		{Race::Halfling, {2,8}}
	};
	return raceStartingPosition_;
}


QString Player::name() const
{
	return name_;
}

Race Player::playerRace() const
{
	return playerRace_;
}

Class Player::playerClass() const
{
	return playerClass_;
}

QColor Player::color() const
{
	return color_;
}

bool Player::isAI() const
{
	return isAI_;
}

FieldId Player::position() const
{
	return position_;
}

void Player::setPosition(FieldId id)
{
	this->position_ = id;
}

Equipment * Player::equipment() const
{
	return equipment_;
}

QList <Quest *> * Player::quests()
{
	return &quests_; //TODO CFiend taka implementacja uniemozliwia uczynienie tej metody const
}

Quest * Player::quest(int index) const
{
	return quests_[index];
}

void Player::removeQuest(int questId)
{
	int i = 0;
	while (i < quests_.size() && quests_[i]->id() != questId)
		++i;
	if (i != quests_.size())
		delete quests_.takeAt(i);
}

quint8 Player::level() const
{
	return level_;
}

void Player::setLevel(quint8 level)
{
	this->level_ = level;
}

int * Player::reputation()
{
	return reputation_; //TODO CFiend taka implementacja uniemozliwia uczynienie tej metody const
}

void Player::setReputation(int value, int index)
{
	reputation_[index] = value;
}

int Player::healthMax() const
{
	return baseStats_.battleStats_.healthMax_;
}

void Player::setHealthMax(int value)
{
	baseStats_.battleStats_.healthMax_ = value;
}

int Player::healthCurrent() const
{
	return healthCurrent_;
}

void Player::setHealthCurrent(int value)
{
	healthCurrent_ = value;
}

int Player::regeneration() const
{
	return baseStats_.regeneration_;
}

void Player::setRegeneration(int value)
{
	baseStats_.regeneration_ = value;
}

int Player::attackMelee() const
{
	return baseStats_.battleStats_.attacks_[AttackType::Melee].first;
}

void Player::setAttackMelee(int value)
{
	baseStats_.battleStats_.attacks_[AttackType::Melee].first = value;
}

int Player::attackRanged() const
{
	return baseStats_.battleStats_.attacks_[AttackType::Ranged].first;
}

void Player::setAttackRanged(int value)
{
	baseStats_.battleStats_.attacks_[AttackType::Ranged].first = value;
}

int Player::attackMagical() const
{
	return baseStats_.battleStats_.attacks_[AttackType::Magical].first;
}

void Player::setAttackMagical(int value)
{
	baseStats_.battleStats_.attacks_[AttackType::Magical].first = value;
}

int Player::defence() const
{
	return baseStats_.battleStats_.defence_;
}

void Player::setDefence(int value)
{
	baseStats_.battleStats_.defence_ = value;
}

int Player::perception() const
{
	return baseStats_.battleStats_.perception_;
}

void Player::setPerception(int value)
{
	baseStats_.battleStats_.perception_ = value;
}

quint8 Player::movePoints() const
{
	return baseStats_.movePoints_;
}

void Player::setMovePoints(quint8 value)
{
	baseStats_.movePoints_ = value;
}

quint16 Player::gold() const
{
	return gold_;
}

void Player::setGold(quint16 value)
{
	gold_ = value;
}

quint16 Player::experience() const
{
	return experience_;
}

void Player::setExperience(quint16 value)
{
	experience_ = value;
}

bool Player::hasFoughtRecently() const
{
	return hasFoughtRecently_;
}

void Player::setHasFoughtRecently(bool value)
{
	hasFoughtRecently_ = value;
}

void Player::setIsActive(bool value)
{
	isActive_ = value;
}

bool Player::isActive() const
{
	return isActive_;
}
