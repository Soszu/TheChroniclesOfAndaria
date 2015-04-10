/*
Copyright (C) 2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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
#include "BoardEditor.hpp"

#include "Core/Containers/Models/BoardModel.hpp"
#include "Core/Widgets/Map.hpp"

BoardEditor::BoardEditor(BoardModel * board) :
	board_(board)
{
	initLayout();
}

QWidget * BoardEditor::createMap()
{
	map_ = new Map(board_);
	connect(board_, &BoardModel::modelChanged, map_, &Map::repaint);

	QGraphicsView * mapView = new QGraphicsView;
	mapView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	mapView->setScene(map_);

	return mapView;
}

QWidget * BoardEditor::createTools()
{
	initBoardSizeTools();
	terrainsTools_ = new QWidget;
	rulingTools_ = new QWidget;
	initialPositionsTools_ = new QWidget;

	QToolBox * tools = new QToolBox;
	tools->addItem(boardSizeTools_,        tr("Board size"));
	tools->addItem(terrainsTools_,         tr("Terrains"));
	tools->addItem(rulingTools_,           tr("Ruling"));
	tools->addItem(initialPositionsTools_, tr("Initial Positions"));

	return tools;
}

void BoardEditor::initBoardSizeTools()
{
	boardSizeTools_ = new QWidget;
	QFormLayout * layout = new QFormLayout;
	boardSizeTools_->setLayout(layout);

	boardColumns_ = new QSpinBox;
	boardColumns_->setValue(board_->columnCount());
	boardColumns_->setMinimum(1);
	connect(boardColumns_, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
	        this, &BoardEditor::changeBoardWidth);

	boardRows_ = new QSpinBox;
	boardRows_->setValue(board_->rowCount());
	boardRows_->setMinimum(1);
	connect(boardRows_, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
	        this, &BoardEditor::changeBoardHeight);

	layout->addRow(tr("Board columns"), boardColumns_);
	layout->addRow(tr("Board rows"),    boardRows_);

	connect(board_, &BoardModel::modelChanged, this, &BoardEditor::updateBoardSizeTools);
}

void BoardEditor::initLayout()
{
	QHBoxLayout * mainLayout = new QHBoxLayout;
	setLayout(mainLayout);

	mainLayout->addWidget(createMap(), 1);
	mainLayout->addWidget(createTools(), 0);
}

void BoardEditor::updateBoardSizeTools()
{
	boardRows_->setValue(board_->rowCount());
	boardColumns_->setValue(board_->columnCount());
}

void BoardEditor::changeBoardWidth(int val)
{
	board_->setSize(QSize(val, board_->size().height()));
	emit boardChanged();
}

void BoardEditor::changeBoardHeight(int val)
{
	board_->setSize(QSize(board_->size().width(), val));
	emit boardChanged();
}
