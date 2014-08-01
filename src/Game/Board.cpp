/*
Copyright (C) 2013-2014 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
Thanks to 2013 Łukasz Piesiewicz <wookesh [at] gmail [dot] com>
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

#include "Game/Board.h"

Board::Board(GameCycle *gameCycle)
           : gameCycle_(gameCycle),
             fields_(&DataKeeper::instance().fields()),
             boardWidth_(DataKeeper::instance().boardWidth()),
             boardHeigth_(DataKeeper::instance().boardHeight())/*,
             playerPositions_(new QList <QPair <QColor, FieldId> >)*/
{}

void Board::movePlayer(int index)
{
	this->currentIndex_ = index;
	this->currentPlayer_ = players_->at(index);
	playerHasMoved_ = false;
	findReachableFields(currentPlayer_);
	boardArea_->highlightFields(showReachableFields());
}

void Board::tileClicked(FieldId field)
{
	if (!playerHasMoved_ && previous_.contains(fieldIdToIndex(field))) {
		currentPlayer_->setPosition(field);
		boardArea_->executeMove(findPath(field), currentIndex_);
		gameMaster_->moveExecuted();
		playerHasMoved_ = true;
	}
}

void Board::findReachableFields(Player *player)
{
	QQueue <QPair <int, FieldId> > queue;
	QMap <int, int> minDist; //<field index, cost of shortest path>

	previous_.clear();
	reachable_.clear();
	if (playerHasMoved_)
		return;

	queue.enqueue(qMakePair(0, player->position()));

	while (!queue.empty()) {
		QPair <int, FieldId> current = queue.dequeue();
		QList <FieldId> nearest = neighboringFields(current.second);

		for (FieldId field : nearest) {
			int index = fieldIdToIndex(field);
			int distance = current.first + DataKeeper::instance().fields()[index]->moveCost();
			if (distance > player->movePoints())
				continue;
			if (minDist.contains(index)) {
				if (minDist[index] > distance) {
					minDist[index] = distance;
					queue.enqueue(qMakePair(distance, indexToFieldId(index)));
					previous_.remove(index);
					previous_.insert(index, current.second);
				}
				continue;
			} else {
				minDist.insert(index, distance);
				queue.enqueue(qMakePair(distance, indexToFieldId(index)));
				previous_.insert(index, current.second);
			}
		}
	}

	previous_.remove(fieldIdToIndex(player->position()));
	QList <int> reachableIndexes = previous_.keys();
	for (int i : reachableIndexes)
		reachable_.push_back(indexToFieldId(i));
}

void Board::updateReachableFields()
{
	findReachableFields(currentPlayer_);
	boardArea_->highlightFields(showReachableFields());
}

void Board::removePlayer(int index)
{
	boardArea_->removePlayerMarker(index);
}

const Field *Board::showField(FieldId field)
{
	return DataKeeper::instance().fields()[fieldIdToIndex(field)];
}

QString Board::playerDescription()
{
	QString description;
	Player *player = gameCycle_->currentPlayer();
	description += player->name() + description + "\n";
	description += Player::raceString()[player->playerRace()] + " " + Player::classString()[player->playerClass()] + "\n";
	description += QObject::tr("poziom ") + QString::number(player->level()) + "\n";
	description += QObject::tr("zdrowie ") + QString::number(player->healthCurrent()) + "/" + QString::number(player->healthMax());
	return description;
}

bool Board::isMoveInProgress()
{
	return boardArea_->animationInProgress();
}

QList <FieldId> Board::showReachableFields()
{
	return reachable_;
}

QList <FieldId> Board::findPath(FieldId field)
{
	QList <FieldId> path;
	FieldId current = field;
	path.push_back(current);

	while (previous_.contains(fieldIdToIndex(current))) {
		current = previous_[fieldIdToIndex(current)];
		path.push_back(current);
	}
	path.pop_back(); //erase the field on which the player marker currently lies

	return path;
}

void Board::moveAI(FieldId field)
{
	tileClicked(field);
}

void Board::showTile(FieldId field)
{
	boardArea_->showTile(fieldIdToIndex(field));
}

void Board::disablePlayerMove()
{
	playerHasMoved_ = true;

	findReachableFields(currentPlayer_);
	boardArea_->highlightFields(showReachableFields());
}

int Board::fieldIdToIndex(FieldId field)
{
	return field.y() * DataKeeper::instance().boardWidth() + field.x();
}

FieldId Board::indexToFieldId(int index)
{
	FieldId tmp;
	tmp.rx() = index % DataKeeper::instance().boardWidth();
	tmp.ry() = index / DataKeeper::instance().boardWidth();

	return tmp;
}

void Board::beginGame()
{
	emit drawBoard();
}

GameCycle *Board::gameCycle()
{
	return gameCycle_;
}

const QList<Player *> &Board::players()
{
	return gameCycle_->players();
}

const Player *Board::player(int i)
{
	return gameCycle_->players()[i];
}

const QList<const Field *> & Board::fields()
{
	return fields_;
}

const Field *Board::field(FieldId id)
{
	return fields[fieldIdToIndex(id)];
}

const quint8 Board::boardWidth()
{
	return boardWidth_;
}

const quint8 Board::boardHeigth()
{
	return boardHeigth_;
}

QList <FieldId> Board::neighboringFields(FieldId field)
{
	QList <FieldId> result;
	FieldId tmp = field;
	if (field.x() > 0) {
		tmp.rx() = field.x() - 1;
		result.push_back(tmp);
	}
	if (field.x() < DataKeeper::instance().boardWidth() - 1) {
		tmp.rx() = field.x() + 1;
		result.push_back(tmp);
	}
	tmp.rx() = field.x();

	if (field.y() < DataKeeper::instance().boardHeight() - 1) {
		tmp.ry() = field.y() + 1;
		result.push_back(tmp);

		if (field.y() % 2 == 1) {
			if (field.x() < DataKeeper::instance().boardWidth() - 1) {
				tmp.rx() = field.x() + 1;
				result.push_back(tmp);
			}
		} else if (field.x() > 0) {
			tmp.rx() = field.x() - 1;
			result.push_back(tmp);
		}
	}
	tmp.rx() = field.x();
	if (field.y() > 0) {
		tmp.ry() = field.y() - 1;
		result.push_back(tmp);
		if (field.y() % 2 == 1) {
			if (field.x() < DataKeeper::instance().boardWidth() - 1) {
				tmp.rx() = field.x() + 1;
				result.push_back(tmp);
			}
		} else if (field.x() > 0) {
			tmp.rx() = field.x() - 1;
			result.push_back(tmp);
		}
	}

	return result;
}
