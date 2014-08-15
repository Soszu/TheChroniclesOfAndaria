#pragma once

#include <QtWidgets>
#include "Core/Utils/EnumHelpers.hpp"
#include "Core/Utils/BiHash.hpp"
#include "Core/Strings.h"
#include "Core/Containers/Effect.h"

enum class Attack : quint8 {
	Melee,
	Ranged,
	Magical
};
uint qHash(Attack attack);
QDataStream & operator<<(QDataStream &out, const Attack &attack);
QDataStream & operator>>(QDataStream &in, Attack &attack);


class Entity {
public:
	Entity();
	virtual const QPixmap & avatar() const = 0;
	quint16 health() const;
	QList <Effect> effects() const;
	virtual const QList <Effect> individualEffects() const = 0;
	virtual const QString & name() const = 0;
	Effect::Value value(Effect::Type attack) const;

protected:
	void initHealth();
	void heal(quint16 delta);
	void imposeEffect(const Effect &effect);
	void imposeEffects(const QList<Effect> &effects);

private:
	quint16 health_;
	QList <Effect> imposedEffects_;
};