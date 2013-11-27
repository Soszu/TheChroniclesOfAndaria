#ifndef BOARDAREA_H
#define BOARDAREA_H

#include <QtWidgets>

#include "Core/Containers/Field.h"
#include "Core/Containers/Player.h"
#include "Core/Board.h"
#include "Core/Game.h"
#include "Gui/Elements/PlayerMarker.h"
#include "Gui/Elements/Tile.h"
#include "Gui/MainWindow.h"

class Board;
class Tile;
class PlayerMarker;
class MainWindow;

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

protected:
	//TODO CFiend dlaczego to jest wykomentowane?
//	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
	QRectF calcBoardAreaRect();
	QPointF calcPlayerMarkerCenter(int index);
	void changeSize(int d);

	QStatusBar *statusBar_;

	qreal tileSide_;
	Board *const board_;
	int rowCount_;
	int columnCount_;

	QList <Field *> *fields_; //TODO CFiend dlaczego to jest QList *?
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
