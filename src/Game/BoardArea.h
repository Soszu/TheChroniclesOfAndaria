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

#ifndef BOARDAREA_H
#define BOARDAREA_H

#include <QtWidgets>

#include "Core/Containers/Field.h"
#include "Core/Containers/Player.h"
#include "Core/Board.h"
#include "Core/Game.h"
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
	explicit BoardArea(Board *board);
	~BoardArea();

	void setStatusBar(QStatusBar *statusBar);
	void displayMessage(const QString &message);
	void drawBoard(QList <Field *> *fields, int columnCount, int rowCount, QList <QPair <QColor, FieldId> > *playerPositions);

	void tileClicked(FieldId id);
	void executeMove(const QList <FieldId> &path, int playerNumber);
	void removePlayerMarker(int index);
	void highlightFields(const QList <FieldId> &fields);
	void showTile(int index);
	bool animationInProgress();

	static QPointF calcCenter(FieldId id, qreal side);
	static qreal calcHeight(qreal side);

public slots:
	void decreaseSize();
	void increaseSize();
	void resetSize();

private:
	QRectF calcBoardAreaRect();
	QPointF calcPlayerMarkerCenter(int index);
	void changeSize(int d);

	QStatusBar *statusBar_;

	qreal tileSide_;
	Board *const board_;
	int rowCount_;
	int columnCount_;

	QList <Tile *> tiles_;
	QList <PlayerMarker *> playerMarkers_;
	QList <int> highlightedFields_;
	QList <QPair <QColor, FieldId> > *playerPositions_;

	Tile *selectedTile;
	QTimeLine *ticTac;
	QTimeLine *highlightTimeLine;
	QList <FieldId> pathToAnimate;
	int animatedMarkerIndex;
	QPointF animationStart;
	QPointF animationFinish;

private slots:
	void animationNextStep();
	void animationStep(int phase);
	void clearSelection();
};

#endif
