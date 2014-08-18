/*
Copyright (C) 2014 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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

namespace Label {
	// Kingdom
	const QString Neutral   = QObject::tr("Neutral");
	const QString Humans    = QObject::tr("Humans");
	const QString Dwarfs    = QObject::tr("Dwarfs");
	const QString Elves     = QObject::tr("Elves");
	const QString Halflings = QObject::tr("Halflings");

	//Race
	const QString Human    = QObject::tr("Human");
	const QString Dwarf    = QObject::tr("Dwarf");
	const QString Elf      = QObject::tr("Elf");
	const QString Halfling = QObject::tr("Halfling");

	//Class
	const QString Fighter = QObject::tr("Fighter");
	const QString Hunter  = QObject::tr("Hunter");
	const QString Mage    = QObject::tr("Mage");
	const QString Druid   = QObject::tr("Druid");

	//Attack
	const QString Melee   = QObject::tr("Melee");
	const QString Ranged  = QObject::tr("Ranged");
	const QString Magical = QObject::tr("Magical");

	//Effect
	const QString MaxHealth       = QObject::tr("Maximum Health");
	const QString Perception      = QObject::tr("Perception");
	const QString Defence         = QObject::tr("Defence");
	const QString MeleeBase       = QObject::tr("Melee Attack Base");
	const QString MeleeRange      = QObject::tr("Melee Attack Range");
	const QString RangedBase      = QObject::tr("Range Attack Base");
	const QString RangedRange     = QObject::tr("Ranged Attack Range");
	const QString MagicalBase     = QObject::tr("Magical Attack Base");
	const QString MagicalRange    = QObject::tr("Magical Attack Range");
	const QString Regeneration    = QObject::tr("Regeneration");
	const QString MovePoints      = QObject::tr("Move Points");
	const QString Heal            = QObject::tr("Heal");
	const QString Wamp            = QObject::tr("Wamp");
	const QString GoldBonus       = QObject::tr("Gold Bonus");
	const QString ExperienceBonus = QObject::tr("Experience Bonus");
	const QString TradeBonus      = QObject::tr("Trade Bonus");
	const QString Fear            = QObject::tr("Fear");
	const QString Retention       = QObject::tr("Retention");

	//Quest
	namespace Quest {
		//Level
		const QString Easy   = QObject::tr("Easy");
		const QString Medium = QObject::tr("Medium");
		const QString Hard   = QObject::tr("Hard");
	}

	//Item
	namespace Item {
		//Type
		const QString Armor           = QObject::tr("Armor");
		const QString Artifact        = QObject::tr("Artifact");
		const QString Helmet          = QObject::tr("Helmet");
		const QString Shield          = QObject::tr("Shield");
		const QString OneHandedWeapon = QObject::tr("OneHandedWeapon");
		const QString TwoHandedWeapon = QObject::tr("TwoHandedWeapon");
		const QString Potion          = QObject::tr("Potion");

		//Quality
		const QString NotApplicable = QObject::tr("Not Applicable");
		const QString Standard      = QObject::tr("Standard");
		const QString Magical       = QObject::tr("Magical");
		const QString Legendary     = QObject::tr("Legendary");
	}
}

//Defaults
namespace Default {
	const QString ItemName = QObject::tr("Item");
}
