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

#ifndef ITEMBASE_H
#define ITEMBASE_H

#include <QtCore>
#include "Core/Game.h"
#include "Core/Util/Serial.hpp"

namespace TCOA {
	enum class PlayerClass : quint8;
	enum class ItemType : quint8 {
		// Wearable items:
		TwoHandedWeapon,
		OneHandedWeapon,
		Shield,
		Armor,
		Helmet,
		Artifact,
		//One-time use items:
		Potion,
		Scroll
	};

	enum class Quality : quint8 {
		NotApplicable,
		Poor,
		Normal,
		Good
	};
}

public:
	ItemBase();
	ItemBase(UID uid, const QString &name);

	UID uid() const;

	QString name() const;
	void setName(const QString &name);

	TCOA::ItemType type() const;
	void setType(TCOA::ItemType type);

	int value() const;
	void setValue(int value);

	QHash <TCOA::PlayerClass, bool> restrictions() const;
	void setRestrictions(QHash <TCOA::PlayerClass, bool> restrictions);

	QList <HOA::Effect> effects() const;
	void setEffects(QList <HOA::Effect> effect);

	friend QDataStream & operator << (QDataStream &out, const ItemBase &item);
	friend QDataStream & operator >> (QDataStream &in, ItemBase &item);

private:
	UID uid_;

	QString name_;

	HOA::ItemType type_;
	QHash <TCOA::PlayerClass, bool> restrictions_;

	int value_;

	QList <HOA::Effect> effects_;
};
#endif // ITEMBASE_H
