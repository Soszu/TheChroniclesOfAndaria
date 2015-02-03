/*
Copyright (C) 2014-2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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
#include "Core/Utils/EnumHelpers.hpp"
#include "Core/Utils/BiHash.hpp"
#include "Core/Strings.hpp"

class Effect {
public:
	enum class Type : quint8 {
		//entity's stats
		MaxHealth,
		Perception,
		Defence,
		//attacks
		MeleeBase,
		MeleeRange,
		RangedBase,
		RangedRange,
		MagicalBase,
		MagicalRange,
		//player's stats
		Regeneration,
		MovePoints,
		//operations
		Heal,
		Vamp,
		Deflect,
		Absorb,
		//bonuses
		GoldBonus,
		ExperienceBonus,
		TradeBonus,
		//states
		Fear,
		Stun
	};
	static const BiHash <Type, QString> TypeLabels;

	typedef qint32 Value;
	typedef qint32 Duration;
	static const Duration Disposable = -1;
	static const Duration Permanent = -2;

	static bool isDisposable(const Effect &effect);
	static bool isPermanent(const Effect &effect);
	static QString description(const Effect &effect);
	static bool expired(const Effect &effect);
	static bool contains(const QList <Effect> &effects, Type type);
	static QList <Effect> filter(const QList <Effect> &effects, Type type);
	static Value sumValue(const QList <Effect> &effects);
	static Value sumValue(const QList <Effect> &effects, Type type);

	Effect(Type type = Type::MaxHealth, Value value = 0, Duration duration = Permanent);
	Effect(const Effect &effect) = default;

	bool operator==(const Effect &other) const;

	Duration duration() const;
	QDataStream & toDataStream(QDataStream &out) const;
	Type type() const;
	Value value() const;

	QDataStream & fromDataStream(QDataStream &in);
	void setDuration(Effect::Duration);
	void setType(Effect::Type);
	void setValue(Effect::Value);
	void shorten();

private:
	Type type_;
	Value value_;
	Duration duration_;
};
Q_DECLARE_METATYPE(Effect)
Q_DECLARE_METATYPE(Effect::Type)

QDataStream & operator<<(QDataStream &out, const Effect &effect);
QDataStream & operator>>(QDataStream &in, Effect &effect);
uint qHash(const Effect::Type type);
QDataStream & operator<<(QDataStream &out, const Effect::Type &effectType);
QDataStream & operator>>(QDataStream &in, Effect::Type &effectType);
