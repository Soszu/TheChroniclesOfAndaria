/*
Copyright (C) 2013 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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
#include "Core/Utils/Serial.hpp"
#include "Core/Utils/BiHash.hpp"
#include "Core/Containers/Effect.h"

enum class Class : quint8;

class ItemBase {
public:
	enum class Type : quint8 {
		Artifact,
		// Wearable items:
		Armor,
		Helmet,
		Shield,
		Aura,
		OneHandedWeapon,
		TwoHandedWeapon,
		//disposable use items:
		Potion
	};
	static const BiHash <Type, QString> TypeLabels;

	enum class Quality : quint8 {
		NotApplicable,
		Standard,
		Magical,
		Legendary
	};
	static const BiHash <Quality, QString> QualityLabels;

	ItemBase(UID uid = Serial::MinUid, const QString &name = QString());
	ItemBase(UID uid,
	         const QString &name,
	         Type type,
	         quint16 price,
	         Quality quality,
	         const QList <Effect> effects);

	const QList <Effect> & effects() const;
	const QString & name() const;
	quint16 price() const;
	Quality quality() const;
	const QHash <Class, bool> & restrictions() const;
	QDataStream & toDataStream(QDataStream &out) const;
	Type type() const;
	UID uid() const;

	void addEffect(const Effect &effect);
	QDataStream & fromDataStream(QDataStream &in);
	void setEffects(const QList <Effect> &effects);
	void setName(const QString &name);
	void setPrice(quint16 price);
	void setQuality(Quality quality);
	void setRestriction(Class playerClass, bool value);
	void setRestrictions(const QHash <Class, bool> &restrictions);
	void setType(Type type);
	void toggleRestriction(Class playerClass);

private:

	UID uid_;
	QString name_;
	Type type_;
	quint16 price_;
	Quality quality_;
	QList <Effect> effects_;
};
Q_DECLARE_METATYPE(ItemBase::Type)
Q_DECLARE_METATYPE(ItemBase::Quality)

QDataStream & operator<<(QDataStream &out, const ItemBase &base);
QDataStream & operator>>(QDataStream &in, ItemBase &base);
uint qHash(ItemBase::Type type);
QDataStream & operator<<(QDataStream &out, const ItemBase::Type &type);
QDataStream & operator>>(QDataStream &in, ItemBase::Type &type);
uint qHash(ItemBase::Quality quality);
QDataStream & operator<<(QDataStream &out, const ItemBase::Quality &quality);
QDataStream & operator>>(QDataStream &in, ItemBase::Quality &quality);
