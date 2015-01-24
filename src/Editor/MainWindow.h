/*
 *TODO
 * paths
 * window and widgets size in const variables listed in one place
 * separate common files if any
 */

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

#include <QtWidgets>
#include "Editor/Strings.h"
#include "Editor/Shortcuts.h"
#include "Editor/Editors/ContentEditor.h"

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	MainWindow();
	~MainWindow();

private:
	void initMenuAndActions();
	void initContentEditors();
	void initModelsList();
	void initEditorsWidgets();
	void initLayout();

	bool loadContent(const QString &path);
	bool saveContent(const QString &path);
	int checkForUnsavedChanges();

	QString openedFilePath;

	QAction *menuFileSave;
	QAction *menuFileSaveAs;

	QSplitter *placeholder;
	QListWidget *modelsList_;
	QStackedWidget *modelsWidgets_;
	QList<ContentEditor *> contentEditors_;

private slots:
	void onNewActivated();
	void onLoadActivated();
	void onSaveActivated();
	void onSaveAsActivated();
	void onQuitActivated();

	void startEditing();

signals:
	void modelSaved();
};
