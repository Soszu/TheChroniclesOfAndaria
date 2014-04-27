#ifndef EDITOR_SHORTCUTS_H
#define EDITOR_SHORTCUTS_H

#include <QtCore>

namespace Editor {
	namespace Shortcuts {
		const QKeySequence MenuFileNew  = QObject::tr("Ctrl+N");
		const QKeySequence MenuFileOpen = QObject::tr("Ctrl+O");
		const QKeySequence MenuFileSave = QObject::tr("Ctrl+S");
		const QKeySequence MenuFileQuit = QObject::tr("Ctrl+Q");
	}
}

#endif //EDITOR_SHORTCUTS_H
