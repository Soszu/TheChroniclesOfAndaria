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

namespace Message {
	const QString HowToStart    = QObject::tr("Use \"New\" or \"Open\" from \"File\" menu to start");
	const QString ContentLoaded = QObject::tr("Content loaded");
	const QString ContentSaved  = QObject::tr("Content saved");
}

namespace Menu {
	namespace File {
		const QString Main   = QObject::tr("&File");
		const QString New    = QObject::tr("New");
		const QString Open   = QObject::tr("Open");
		const QString Save   = QObject::tr("Save");
		const QString SaveAs = QObject::tr("Save as");
		const QString Quit   = QObject::tr("Quit");
	}
}

namespace Title {
	const QString EditorWindow   = QObject::tr("TCOA Editor");
	const QString OpenFileDialog = QObject::tr("Open Content");
	const QString SaveFileDialog = QObject::tr("Save Content");

	const QString Items   = QObject::tr("Items");
	const QString Enemies = QObject::tr("Enemies");
	const QString Quests  = QObject::tr("Quests");
}

namespace Label {
	namespace Item {
		const QString Name    = QObject::tr("Name");
		const QString Type    = QObject::tr("Type");
		const QString Quality = QObject::tr("Quality");
		const QString Price   = QObject::tr("Price");
		const QString Effects = QObject::tr("Effects");
	}
	namespace Enemy {
		const QString Name          = QObject::tr("Name");
		const QString ImagePath     = QObject::tr("Image path");
		const QString Level         = QObject::tr("Level");
		const QString DefaultAttack = QObject::tr("Default attack");
		const QString BaseStats     = QObject::tr("Base stats");
		const QString WinningPrize  = QObject::tr("Winning prize");
	}
	namespace Editor {
		const QString Add      = QObject::tr("Add");
		const QString Remove   = QObject::tr("Remove");
	}

	namespace Effect {
		const QString List     = QObject::tr("List");
		const QString Details  = QObject::tr("Details");

		const QString Type     = QObject::tr("Type");
		const QString Value    = QObject::tr("Value");
		const QString Duration = QObject::tr("Duration");

		const QString Add      = QObject::tr("Add");
		const QString Remove   = QObject::tr("Remove");
	}
}

namespace String {
	const QString ContentFilesExtension = QObject::tr("tcoa");
	const QString ContentFiles          = QObject::tr("TCOA content files (*.%1)").arg(ContentFilesExtension);
}
