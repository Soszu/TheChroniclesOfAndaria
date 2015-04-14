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
#include "Editor/MainWindow.hpp"

#include "Core/Mod.hpp"
#include "Core/Paths.hpp"
#include "Core/Strings.hpp"
#include "Editor/Editors/BoardEditor.hpp"
#include "Editor/Editors/ItemsEditor.hpp"
#include "Editor/Editors/EnemiesEditor.hpp"
#include "Editor/Editors/QuestEditor.hpp"
#include "Editor/Shortcuts.hpp"

MainWindow::MainWindow() :
	mod_(new Mod)
{
	Q_INIT_RESOURCE(resources);

	resize(1024, 768);
	setWindowTitle(tr("[*]TCOA Editor"));

	initMenuAndActions();
	initEditors();
}

void MainWindow::initMenuAndActions()
{
	using namespace Editor;

	QMenu *modMenu = menuBar()->addMenu(tr("&Mod"));

	QAction *menuModNew     = new QAction(tr("&New"),           this);
	QAction *menuModLoad    = new QAction(tr("&Open..."),       this);
	QAction *menuModLoadTxt = new QAction(tr("&Load from txt"), this);
	QAction *menuModSave_   = new QAction(tr("&Save"),          this);
	QAction *menuModSaveAs_ = new QAction(tr("Save &As..."),    this);
	QAction *menuModQuit    = new QAction(tr("&Quit"),          this);

	connect(menuModNew,     &QAction::triggered, this, &MainWindow::onNewActivated);
	connect(menuModLoad,    &QAction::triggered, this, &MainWindow::onLoadActivated);
	connect(menuModLoadTxt, &QAction::triggered, this, &MainWindow::onLoadTxtActivated);
	connect(menuModSave_,   &QAction::triggered, this, &MainWindow::onSaveActivated);
	connect(menuModSaveAs_, &QAction::triggered, this, &MainWindow::onSaveAsActivated);
	connect(menuModQuit,    &QAction::triggered, this, &MainWindow::onQuitActivated);

	menuModNew->setShortcut(Shortcuts::Menus::Mod::New);
	menuModLoad->setShortcut(Shortcuts::Menus::Mod::Open);
	menuModSave_->setShortcut(Shortcuts::Menus::Mod::Save);
	menuModQuit->setShortcut(Shortcuts::Menus::Mod::Quit);

	modMenu->addAction(menuModNew);
	modMenu->addAction(menuModLoad);
	modMenu->addAction(menuModLoadTxt);
	modMenu->addAction(menuModSave_);
	modMenu->addAction(menuModSaveAs_);
	modMenu->addSeparator();
	modMenu->addAction(menuModQuit);
}

void MainWindow::initEditors()
{
	editorTabs_ = new QTabWidget;
	setCentralWidget(editorTabs_);

	editorTabs_->addTab(new BoardEditor(mod_->boardModel()),   tr("Board"));
	editorTabs_->addTab(new ItemsEditor(mod_->itemModel()),    tr("Items"));
	editorTabs_->addTab(new EnemiesEditor(mod_->enemyModel()), tr("Enemies"));
	editorTabs_->addTab(new QuestEditor(mod_->questModel()),   tr("Quests"));
}

int MainWindow::checkForUnsavedChanges()
{
	if (!mod_->unsavedChanges())
		return QMessageBox::Discard;

	QMessageBox msgBox;
	msgBox.setText(tr("Mod has been modified."));
	msgBox.setInformativeText(tr("Do you want to save your changes?"));
	msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Save);

	return msgBox.exec();
}

void MainWindow::onNewActivated()
{
	switch (checkForUnsavedChanges()) {
		case QMessageBox::Save:
			if (!onSaveActivated())
				return;
			/* NOTE: fall-through */
		case QMessageBox::Discard:
			mod_->reset();
			break;
		default:
			return;
	}
}

void MainWindow::onLoadActivated()
{
	switch (checkForUnsavedChanges()) {
		case QMessageBox::Save:
			if (!onSaveActivated())
				return;
			/* NOTE: fall-through */
		case QMessageBox::Discard:
			break;
		default:
			return;
	}

	QString path = QFileDialog::getOpenFileName(this, tr("Open mod"),
	                                            resolvePath(Path::ModsDir), Strings::ModFiles);
	mod_->load(path);

	currentFilePath_ = path;
}

void MainWindow::onLoadTxtActivated()
{
	switch (checkForUnsavedChanges()) {
		case QMessageBox::Save:
			if (!onSaveActivated())
				return;
			/* NOTE: fall-through */
			case QMessageBox::Discard:
				break;
			default:
				return;
	}

	mod_->loadFromTxt();
}

bool MainWindow::onSaveActivated()
{
	if (currentFilePath_.isEmpty())
		return onSaveAsActivated();

	if (mod_->save(currentFilePath_)) {
		emit modelSaved();
		return true;
	}

	return false;
}

bool MainWindow::onSaveAsActivated()
{
	QString path = QFileDialog::getSaveFileName(this, tr("Save mod"),
	                                            resolvePath(Path::ModsDir), Strings::ModFiles);

	if (!path.endsWith(Strings::ModFilesExtension))
		path.append(Strings::ModFilesExtension);

	if (mod_->save(path)) {
		emit modelSaved();
		currentFilePath_ = path;
		return true;
	}

	return false;
}

void MainWindow::onQuitActivated()
{
	switch (checkForUnsavedChanges()) {
		case QMessageBox::Save:
			if (!onSaveActivated())
				return;
			/* NOTE: fall-through */
		case QMessageBox::Discard:
			close();
			break;
		default:
			break;
	}
}
