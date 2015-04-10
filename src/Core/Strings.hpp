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
	namespace Effect {
		const QString Type     = QObject::tr("Type");
		const QString Value    = QObject::tr("Value");
		const QString Duration = QObject::tr("Duration");
	}

	namespace Quest {
		const QString DefaultName      = QObject::tr("Quest");
		const QString Title            = QObject::tr("Title");
		const QString Description      = QObject::tr("Description");
		const QString Fraction         = QObject::tr("Fraction");
		const QString Level            = QObject::tr("Level");
		const QString Difficulty       = QObject::tr("Difficulty");
		const QString IsReturnRequired = QObject::tr("Is return required?");
		const QString CanBeDrawn       = QObject::tr("Can be drawn\nfrom deck?");
		const QString FollowUp         = QObject::tr("Follow Up");
		const QString Objectives       = QObject::tr("Objectives");
		const QString Reward           = QObject::tr("Reward");
	}

	namespace Item {
		const QString DefaultName = QObject::tr("Item");
		const QString Name        = QObject::tr("Name");
		const QString Type        = QObject::tr("Type");
		const QString Price       = QObject::tr("Price");
		const QString Quality     = QObject::tr("Quality");
		const QString CanBeDrawn  = QObject::tr("CanBeDrawn");
		const QString Effects     = QObject::tr("Effects");
	}

	namespace Enemy {
		const QString DefaultName   = QObject::tr("Enemy");
		const QString Name          = QObject::tr("Name");
		const QString ImageName     = QObject::tr("Image name");
		const QString Level         = QObject::tr("Level");
		const QString Type          = QObject::tr("Type");
		const QString DefaultAttack = QObject::tr("Default attack");
		const QString BaseStats     = QObject::tr("Base stats");
		const QString WinningPrize  = QObject::tr("Winning prize");
	}
}

namespace Strings {
	const QString ModFilesExtension = QObject::tr(".tcoa");
	const QString ModFiles          = QObject::tr("TCOA mod files (*%1)").arg(ModFilesExtension);
}
