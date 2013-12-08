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

#include "Gui/BoardArea.h"

BoardArea::BoardArea(Board *board)
	: tileSide_(InitialTileSize), board_(board), selectedTile(nullptr)
{
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

/**
 * @brief BoardArea::wyswietlKomunikat	wyświetla przekazany komunikat na pasku statusu
 * @param tresc
 */
void BoardArea::displayMessage(const QString &message)
{
	statusBar_->showMessage(message, DLUGOSC_TRWANIA_KOMUNIKATU);
}

/**
 * @brief BoardArea::narysujPlansze Rysuje plansze na ekranie
 * @param pola lista pól planszy
 * @param kolumny ilość kolumn planszy
 * @param wiersze ilość wierszy planszy
 * @param pozycjeGraczy mapa, w której każdemu kolorowi gracza przypisana jest jego pozycja
 */
void BoardArea::drawBoard(QList <Field *> *fields, int columnCount, int rowCount, QList <QPair <QColor, FieldId> > *playerPositions)
{
	this->rowCount_ = rowCount;
	this->columnCount_ = columnCount;
    this->playerPositions_ = playerPositions;
	setBackgroundBrush(QBrush(Qt::black));
	setSceneRect(calcBoardAreaRect());

	for (int i = 0; i < fields->size(); ++i) {
		tiles_.append(new Tile(fields->at(i), tileSide_, this));
		addItem(tiles_.at(i));
	}

	for (int i = 0; i < playerPositions_->size(); ++i) {
		playerMarkers_.append(new PlayerMarker(playerPositions_->at(i).first, board_->playerDescription(i), calcPlayerMarkerCenter(i), tileSide_ / 2));
		addItem(playerMarkers_.at(i));
	}
}

/**
 * @brief BoardArea::kliknietoHex Informuje planszę o kliknięciu na hex
 * @param id
 */
void BoardArea::tileClicked(FieldId id)
{
	board_->tileClicked(id);
}

/**
 * @brief BoardArea::wykonajRuch Zmienia potrzedne zmienne i zaczyna wykonywanie animowanego ruchu.
 * @param droga Lista poł po których pionek ma się poruszać.
 * @param indeks indeks gracza, który wykonuje ruch.
 */
void BoardArea::executeMove(const QList <FieldId> &path, int playerNumber)
{
	pathToAnimate = path;
	animatedMarkerIndex = playerNumber;

	while (!highlightedFields_.isEmpty()) {
		tiles_[highlightedFields_.back()]->setHighlighted(false);
		highlightedFields_.pop_back();
	}

	animationNextStep();
}

/**
 * @brief BoardArea::usunPionek	Usuwa z planszy pionek, którego indeks został podany
 * @param indeks	indeks pionka w tablicy pionków
 */
void BoardArea::removePlayerMarker(int index)
{
	playerMarkers_[index]->setVisible(false);
}

/**
 * @brief BoardArea::podswietl Podświetla zadane pola.
 * @param lista
 */
void BoardArea::highlightFields(const QList <FieldId> &fields)
{
	while (!highlightedFields_.isEmpty()) {
		tiles_[highlightedFields_.back()]->setHighlighted(false);
		highlightedFields_.pop_back();
	}

	for (int i = 0; i < fields.size(); ++i) {
		tiles_[fields[i].y() * columnCount_ + fields[i].x()]->setHighlighted(true);
		tiles_[fields[i].y() * columnCount_ + fields[i].x()]->update();
		highlightedFields_.push_back(fields[i].y() * columnCount_ + fields[i].x());
	}
}

/**
 * @brief BoardArea::pokazHex	Zaznacza hex znajdujący się na liście pod wskazanym indeksem.
 * @param indeks
 */
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

/**
 * @brief BoardArea::animacjaTrwa Informuje czy trwa animacja.
 * @return
 */
bool BoardArea::animationInProgress()
{
	return (ticTac->state() == QTimeLine::Running || highlightTimeLine->state() == QTimeLine::Running);
}

/**
 * @brief BoardArea::podajOgraniczenie Na podstawie ilości hexów w kolumnach i wierszach oraz długości boku hexa zwraca najmniejszy prostokąt, w którym zawiera się cała plansza.
 * @param wiersze
 * @param kolumny
 * @param bokHexa
 * @return
 */
QRectF BoardArea::calcBoardAreaRect()
{
	qreal sceneWidth = columnCount_ * calcHeight(tileSide_) * 2;
	if (rowCount_ > 1)
		sceneWidth += calcHeight(tileSide_);
	qreal sceneHeight = 2 * tileSide_ + (rowCount_ - 1) * 1.5 * tileSide_;
	return QRectF(0, 0, sceneWidth, sceneHeight);
}

/**
 * @brief BoardArea::podajSrodekPionka Na podstawie listy pozycjeGraczy, podaje gdzie powinien stać pionek.
 * @param indeks indeks gracza na liscie "pozycjeGraczy"
 * @param bok bok Hexa
 * @return
 */
QPointF BoardArea::calcPlayerMarkerCenter(int index)
{
	QPointF center = calcCenter(playerPositions_->at(index).second, tileSide_);
	if (index >= NUMBER_OF_ENVISAGED_MODIFICATORS)
		return center;

	int markersOnSameField = 0;
	FieldId field = playerPositions_->at(index).second;
	for (int i = 0; i < index; ++i)
		if (playerPositions_->at(i).second.x() == field.x() && playerPositions_->at(i).second.y() == field.y())
			++markersOnSameField;

	QPointF shift(POSITION_MODIFICATORS[markersOnSameField] * tileSide_ / 4.0);
	return center + shift;
}

/**
 * @brief BoardArea::podajSrodek Na podstawie długości boku i współrzędnych pola podaje jego środek.
 * @param id współrzędne pola
 * @param bok środek pola
 * @return jeśli dane są poprawne, zwraca środek, w przeciwnym razie punkt (-1,-1)
 */
QPointF BoardArea::calcCenter(FieldId id, qreal side)
{
	if (side < 0 || id.x() < 0 || id.y() < 0)
		return QPointF(-1, -1);
	qreal height = calcHeight(side);
	QPointF center = QPointF(height * (1 + 2 * id.x()), side * (1 + 1.5 * id.y()));
	if (id.y() % 2 == 1) //przesunięcie co drugiego wiersza nieco w prawo
		center.setX(center.x() + height);
	return center;
}

/**
 * @brief BoardArea::podajWysokosc Zwraca wysokość trójkąta równobocznego
 * @param bok bok trójkąta
 * @return wysokość trójkąta równobocznego, lub 0, jeśli bok jest ujemny.
 */
qreal BoardArea::calcHeight(qreal side)
{
	if (side < 0)
		return 0;
	qreal sqrt3 = 1.732;
	return side * sqrt3 / 2;
}

/**
* @brief BoardArea::zmienRozmiar Zmienia rozmiar planszy o d punktów, jeśli tylko nie przekroczy przez to minimalnego lub maksymalnego rozmiaru.
* @param d
*/
void BoardArea::changeSize(int d)
{
	if (tileSide_ + d < MINIMALNY_ROZMIAR_HEXA || tileSide_ + d > MAKSYMALNY_ROZMIAR_HEXA)
		return;
	this->tileSide_ += d;

	for (int i = 0; i < tiles_.size(); ++i)
		tiles_.at(i)->setSide(tileSide_);

	for (int i = 0; i < playerMarkers_.size(); ++i) {
		playerMarkers_.at(i)->setRadius(tileSide_ / 2);
		playerMarkers_.at(i)->setPos(calcPlayerMarkerCenter(i));
	}

	setSceneRect(calcBoardAreaRect());
	update();
}

/**
 * @brief BoardArea::powiekszRozmiarPlanszy	Zwiększa o ustaloną wartość rozmiar planszy.
 */
void BoardArea::increaseSize()
{
	changeSize(ZMIANA_WIELKOSCI_PLANSZY * -1);
}

/**
 * @brief BoardArea::pomniejszRozmiarPlanszy	Zmniejsza o ustaloną wartość rozmiar planszy.
 */
void BoardArea::decreaseSize()
{
	changeSize(ZMIANA_WIELKOSCI_PLANSZY);
}

/**
 * @brief BoardArea::przywrocRozmiarPlanszy	Przywraca bazowy rozmiar planszy.
 */
void BoardArea::resetSize()
{
	changeSize(InitialTileSize - tileSide_);
}

/**
 * @brief BoardArea::kolejnePrzejscie Wykonuje animowane przejscie na sąsiadujące pole.
 */
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

/**
 * @brief BoardArea::krokAnimacji Przesuwa pionek nad planszą na podstawie fazy animacji
 * @param faza faza animacji
 */
void BoardArea::animationStep(int phase)
{
	qreal posX = animationStart.x() + (animationFinish.x() - animationStart.x()) * phase / 100;
	qreal posY = animationStart.y() + (animationFinish.y() - animationStart.y()) * phase / 100;

	playerMarkers_[animatedMarkerIndex]->setPos(posX, posY);
}

/**
 * @brief BoardArea::usunZaznaczenie	Usuwa zaznaczenie z przycisku, który jest podświetlony.
 *						(Jest tylko 1 taki przycisk)
 */
void BoardArea::clearSelection()
{
	if (selectedTile != nullptr) {
		selectedTile->deselect();
		selectedTile = nullptr;
	}
}
