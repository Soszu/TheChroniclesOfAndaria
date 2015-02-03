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

#include "Game/Board.hpp"

Board::Board(GameCycle *gameCycle) :
	gameCycle_(gameCycle),
	fields_(&DataKeeper::instance().fields()),
	boardWidth_(DataKeeper::instance().boardWidth()),
	boardHeigth_(DataKeeper::instance().boardHeight())/*,
	playerPositions_(new QList <QPair <QColor, Coordinates> >)*/
{}

void Board::movePlayer(int index)
{
	this->currentIndex_ = index;
	this->currentPlayer_ = players_->at(index);
	playerHasMoved_ = false;
	findReachableFields(currentPlayer_);
	boardArea_->highlightFields(showReachableFields());
}

void Board::tileClicked(Coordinates field)
{
	if (!playerHasMoved_ && previous_.contains(coordinatesToIndex(field))) {
		currentPlayer_->setPosition(field);
		boardArea_->executeMove(findPath(field), currentIndex_);
		gameMaster_->moveExecuted();
		playerHasMoved_ = true;
	}
}

void Board::findReachableFields(Player *player)
{
	QQueue <QPair <int, Coordinates> > queue;
	QMap <int, int> minDist; //<field index, cost of shortest path>

	previous_.clear();
	reachable_.clear();
	if (playerHasMoved_)
		return;

	queue.enqueue(qMakePair(0, player->position()));

	while (!queue.empty()) {
		QPair <int, Coordinates> current = queue.dequeue();
		QList <Coordinates> nearest = neighboringFields(current.second);

		for (Coordinates field : nearest) {
			int index = coordinatesToIndex(field);
			int distance = current.first + DataKeeper::instance().fields()[index]->moveCost();
			if (distance > player->movePoints())
				continue;
			if (minDist.contains(index)) {
				if (minDist[index] > distance) {
					minDist[index] = distance;
					queue.enqueue(qMakePair(distance, indexToCoordinates(index)));
					previous_.remove(index);
					previous_.insert(index, current.second);
				}
				continue;
			} else {
				minDist.insert(index, distance);
				queue.enqueue(qMakePair(distance, indexToCoordinates(index)));
				previous_.insert(index, current.second);
			}
		}
	}

	previous_.remove(coordinatesToIndex(player->position()));
	QList <int> reachableIndexes = previous_.keys();
	for (int i : reachableIndexes)
		reachable_.push_back(indexToCoordinates(i));
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

const Field *Board::showField(Coordinates field)
{
	return DataKeeper::instance().fields()[coordinatesToIndex(field)];
}

QString Board::playerDescription()
{
	QString description;
	Player *player = gameCycle_->currentPlayer();
	description += player->name() + description + "\n";
	description += Player::raceString()[player->playerRace()] + " " + Player::classString()[player->playerClass()] + "\n";
	description += QObject::tr("poziom ") + QString::number(player->level()) + "\n";
	description += QObject::tr("zdrowie ") + QString::number(player->currentHealth()) + "/" + QString::number(player->maxHealth());
	return description;
}

bool Board::isMoveInProgress()
{
	return boardArea_->animationInProgress();
}

QList <Coordinates> Board::showReachableFields()
{
	return reachable_;
}

QList <Coordinates> Board::findPath(Coordinates field)
{
	QList <Coordinates> path;
	Coordinates current = field;
	path.push_back(current);

	while (previous_.contains(coordinatesToIndex(current))) {
		current = previous_[coordinatesToIndex(current)];
		path.push_back(current);
	}
	path.pop_back(); //erase the field on which the player marker currently lies

	return path;
}

void Board::moveAI(Coordinates field)
{
	tileClicked(field);
}

void Board::showTile(Coordinates field)
{
	boardArea_->showTile(coordinatesToIndex(field));
}

void Board::disablePlayerMove()
{
	playerHasMoved_ = true;

	findReachableFields(currentPlayer_);
	boardArea_->highlightFields(showReachableFields());
}

int Board::coordinatesToIndex(Coordinates field)
{
	return field.y() * DataKeeper::instance().boardWidth() + field.x();
}

Coordinates Board::indexToCoordinates(int index)
{
	Coordinates tmp;
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

const Field *Board::field(Coordinates id)
{
	return fields[coordinatesToIndex(id)];
}

const quint8 Board::boardWidth()
{
	return boardWidth_;
}

const quint8 Board::boardHeigth()
{
	return boardHeigth_;
}

QList <Coordinates> Board::neighboringFields(Coordinates field)
{
	QList <Coordinates> result;
	Coordinates tmp = field;
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
