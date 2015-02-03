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

#include "Core/Containers/Board.hpp"
#include "Editor/Strings.hpp"

BoardEditor::BoardEditor(Board *board) :
	board_(board)
{
	initMap();
	initTools();
	initLayout();
}

void BoardEditor::initMap()
{
	map_ = new Map(board_);
	map_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void BoardEditor::initTools()
{
	initBoardSizeTools();
	terrainsTools_ = new QWidget;
	rulingTools_ = new QWidget;
	initialPositionsTools_ = new QWidget;

	tools_ = new QToolBox;
	tools_->addItem(boardSizeTools_,        Editor::Labels::BoardTools::BoardSize);
	tools_->addItem(terrainsTools_,         Editor::Labels::BoardTools::Terrains);
	tools_->addItem(rulingTools_,           Editor::Labels::BoardTools::Ruling);
	tools_->addItem(initialPositionsTools_, Editor::Labels::BoardTools::InitialPositions);
}

void BoardEditor::initBoardSizeTools()
{
	boardSizeTools_ = new QWidget;
	QFormLayout *layout = new QFormLayout;
	boardSizeTools_->setLayout(layout);

	QSpinBox *boardColumns = new QSpinBox;
	boardColumns->setValue(board_->columnCount());
	boardColumns->setMinimum(1);
	connect(boardColumns, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
	        this, &BoardEditor::changeBoardWidth);

	QSpinBox *boardRows = new QSpinBox;
	boardRows->setValue(board_->rowCount());
	boardRows->setMinimum(1);
	connect(boardRows, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
	        this, &BoardEditor::changeBoardHeight);

	layout->addRow(Editor::Labels::BoardTools::BoardColumns, boardColumns);
	layout->addRow(Editor::Labels::BoardTools::BoardRows,    boardRows);
}

void BoardEditor::initLayout()
{
	setLayout(new QHBoxLayout);
	layout()->addWidget(map_);
	layout()->addWidget(tools_);
}

void BoardEditor::changeBoardWidth(int val)
{
	board_->setSize(QSize(val, board_->size().height()));
}

void BoardEditor::changeBoardHeight(int val)
{
	board_->setSize(QSize(board_->size().width(), val));
}
