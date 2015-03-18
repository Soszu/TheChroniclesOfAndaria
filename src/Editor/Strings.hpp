/*
Copyright (C) 2014-2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
Copyright (C) 2015 by Marcin Parafiniuk <jessie [dot] inferno [at] gmail [dot] com>
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

namespace Editor {
	namespace Messages {
		const QString ModLoaded  = QObject::tr("Mod loaded");
		const QString ModSaved   = QObject::tr("Mod saved");

		const QString ModModified      = QObject::tr("Mod has been modified.");
		const QString AskIfSaveChanges = QObject::tr("Do you want to save your changes?");
	}

	namespace Menus {
		namespace Mod {
			const QString Main   = QObject::tr("&Mod");
			const QString New    = QObject::tr("&New");
			const QString Open   = QObject::tr("&Open...");
			const QString LoadTxt= QObject::tr("&Load from txt");
			const QString Save   = QObject::tr("&Save");
			const QString SaveAs = QObject::tr("Save &As...");
			const QString Quit   = QObject::tr("&Quit");
		}
	}

	namespace Titles {
		const QString EditorWindow   = QObject::tr("[*]TCOA Editor");
		const QString OpenFileDialog = QObject::tr("Open mod");
		const QString SaveFileDialog = QObject::tr("Save mod");

		const QString Board   = QObject::tr("Board");
		const QString Items   = QObject::tr("Items");
		const QString Enemies = QObject::tr("Enemies");
		const QString Quests  = QObject::tr("Quests");
	}

	namespace Labels {
		const QString Add      = QObject::tr("Add");
		const QString Remove   = QObject::tr("Remove");

		namespace Effects {
			const QString List     = QObject::tr("List");
			const QString Details  = QObject::tr("Details");

			const QString Add      = QObject::tr("Add");
			const QString Remove   = QObject::tr("Remove");
		}

		namespace Prize {
			const QString Experience         = QObject::tr("Experience");
			const QString Gold               = QObject::tr("Gold");
			const QString Effects            = QObject::tr("Effects");
			const QString KingdomReputations = QObject::tr("Kingdom Reputations");
			const QString AddKingdom         = QObject::tr("Add Kingdom");
		}

		namespace BoardTools {
			const QString BoardSize        = QObject::tr("Board size");
			const QString BoardColumns     = QObject::tr("Board columns");
			const QString BoardRows        = QObject::tr("Board rows");

			const QString Terrains         = QObject::tr("Terrains");
			const QString Ruling           = QObject::tr("Ruling");
			const QString InitialPositions = QObject::tr("Initial Positions");
		}
	}
}
