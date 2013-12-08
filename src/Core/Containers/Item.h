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

#ifndef ITEM_H
#define ITEM_H

#include <QtGui>

//TODO CFiend to powinn być public Item { enum class Type };
enum ItemType {
	bronDwureczna,
	bronJednoreczna,
	tarcza,
	pancerz,
	helm,
	artefakt,
	mikstura
};

static const int NUMBER_OF_POSSIBLE_QUALITIES(4);

enum ItemQuality {
	notApplicable,
	poor,
	normal,
	good
};

static const quint8 LICZBA_RODZAJOW_PRZEDMIOTOW = 7;

static const QString RODZAJE_PRZEDMIOTOW[LICZBA_RODZAJOW_PRZEDMIOTOW] = {
	QString::fromUtf8("broń dwuręczna"),
	QString::fromUtf8("broń jednoręczna"),
	QString::fromUtf8("tarcza"),
	QString::fromUtf8("pancerz"),
	QString::fromUtf8("hełm"),
	QString::fromUtf8("artefakt"),
	QString::fromUtf8("mikstura"),
};

class Item {

public:
	Item(QString name,
	     ItemType type,
	     int bonusMelee,
	     int bonusRanged,
	     int bonusMagical,
	     int bonusDefence,
	     int bonusPerception,
	     int bonusHitPoints,
	     int bonusRegeneration,
	     int restrictions,
	     int value,
	     bool isStrong,
	     ItemQuality quality);

	QString name() const;
	ItemType type() const;
	int bonusMelee() const;
	int bonusRanged() const;
	int bonusMagical() const;
	int bonusDefence() const;
	int bonusPerception() const;
	int bonusHitPoints() const;
	int bonusRegeneration() const;
	int restrictions() const;
	int value() const;
	bool isStrong() const;
	ItemQuality quality() const;

	static const quint8 ArtifactLimit = 5;

private:
	QString name_;
	ItemType type_;
	int bonusMelee_;
	int bonusRanged_;
	int bonusMagical_;
	int bonusDefence_;
	int bonusPerception_;
	int bonusHitPoints_;
	int bonusRegeneration_;
	int restrictions_;
	int value_;
	bool isStrong_;
	ItemQuality quality_;
};

#endif
