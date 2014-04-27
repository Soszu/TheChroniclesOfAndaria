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

#ifndef BOARD_H
#define BOARD_H

#include "Core/Containers/Field.h"
#include "Core/Containers/Player.h"
#include "Core/Game.h"
#include "Core/GameCycle.h"
#include "Core/GameMaster.h"
#include "Game/BoardArea.h" //TODO CFiend WTF dlaczego logika wciaga grafike?

using namespace std;

class GameCycle;
class GameMaster;
class BoardArea;
class BoardParser;

class Board {
	friend class BoardParser;
public:
	Board(GameCycle *gameCycle);
	~Board();
	void setBoardArea(BoardArea *boardArea);
	void setGameMaster(GameMaster *gameMaster);
	void setPlayers(QList <Player *> *players);
	const QList <int> & cities();
	void movePlayer(int index);
	void tileClicked(FieldId field);
	void findReachableFields(Player *player);
	void updateReachableFields();
	void removePlayer(int index);
	Field * showField(FieldId field);
	QString playerDescription(int index);
	bool isMoveInProgress();
	QList <FieldId> showReachableFields();
	void moveAI(FieldId field);
	void showTile(FieldId field);
	void disablePlayerMove();
	int fieldIdToIndex(FieldId field);
	FieldId indexToFieldId(int index);
	void beginGame();

private:
	QList <FieldId> findPath(FieldId field);
	QList <QPair <QColor, FieldId> > * collectPlayerPositions();
	QList <FieldId> neighboringFields(FieldId field);

	BoardArea *boardArea_;
	GameCycle *gameCycle_;
	GameMaster *gameMaster_;

	QList <int> cities_;
	QList <QPair <QColor, FieldId> > *playerPositions_;
	QList <Player *> *players_;
	QList <Field *> *fields_;
	QList <FieldId> reachable_;
	QMap <int, FieldId> previous_; //<indeks pola obecnego, pole z którego można na nie przyjść>

	quint8 boardHeight_;
	quint8 boardWidth_;
	//TODO CFiend te 3 rzeczy ponizej nie powinny byc np. w GameMaster albo GameCycle?
	//NOTE should be solve during reducing layers dependencies
	int currentIndex_;
	Player *currentPlayer_;
	bool playerHasMoved_;
};

#endif
