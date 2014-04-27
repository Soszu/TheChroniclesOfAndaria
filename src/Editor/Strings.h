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
