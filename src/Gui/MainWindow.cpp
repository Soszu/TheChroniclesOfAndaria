/*
Copyright (C) 2013 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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

#include "Gui/MainWindow.h"
#include <QtCore>
#include <QtGui>


MainWindow::MainWindow(GameMaster *gameMaster, Board *board, QWidget *parent)
	: QMainWindow(parent)
{
	QWidget *centralWidget = new QWidget();
	this->setCentralWidget(centralWidget);
	QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
	QVBoxLayout *sideLayout = new QVBoxLayout();
	graphicsView = new QGraphicsView;
	QFrame *frame = new QFrame();
	actionPanel_ = new ActionPanel(gameMaster);

	menuGame = new QMenu("Gra");
	menuView = new QMenu("Widok");
	menuHelp = new QMenu("Pomoc");

	menuBar()->addMenu(menuGame);
	menuBar()->addMenu(menuView);
	menuBar()->addMenu(menuHelp);

	mainLayout->addWidget(graphicsView);
	mainLayout->addLayout(sideLayout);
	sideLayout->addWidget(frame);
	sideLayout->addWidget(actionPanel_);

	playerWindow_ = new PlayerWindow(frame);
	playerWindow_->setGameMaster(gameMaster);
	
	boardArea_ = new BoardArea(board);
	graphicsView->setScene(boardArea_);

	dateDisplay = new QLabel(statusBar());
	statusBar()->addPermanentWidget(dateDisplay);
	boardArea_->setStatusBar(statusBar());

	menuGame->addAction("Nowa gra");
	menuGame->addSeparator();
	menuGame->addAction(QString::fromUtf8("Wczytaj grę"));
	menuGame->addAction(QString::fromUtf8("Zapisz grę"));
	menuGame->addSeparator();
	menuGame->addAction(QString::fromUtf8("Zakończ"), this, SLOT(close()));

	menuView->addAction(QString::fromUtf8("Oddal"), boardArea_, SLOT(increaseSize()), Qt::CTRL + Qt::Key_Minus);
	menuView->addAction(QString::fromUtf8("Przybliż"), boardArea_, SLOT(decreaseSize()), Qt::CTRL + Qt::Key_Plus);
	menuView->addAction(QString::fromUtf8("Przywróć rozmiar"), boardArea_, SLOT(resetSize()), Qt::CTRL + Qt::Key_Equal);

	menuHelp->addAction("Pomoc", this, SLOT(displayRules()), Qt::Key_F1);
	menuHelp->addAction("O Autorze");
}

MainWindow::~MainWindow()
{
	delete playerWindow_;
	delete boardArea_;
	delete actionPanel_;

	delete menuGame;
	delete menuView;
	delete menuHelp;
}

ActionPanel * MainWindow::actionPanel()
{
	return actionPanel_;
}

PlayerWindow * MainWindow::playerWindow()
{
	return playerWindow_;
}

BoardArea * MainWindow::boardArea()
{
	return boardArea_;
}

/**
 * @brief MainWindow::zmienDate		Wyświetla wskazaną datę na pasku statusu
 * @param dzien
 * @param tydzien
 */
void MainWindow::changeDate(int day, int week)
{
	dateDisplay->setText(QString::fromUtf8("Dzień ") + QString::number(day) + QString::fromUtf8(", Tydzień ") + QString::number(week));
}

/**
 * @brief MainWindow::wyswietlZasady	Wyświetla okno zasad i blokuje pozostałe Windows
 */
void MainWindow::displayRules()
{
	rulesWindow_ = new RulesWindow();
	rulesWindow_->setWindowModality(Qt::ApplicationModal);
	rulesWindow_->setAttribute(Qt::WA_DeleteOnClose);
	rulesWindow_->show();
}
