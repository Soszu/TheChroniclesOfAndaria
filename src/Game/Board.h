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

#ifndef BOARD_H
#define BOARD_H

#include "Core/Containers/Field.h"
#include "Core/Containers/Player.h"
#include "Game/Game.h"
#include "Game/GameCycle.h"
#include "Game/DataKeeper.h"

using namespace std;

class GameCycle;
class GameMaster;
class BoardArea;

class Board {
public:
	Board(GameCycle *gameCycle);

	void movePlayer(int index);
	void tileClicked(FieldId field);
	void findReachableFields(Player *player);
	void updateReachableFields();
	void removePlayer(int index);
	const Field * showField(FieldId field);
	QString playerDescription();
	bool isMoveInProgress();
	QList <FieldId> showReachableFields();
	void moveAI(FieldId field);
	void showTile(FieldId field);
	void disablePlayerMove();
	static int fieldIdToIndex(FieldId field);
	static FieldId indexToFieldId(int index);
	void beginGame();

	GameCycle * gameCycle();
	const QList <Player *> & players();
	const Player * player(int i);

	const QList <const Field *> & fields();
	const Field * field(FieldId id);
	const quint8 boardWidth();
	const quint8 boardHeigth();

private:
	QList <FieldId> findPath(FieldId field);
	QList <FieldId> neighboringFields(FieldId field);

	GameCycle *gameCycle_;

	const QList <const Field *> *fields_;
	const quint8 boardWidth_;
	const quint8 boardHeigth_;

	QList <FieldId> reachable_;
	QMap <int, FieldId> previous_; //<indeks pola obecnego, pole z którego można na nie przyjść>

signals:
	void drawBoard();
};

#endif
