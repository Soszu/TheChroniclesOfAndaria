/*
Copyright (C) 2013-2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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

#include "Game/Client/MainWindow.hpp"
#include <QtCore>
#include <QtGui>


MainWindow::MainWindow(GameCycleClt *gameCycleClt, QWidget *parent) :
	QMainWindow(parent),
	gameCycleClt_(gameCycleClt)
//  actionPanel_(gameCycle->gameMaster()),
//             boardArea_(gameCycle->board())
{/*
	QWidget *centralWidget = new QWidget();
	this->setCentralWidget(centralWidget);
	QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
	QVBoxLayout *sideLayout = new QVBoxLayout();
	graphicsView = new QGraphicsView;
	QFrame *frame = new QFrame();
	frame->setLayout(playerWindow_.mainLayout());

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

	connect(gameCycle, &GameCycle::dateChanged, this, &MainWindow::changeDate);
	connect(gameCycle, &GameCycle::playerChanged, &playerWindow_, &PlayerWindow::displayPlayer);
	connect(gameCycle, &GameCycle::statsChanged, &playerWindow_, &PlayerWindow::update);
*/}
/*
MainWindow::~MainWindow()
{
	delete menuGame;
	delete menuView;
	delete menuHelp;
}

void MainWindow::changeDate(int day, int week)
{
	dateDisplay->setText(QString::fromUtf8("Dzień ") + QString::number(day) + QString::fromUtf8(", Tydzień ") + QString::number(week));
}

void MainWindow::displayRules()
{
	rulesWindow_ = new RulesWindow();
	rulesWindow_->setWindowModality(Qt::ApplicationModal);
	rulesWindow_->setAttribute(Qt::WA_DeleteOnClose);
	rulesWindow_->show();
}*/
