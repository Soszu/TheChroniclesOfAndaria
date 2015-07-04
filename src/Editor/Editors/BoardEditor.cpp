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
#include "Core/Widgets/MapView.hpp"
#include "Core/Widgets/Map.hpp"

#include "Editor/CustomWidgets/Tools/BoardSizeTool.hpp"
#include "Editor/CustomWidgets/Tools/TerrainsTool.hpp"
#include "Editor/CustomWidgets/Tools/RulingTool.hpp"
#include "Editor/CustomWidgets/Tools/InitialPositionsTool.hpp"

BoardEditor::BoardEditor(BoardModel * board) :
	board_(board),
	activeTool_(nullptr)
{
	initLayout();
}

QWidget * BoardEditor::createMap()
{
	Map * map = new Map(board_);
	connect(board_, &BoardModel::modelChanged, map, &Map::repaint);

	mapView_ = new MapView;
	mapView_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	mapView_->setScene(map);

	return mapView_;
}

QWidget * BoardEditor::createTools()
{
	boardSizeTool_ = new BoardSizeTool(board_);
	terrainsTool_ = new TerrainsTool(board_);
	rulingTool_ = new RulingTool(board_);
	initialPositionsTool_ = new InitialPositionsTool(board_);

	QToolBox * tools = new QToolBox;
	tools->addItem(boardSizeTool_,        tr("Board size"));
	tools->addItem(terrainsTool_,         tr("Terrains"));
	tools->addItem(rulingTool_,           tr("Ruling"));
	tools->addItem(initialPositionsTool_,  tr("Initial Positions"));

	return tools;
}

void BoardEditor::initLayout()
{
	QHBoxLayout * mainLayout = new QHBoxLayout;
	setLayout(mainLayout);

	mainLayout->addWidget(createMap(), 1);
	mainLayout->addWidget(createTools(), 0);
}
