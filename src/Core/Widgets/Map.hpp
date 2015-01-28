#pragma once

#include <QtWidgets>

class Board;

class Map : public QGraphicsView {

public:
    Map(Board* board);

private:
	Board *board_;
};
