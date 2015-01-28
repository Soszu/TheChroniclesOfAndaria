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
#include "Editor/MainWindow.h"

#include "Core/Mod.h"
#include "Core/Paths.h"
#include "Core/Strings.h"
#include "Editor/Editors/ItemsEditor.h"
#include "Editor/Editors/EnemiesEditor.h"
#include "Editor/Strings.h"
#include "Editor/Shortcuts.h"

MainWindow::MainWindow() : mod_(new Mod)
{
	resize(800, 600);
	setWindowTitle(Editor::Titles::EditorWindow);

	initMenuAndActions();
	initEditors();
}

void MainWindow::initMenuAndActions()
{
	using namespace Editor;

	QMenu *modMenu = menuBar()->addMenu(Menus::Mod::Main);

	QAction *menuModNew  = new QAction(Menus::Mod::New,    this);
	QAction *menuModLoad = new QAction(Menus::Mod::Open,   this);
	menuModSave_         = new QAction(Menus::Mod::Save,   this);
	menuModSaveAs_       = new QAction(Menus::Mod::SaveAs, this);
	QAction *menuModQuit = new QAction(Menus::Mod::Quit,   this);

	connect(menuModNew,     &QAction::triggered, this, &MainWindow::onNewActivated);
	connect(menuModLoad,    &QAction::triggered, this, &MainWindow::onLoadActivated);
	connect(menuModSave_,   &QAction::triggered, this, &MainWindow::onSaveActivated);
	connect(menuModSaveAs_, &QAction::triggered, this, &MainWindow::onSaveAsActivated);
	connect(menuModQuit,    &QAction::triggered, this, &MainWindow::onQuitActivated);

	menuModNew->setShortcut(Shortcuts::Menus::Mod::New);
	menuModLoad->setShortcut(Shortcuts::Menus::Mod::Open);
	menuModSave_->setShortcut(Shortcuts::Menus::Mod::Save);
	menuModQuit->setShortcut(Shortcuts::Menus::Mod::Quit);

	menuModSave_->setEnabled(false);
	menuModSaveAs_->setEnabled(false);

	modMenu->addAction(menuModNew);
	modMenu->addAction(menuModLoad);
	modMenu->addAction(menuModSave_);
	modMenu->addAction(menuModSaveAs_);
	modMenu->addSeparator();
	modMenu->addAction(menuModQuit);
}

void MainWindow::initEditors()
{
	editorTabs_ = new QTabWidget;
	setCentralWidget(editorTabs_);

	editorTabs_->hide();

	editorTabs_->addTab(new ItemsEditor(mod_->itemModel()), Editor::Titles::Items);
	editorTabs_->addTab(new EnemiesEditor(mod_->enemyModel()), Editor::Titles::Enemies);

}

void MainWindow::startEditing()
{
	menuModSave_->setEnabled(true);
	menuModSaveAs_->setEnabled(true);

	editorTabs_->show();
}

int MainWindow::checkForUnsavedChanges()
{
	if (not mod_->unsavedChanges())
		return QMessageBox::Discard;

	QMessageBox msgBox;
	msgBox.setText(Editor::Messages::ModModified);
	msgBox.setInformativeText(Editor::Messages::AskIfSaveChanges);
	msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Save);

	return msgBox.exec();
}

void MainWindow::onNewActivated()
{
	switch (checkForUnsavedChanges()) {
		case QMessageBox::Save:
			onSaveActivated();
			return;
		case QMessageBox::Discard:
			mod_->reset();
			break;
		default :
			return;
	}

	startEditing();
}

void MainWindow::onLoadActivated()
{
	switch (checkForUnsavedChanges()) {
		case QMessageBox::Save:
			onSaveActivated();
			return;
		case QMessageBox::Discard:
			break;
		default :
			return;
	}

	QString path = QFileDialog::getOpenFileName(this, Editor::Titles::OpenFileDialog,
	                                            Path::ModsDir, Strings::ModFiles);
	if (mod_->load(path))
		startEditing();

	currentFilePath_ = path;
}

void MainWindow::onSaveActivated()
{
	if (currentFilePath_.isEmpty())
		onSaveAsActivated();

	if (mod_->save(currentFilePath_))
		emit modelSaved();
}

void MainWindow::onSaveAsActivated()
{
	QString path = QFileDialog::getSaveFileName(this, Editor::Titles::SaveFileDialog,
	                                            Path::ModsDir, Strings::ModFiles);

	if (mod_->save(path)){
		emit modelSaved();
		currentFilePath_ = path;
	}
}

void MainWindow::onQuitActivated()
{
	close();
}
