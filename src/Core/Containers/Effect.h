#pragma once

#include <QtCore>
#include "Core/Utils/EnumHelpers.hpp"
#include "Core/Utils/BiHash.hpp"
#include "Core/Strings.h"

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
		Wamp,
		//bonuses
		GoldBonus,
		ExperienceBonus,
		TradeBonus,
		//states
		Fear,
		Retention
	};
	static const BiHash <Type, QString> TypeLabels;

	typedef qint32 Value;
	typedef qint32 Duration;
	static const Duration Disposable = -1;
	static const Duration Permanent = -2;

	inline bool isDisposable(const Effect &effect);
	inline bool isPermanent(const Effect &effect);
	inline bool expired(const Effect &effect);
	static bool contains(const QList <Effect> &effects, Type type);
	static QList <Effect> filter(const QList <Effect> &effects, Type type);
	static Value sumValue(const QList <Effect> &effects);
	static Value sumValue(const QList <Effect> &effects, Type type);

	Effect(Type type = Type::MaxHealth, Value value = 0, Duration duration = Permanent);
	Effect(const Effect &effect) = default;

	Duration duration() const;
	QDataStream & toDataStream(QDataStream &out) const;
	Type type() const;
	Value value() const;

	QDataStream & fromDataStream(QDataStream &in);
	void shorten();

private:
	Type type_;
	Value value_;
	Duration duration_;
};

QDataStream & operator<<(QDataStream &out, const Effect &effect);
QDataStream & operator>>(QDataStream &in, Effect &effect);
uint qHash(const Effect::Type type);
QDataStream & operator<<(QDataStream &out, const Effect::Type &effectType);
QDataStream & operator>>(QDataStream &in, Effect::Type &effectType);
