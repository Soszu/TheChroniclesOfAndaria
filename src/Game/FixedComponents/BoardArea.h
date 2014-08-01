/*
Copyright (C) 2013-2014 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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

#ifndef BOARDAREA_H
#define BOARDAREA_H

#include <QtWidgets>

#include "Core/Containers/Field.h"
#include "Core/Containers/Player.h"
#include "Game/Board.h"
#include "Game/Game.h"
#include "Game/Elements/PlayerMarker.h"
#include "Game/Elements/Tile.h"
#include "Game/MainWindow.h"

class Board;
class Tile;
class PlayerMarker;
class MainWindow;

static const int NUMBER_OF_ENVISAGED_MODIFICATORS = 9;
static const QPointF POSITION_MODIFICATORS[]= {
	{0,0}, {0, -1}, {-1, 1}, {1, 1}, {-1, -1}, {1, -1}, {0, 1}, {-1, 0}, {1, 0} };

class BoardArea : public QGraphicsScene {
	Q_OBJECT
public:
	explicit BoardArea(Board *board, QWidget *parent = nullptr);
	~BoardArea();

	void setStatusBar(QStatusBar *statusBar);
	void drawBoard();

	void executeMove(const QList <FieldId> &path);
	void removePlayerMarker(int index);
	void highlightFields(const QList <FieldId> &fieldsIDs);
	void showTile(int index);
	bool animationInProgress();

	static QPointF calcCenter(const FieldId id, qreal side);
	static qreal calcHeight(qreal side);

public slots:
	void displayDescription(FieldId id);
	void handleClicked(FieldId id);
	void decreaseSize();
	void increaseSize();
	void resetSize();

private:
	QRectF calcBoardAreaRect();
	QPointF calcPlayerMarkerCenter(int index);
	void changeSize(int d);

	Board * board_;
	QStatusBar *statusBar_;

	qreal tileSide_;

	QList <Tile *> tiles_;
	QList <PlayerMarker *> playerMarkers_;

	QList <int> highlightedFields_;

	Tile *selectedTile;
	QTimeLine *highlightTimeLine;

	QTimeLine *ticTac;
	QList <FieldId> pathToAnimate;
	QPointF animationStart;
	QPointF animationFinish;

private slots:
	void animationNextStep();
	void animationStep(int phase);
	void clearSelection();
};

#endif
