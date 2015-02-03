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

namespace Labels {
	namespace Kingdoms {
		const QString Neutral   = QObject::tr("Neutral");
		const QString Humans    = QObject::tr("Humans");
		const QString Dwarfs    = QObject::tr("Dwarfs");
		const QString Elves     = QObject::tr("Elves");
		const QString Halflings = QObject::tr("Halflings");
	}

	namespace Races {
		const QString Human    = QObject::tr("Human");
		const QString Dwarf    = QObject::tr("Dwarf");
		const QString Elf      = QObject::tr("Elf");
		const QString Halfling = QObject::tr("Halfling");
	}

	namespace Classes {
		const QString Fighter = QObject::tr("Fighter");
		const QString Hunter  = QObject::tr("Hunter");
		const QString Mage    = QObject::tr("Mage");
		const QString Druid   = QObject::tr("Druid");
	}

	namespace Attacks {
		const QString Melee   = QObject::tr("Melee");
		const QString Ranged  = QObject::tr("Ranged");
		const QString Magical = QObject::tr("Magical");
	}

	namespace Actions {
		const QString GoToMarket       = QObject::tr("Go to market");
		const QString GoToTavern       = QObject::tr("Go to tavern");
		const QString FightWithMonster = QObject::tr("Fight with monster");
		const QString EndTurn          = QObject::tr("End turn");
	}

	namespace Effect {
		const QString Type     = QObject::tr("Type");
		const QString Value    = QObject::tr("Value");
		const QString Duration = QObject::tr("Duration");
		namespace Types {
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
			const QString Vamp            = QObject::tr("Vamp");
			const QString Absorb          = QObject::tr("Absorb");
			const QString Deflect         = QObject::tr("Deflect");
			const QString GoldBonus       = QObject::tr("Gold Bonus");
			const QString ExperienceBonus = QObject::tr("Experience Bonus");
			const QString TradeBonus      = QObject::tr("Trade Bonus");
			const QString Fear            = QObject::tr("Fear");
			const QString Stun            = QObject::tr("Stun");
		}
	}

	namespace Quest {
		const QString DefaultName      = QObject::tr("Quest");
		const QString Title            = QObject::tr("Title");
		const QString Description      = QObject::tr("Description");
		const QString Fraction         = QObject::tr("Fraction");
		const QString Level            = QObject::tr("Level");
		const QString IsReturnRequired = QObject::tr("Is return required?");
		const QString CanBeDrawn       = QObject::tr("Can be drawn\nfrom deck?");
		const QString FollowUp         = QObject::tr("Follow Up");
		const QString Objectives       = QObject::tr("Objectives");
		const QString Reward           = QObject::tr("Reward");
		namespace Levels {
			const QString Easy   = QObject::tr("Easy");
			const QString Medium = QObject::tr("Medium");
			const QString Hard   = QObject::tr("Hard");
		}
	}

	namespace Item {
		const QString DefaultName = QObject::tr("Item");
		const QString Name        = QObject::tr("Name");
		const QString Type        = QObject::tr("Type");
		const QString Quality     = QObject::tr("Quality");
		const QString Price       = QObject::tr("Price");
		const QString Effects     = QObject::tr("Effects");
		namespace Types {
			const QString Armor           = QObject::tr("Armor");
			const QString Artifact        = QObject::tr("Artifact");
			const QString Helmet          = QObject::tr("Helmet");
			const QString Shield          = QObject::tr("Shield");
			const QString OneHandedWeapon = QObject::tr("OneHandedWeapon");
			const QString TwoHandedWeapon = QObject::tr("TwoHandedWeapon");
			const QString Potion          = QObject::tr("Potion");
		}
		namespace Qualities {
			const QString NotApplicable = QObject::tr("Not Applicable");
			const QString Standard      = QObject::tr("Standard");
			const QString Magical       = QObject::tr("Magical");
			const QString Legendary     = QObject::tr("Legendary");
		}
	}

	namespace Enemy {
		const QString DefaultName   = QObject::tr("Enemy");
		const QString Name          = QObject::tr("Name");
		const QString ImageName     = QObject::tr("Image name");
		const QString Level         = QObject::tr("Level");
		const QString DefaultAttack = QObject::tr("Default attack");
		const QString BaseStats     = QObject::tr("Base stats");
		const QString WinningPrize  = QObject::tr("Winning prize");
	}
}

namespace Strings {
	const QString ModFilesExtension = QObject::tr("tcoa");
	const QString ModFiles          = QObject::tr("TCOA mod files (*.%1)").arg(ModFilesExtension);
}
