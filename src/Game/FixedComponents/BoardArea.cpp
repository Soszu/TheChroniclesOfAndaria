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

#include "Game/FixedComponents/BoardArea.h"

BoardArea::BoardArea(Board *board, QWidget *parent)
                   : QGraphicsScene(parent),
                     tileSide_(InitialTileSize),
                     board_(board),
                     selectedTile(nullptr),
                     playerMarkers_(nullptr),
                     tiles_(nullptr)
{
	connect(board_, &Board::drawBoard, this, &BoardArea::drawBoard);

	ticTac = new QTimeLine(CZAS_TRWANIA_JEDNEGO_PRZEJSCIA, this);
	ticTac->setFrameRange(0, 100);
	connect(ticTac, SIGNAL(frameChanged(int)), this, SLOT(animationStep(int)));
	connect(ticTac, SIGNAL(finished()), this, SLOT(animationNextStep()));

	highlightTimeLine = new QTimeLine(CZAS_TRWANIA_PODSWIETLENIA, this);
	connect(highlightTimeLine, SIGNAL(finished()), this, SLOT(clearSelection()));
}

BoardArea::~BoardArea()
{
	qDeleteAll(playerMarkers_);
	qDeleteAll(tiles_);
}

void BoardArea::setStatusBar(QStatusBar *statusBar)
{
	this->statusBar_ = statusBar;
}

void BoardArea::displayDescription(FieldId id)
{
	QString message = QString(board_->field(id)->name() + ";\t koszt ruchu: " + QString::number(board_->field(id)->moveCost()));
	statusBar_->showMessage(message, DLUGOSC_TRWANIA_KOMUNIKATU);
}

void BoardArea::drawBoard()
{
	setBackgroundBrush(QBrush(Qt::black));
	setSceneRect(calcBoardAreaRect());

	for (int i = 0; i < board_->fields()->size(); ++i) {
		tiles_.append(new Tile(fields[i], tileSide_, this));
		addItem(tiles_[i]);
		connect(&tile[i], &Tile::clicked, this, &BoardArea::handleClicked);
		connect(&tile[i], &Tile::mouseEntered, this, &BoardArea::displayDescription);
	}

	for (int i = 0; i < board_->players().count(); ++i) {
		playerMarkers_.append(new PlayerMarker(board_->player(i)->color(),
		                                       calcPlayerMarkerCenter(i),
		                                       tileSide_ / 2));
		addItem(playerMarkers_[i]);
	}
}

void BoardArea::handleClicked(FieldId id)
{
	board_->tileClicked(id);
}

void BoardArea::executeMove(const QList <FieldId> &path)
{
	pathToAnimate = path;

	while (!highlightedFields_.isEmpty()) {
		tiles_[highlightedFields_.back()]->setHighlighted(false);
		highlightedFields_.pop_back();
	}

	animationNextStep();
}

void BoardArea::removePlayerMarker(int index)
{
	playerMarkers_[index]->setVisible(false);
}

void BoardArea::highlightFields(const QList <FieldId> &fieldsIDs)
{
	while (!highlightedFields_.isEmpty()) {
		tiles_[highlightedFields_.back()]->setHighlighted(false);
		highlightedFields_.pop_back();
	}

	for (auto id : fieldsIDs) {
		int idx = board_->fieldIdToIndex(id);
		tiles_[idx]->setHighlighted(true);
		highlightedFields_.push_back(idx);
	}
}

void BoardArea::showTile(int index)
{
	if (highlightTimeLine->state() == QTimeLine::Running) {
		clearSelection();
		highlightTimeLine->stop();
	}
	selectedTile = tiles_[index];
	selectedTile->select();
	highlightTimeLine->start();
}

bool BoardArea::animationInProgress()
{
	return (ticTac->state() == QTimeLine::Running || highlightTimeLine->state() == QTimeLine::Running);
}

QRectF BoardArea::calcBoardAreaRect()
{
	qreal sceneWidth = board_->boardWidth() * calcHeight(tileSide_) * 2;
	if (board_->boardHeigth() > 1)
		sceneWidth += calcHeight(tileSide_);
	qreal sceneHeight = 2 * tileSide_ + (board_->boardHeigth() - 1) * 1.5 * tileSide_;
	return QRectF(0, 0, sceneWidth, sceneHeight);
}

QPointF BoardArea::calcPlayerMarkerCenter(int index)
{
	const FieldId field = board_->player(index)->position();
	QPointF center = calcCenter(field, tileSide_);
	if (index >= NUMBER_OF_ENVISAGED_MODIFICATORS)
		return center;

	int markersOnSameField = 0;
	for (int i = 0; i < index; ++i)
		if (board_->player(i)->position() == field)
			++markersOnSameField;

	QPointF shift(POSITION_MODIFICATORS[markersOnSameField] * tileSide_ / 4.0);
	return center + shift;
}

QPointF BoardArea::calcCenter(const FieldId id, qreal side)
{
	if (side < 0 || id.x() < 0 || id.y() < 0)
		return QPointF(-1, -1);
	qreal height = calcHeight(side);
	QPointF center = QPointF(height * (1 + 2 * id.x()), side * (1 + 1.5 * id.y()));
	if (id.y() % 2 == 1) //przesunięcie co drugiego wiersza nieco w prawo
		center.setX(center.x() + height);
	return center;
}

qreal BoardArea::calcHeight(qreal side)
{
	if (side < 0)
		return 0;
	qreal sqrt3 = 1.732;
	return side * sqrt3 / 2;
}

void BoardArea::changeSize(int d)
{
	if (tileSide_ + d < MINIMALNY_ROZMIAR_HEXA || tileSide_ + d > MAKSYMALNY_ROZMIAR_HEXA)
		return;
	this->tileSide_ += d;

	for (int i = 0; i < tiles_.size(); ++i)
		tiles_[i]->setSide(tileSide_);

	for (int i = 0; i < playerMarkers_.size(); ++i) {
		playerMarkers_[i]->setRadius(tileSide_ / 2);
		playerMarkers_[i]->setPos(calcPlayerMarkerCenter(i));
	}

	setSceneRect(calcBoardAreaRect());
	update();
}

void BoardArea::increaseSize()
{
	changeSize(ZMIANA_WIELKOSCI_PLANSZY * -1);
}

void BoardArea::decreaseSize()
{
	changeSize(ZMIANA_WIELKOSCI_PLANSZY);
}

void BoardArea::resetSize()
{
	changeSize(InitialTileSize - tileSide_);
}

void BoardArea::animationNextStep()
{
	if (pathToAnimate.empty()) {
		for (int i = 0; i < playerMarkers_.size(); ++i)
			playerMarkers_[i]->setPos(calcPlayerMarkerCenter(i));
		return;
	}

	animationStart = playerMarkers_[animatedMarkerIndex]->pos();
	playerPositions_->insert(animatedMarkerIndex, qMakePair(playerPositions_->at(animatedMarkerIndex).first, pathToAnimate.back()));
	playerPositions_->removeAt(animatedMarkerIndex + 1);
	animationFinish = calcPlayerMarkerCenter(animatedMarkerIndex);

	pathToAnimate.pop_back();
	ticTac->start();
}

void BoardArea::animationStep(int phase)
{
	qreal posX = animationStart.x() + (animationFinish.x() - animationStart.x()) * phase / 100;
	qreal posY = animationStart.y() + (animationFinish.y() - animationStart.y()) * phase / 100;

	playerMarkers_[animatedMarkerIndex]->setPos(posX, posY);
}

void BoardArea::clearSelection()
{
	if (selectedTile != nullptr) {
		selectedTile->deselect();
		selectedTile = nullptr;
	}
}
