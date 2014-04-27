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

#ifndef EDITOR_STRINGS_H
#define EDITOR_STRINGS_H

#include <QtCore>
#include "Editor/Shortcuts.h"

namespace Editor {

	namespace Messages {
		const QString HowToStart    = QObject::tr("Use \"New\" or \"Open\" from \"File\" menu to start");
		const QString ContentLoaded = QObject::tr("Content loaded");
		const QString ContentSaved  = QObject::tr("Content saved");
	}

	namespace Strings {
		const QString MenuFile       = QObject::tr("&File");
		const QString MenuFileNew    = QObject::tr("New");
		const QString MenuFileOpen   = QObject::tr("Open");
		const QString MenuFileSave   = QObject::tr("Save");
		const QString MenuFileSaveAs = QObject::tr("Save as");
		const QString MenuFileQuit   = QObject::tr("Quit");

		const QString OpenFileDialog        = QObject::tr("Open Content");
		const QString SaveFileDialog        = QObject::tr("Save Content");
		const QString ContentFilesExtension = QObject::tr("tcoa");
		const QString ContentFiles          = QObject::tr("TCOA content files (*.%1)").arg(ContentFilesExtension);

	}
}

#endif //EDITOR_STRINGS_H
