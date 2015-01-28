#pragma once

#include <QtWidgets>

#include "Core/Widgets/Map.hpp"

class Board;

class BoardEditor : public QWidget {

public:
	BoardEditor(Board *board);

private:
	void initMap();
	void initTools();
	void initBoardSizeTools();
	void initLayout();

	Board *board_;
	Map *map_;
	QToolBox *tools_;
	QWidget *boardSizeTools_;
	QWidget *terrainsTools_;
	QWidget *rulingTools_;
	QWidget *initialPositionsTools_;

private slots:
	void changeBoardWidth(int val);
	void changeBoardHeight(int val);
};
