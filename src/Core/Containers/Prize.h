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
#include "Core/Containers/Effect.h"
#include "Core/Containers/Item.h"

enum class Kingdom : quint8;

class Prize {
public:
	Prize();
	Prize(QList <Effect> effects,
	      quint16 experience,
	      QList <Item> items,
	      quint16 gold,
	      QHash <Kingdom, qint8> reputations);

	const QList <Effect> &effects() const;
	quint16 experience() const;
	quint16 gold() const;
	const QList <Item> & items() const;
	const qint8 reputation(Kingdom kingdom) const;
	const QHash <Kingdom, qint8> & reputations() const;
	QDataStream & toDataStream(QDataStream &out) const;

	void addEffect(Effect effect);
	void addItem(Item item);
	void addReputation(Kingdom kingdom, qint8 reputation);
	QDataStream & fromDataStream(QDataStream &in);
	void setEffects(QList <Effect> effects);
	void setExperience(quint16 experience);
	void setGold(quint16 gold);
	void setItems(QList <Item> items);
	void setReputations(QHash <Kingdom, qint8> reputations);

private:
	QList <Effect> effects_;
	quint16 experience_;
	QList <Item> items_;
	quint16 gold_;
	QHash <Kingdom, qint8> reputations_;
};

QDataStream & operator<<(QDataStream &out, const Prize &prize);
QDataStream & operator>>(QDataStream &in, Prize &prize);
