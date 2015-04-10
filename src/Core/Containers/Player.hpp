/*
Copyright (C) 2013-2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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

#include <QtCore>

#include "Core/EnumsDeclarations.hpp"
#include "Core/Containers/Entity.hpp"
#include "Core/Containers/Equipment.hpp"
#include "Core/Containers/Journal.hpp"
#include "Core/Containers/Coordinates.hpp"

class Mod;
class PlayerDraft;
class Prize;

class Player : public Entity {
public:
	static const quint8 MaximumLevel = 10;
	static const quint8 GrowthPointsPerLevel = 3;
	static const quint8 AttributeGrowth = 1;
	static const quint8 HealthIncreasePerLevel = 3;
	static const quint16 LevelBorders[MaximumLevel];
	static const qint8 MaximumReputation = 5;

	static const QSet<Effect::Type> extendableAttributes;

	Player(const PlayerDraft & draft, const Mod & mod);

	const QPixmap & avatar() const;
	QColor color() const;
	const Equipment & equipment() const;
	quint16 experience() const;
	const Journal & journal() const;
	quint8 level() const;
	quint16 gold() const;
	quint8 growthPoints() const;
	const QList<Effect> individualEffects() const;
	const QString & name() const;
	Race playerRace() const;
	Class playerClass() const;
	Coordinates position() const;
	const qint8 reputation(Kingdom kingdom) const;

	void consumeGrowthPoint(Effect::Type attribute);
	Equipment & equipment();
	Journal & journal();
	void grantPrize(const Prize & prize);
	void move(Coordinates field);
	void regenerate();
	void shiftGold(qint16 amount);
	void shiftReputation(Kingdom kingdom, qint8 value);

private:
	static const quint8  InitialLevel = 1;
	static const quint8  InitialGrowthPoints = 3;
	static const quint16 InitialExperience = 0;
	static const quint16 InitialGold = 3;
	static const quint8  InitialReputation = 0;
	static const QHash<Kingdom, qint8> InitialReputations;
	static const quint8  InitialMovePoints = 8;
	static const quint16 InitialAttackRange = 10;
	static const QList<Effect> & InitialEffects(Class playerClass, Race playerRace);

	void grantExperience(quint16 experience);

	const QString name_;
	const QPixmap avatar_;
	const Race playerRace_;
	const Class playerClass_;
	const QColor color_;
	quint8 level_;
	quint8 growthPoints_;
	QList<Effect> baseStats_;
	quint16 experience_;
	quint16 gold_;
	Coordinates position_;
	Equipment equipment_;
	Journal journal_;
	QHash<Kingdom, qint8> reputations_;
};
