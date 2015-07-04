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
#include "Editor/CustomWidgets/Tools/BoardSizeTool.hpp"

#include "Core/Containers/Models/BoardModel.hpp"
#include "Core/Widgets/Tile.hpp"

BoardSizeTool::BoardSizeTool(BoardModel * board) :
	Tool(board)
{
	initLayout();
}

void BoardSizeTool::initLayout()
{
	QFormLayout * layout = new QFormLayout;
	setLayout(layout);

	boardColumns_ = new QSpinBox;
	boardColumns_->setValue(board_->columnCount());
	boardColumns_->setMinimum(1);
	connect(boardColumns_, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
	        this, &BoardSizeTool::changeBoardWidth);

	boardRows_ = new QSpinBox;
	boardRows_->setValue(board_->rowCount());
	boardRows_->setMinimum(1);
	connect(boardRows_, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
	        this, &BoardSizeTool::changeBoardHeight);

	layout->addRow(tr("Board columns"), boardColumns_);
	layout->addRow(tr("Board rows"),    boardRows_);

	connect(board_, &BoardModel::modelChanged, this, &BoardSizeTool::updateBoardSizeTools);
}

void BoardSizeTool::updateBoardSizeTools()
{
	boardRows_->setValue(board_->rowCount());
	boardColumns_->setValue(board_->columnCount());
}

void BoardSizeTool::changeBoardWidth(int val)
{
	board_->setSize(QSize(val, board_->size().height()));
}

void BoardSizeTool::changeBoardHeight(int val)
{
	board_->setSize(QSize(board_->size().width(), val));
}
