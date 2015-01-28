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

#include "Core/Containers/PlayerDraft.h"
#include "Core/Containers/Player.h"
#include "Core/Mod.h"

const quint16 Player::LevelBorders[MaximumLevel] = {0, 500, 1100, 1800, 2600, 3500, 4500, 5600, 6800, 8100};

const QSet <Effect::Type> Player::extendableAttributes = {
	{Effect::Type::MeleeBase},
	{Effect::Type::RangedBase},
	{Effect::Type::MagicalBase},
	{Effect::Type::Defence},
	{Effect::Type::Perception},
};

Player::Player(const PlayerDraft &draft, const Mod &mod)
      : name_(draft.name()),
        playerRace_(draft.playerRace()),
        playerClass_(draft.playerClass()),
        color_(draft.color()),
        level_(InitialLevel),
        growthPoints_(InitialGrowthPoints),
        baseStats_(InitialEffects(playerClass_, playerRace_)),
        experience_(InitialExperience),
        gold_(InitialGold),
        position_(mod.initialPosition(playerRace_)),
        equipment_(playerClass_),
        journal_(),
        reputations_(InitialReputations)
{
	initHealth();
}

const QPixmap & Player::avatar() const
{
	return avatar_;
}

QColor Player::color() const
{
	return color_;
}

const Equipment & Player::equipment() const
{
	return equipment_;
}

quint16 Player::experience() const
{
	return experience_;
}

const Journal & Player::journal() const
{
	return journal_;
}

quint8 Player::level() const
{
	return level_;
}

quint16 Player::gold() const
{
	return gold_;
}

quint8 Player::growthPoints() const
{
	return growthPoints_;
}

const QList <Effect> Player::individualEffects() const
{
	return baseStats_ + equipment_.activeEffects();
}

const QString &Player::name() const
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

Coordinates Player::position() const
{
	return position_;
}

const qint8 Player::reputation(Kingdom kingdom) const
{
	return reputations_[kingdom];
}

void Player::consumeGrowthPoint(Effect::Type attribute)
{
	if (growthPoints_ == 0 || not extendableAttributes.contains(attribute))
		return;
	baseStats_.append(Effect(attribute, AttributeGrowth));
	--growthPoints_;
}

Equipment & Player::equipment()
{
	return equipment_;
}

Journal & Player::journal()
{
	return journal_;
}

void Player::grantPrize(const Prize &prize)
{
	imposeEffects(prize.effects());
	grantExperience(prize.experience());
	equipment_.addItems(prize.items());
	shiftGold(prize.gold());
	for (auto &kingdom : prize.reputations().keys())
		shiftReputation(kingdom, prize.reputation(kingdom));
}

void Player::move(Coordinates field)
{
	position_ = field;
}

void Player::regenerate()
{
	heal(value(Effect::Type::Regeneration));
}

void Player::shiftGold(qint16 amount)
{
	gold_ = qMax(0, qint32(gold_) + amount);
}

void Player::shiftReputation(Kingdom kingdom, qint8 value)
{
	reputations_[kingdom] = qMin(MaximumReputation, static_cast<qint8>(reputation(kingdom) + value));
}

const QHash <Kingdom, qint8> Player::InitialReputations {
	{Kingdom::Humans,    InitialReputation},
	{Kingdom::Dwarfs,    InitialReputation},
	{Kingdom::Elves,     InitialReputation},
	{Kingdom::Halflings, InitialReputation}
};

QList <Effect> Player::InitialEffects(Class playerClass, Race playerRace)
{
	static const QHash <Race, QList <Effect> > InitialRaceEffects = {
		{Race::Human,    {}},
		{Race::Dwarf,    {}},
		{Race::Elf,      {}},
		{Race::Halfling, {}},
	};

	static const QHash <Class, QList <Effect> > InitialClassEffects = {
		{Class::Fighter, {Effect(Effect::Type::MaxHealth,    15),
		                  Effect(Effect::Type::Defence,      10),
		                  Effect(Effect::Type::Perception,   1),
		                  Effect(Effect::Type::Regeneration, 2),
		                  Effect(Effect::Type::MeleeBase,    10),
		                  Effect(Effect::Type::RangedBase,   5),
		                  Effect(Effect::Type::MagicalBase,  1)}},

		{Class::Hunter,  {Effect(Effect::Type::MaxHealth,    13),
		                  Effect(Effect::Type::Defence,      8),
		                  Effect(Effect::Type::Perception,   7),
		                  Effect(Effect::Type::Regeneration, 3),
		                  Effect(Effect::Type::MeleeBase,    5),
		                  Effect(Effect::Type::RangedBase,   9),
		                  Effect(Effect::Type::MagicalBase,  1)}},

		{Class::Mage,    {Effect(Effect::Type::MaxHealth,    11),
		                  Effect(Effect::Type::Defence,      3),
		                  Effect(Effect::Type::Perception,   4),
		                  Effect(Effect::Type::Regeneration, 3),
		                  Effect(Effect::Type::MeleeBase,    2),
		                  Effect(Effect::Type::RangedBase,   1),
		                  Effect(Effect::Type::MagicalBase,  11)}},

		{Class::Druid,   {Effect(Effect::Type::MaxHealth,    13),
		                  Effect(Effect::Type::Defence,      9),
		                  Effect(Effect::Type::Perception,   3),
		                  Effect(Effect::Type::Regeneration, 5),
		                  Effect(Effect::Type::MeleeBase,    2),
		                  Effect(Effect::Type::RangedBase,   2),
		                  Effect(Effect::Type::MagicalBase,  8)}},
	};

	QList <Effect> initialEffects;
	initialEffects.append(Effect(Effect::Type::MeleeRange, InitialAttackRange));
	initialEffects.append(Effect(Effect::Type::RangedRange, InitialAttackRange));
	initialEffects.append(Effect(Effect::Type::MeleeRange, InitialAttackRange));
	initialEffects.append(Effect(Effect::Type::MovePoints, InitialMovePoints));
	initialEffects.append(InitialRaceEffects[playerRace]);
	initialEffects.append(InitialClassEffects[playerClass]);
	return initialEffects;
}

void Player::grantExperience(quint16 experience)
{
	experience_ += experience;
	if (level_ < MaximumLevel && experience >= LevelBorders[level_]) {
		++level_;
		growthPoints_ += GrowthPointsPerLevel;
		baseStats_.append(Effect(Effect::Type::MaxHealth, HealthIncreasePerLevel));
		heal(HealthIncreasePerLevel);
	}
}
