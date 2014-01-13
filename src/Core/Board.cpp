#include "Core/Parsers/BoardParser.h"
#include "Core/Board.h"

Board::Board(GameCycle *gameCycle)
	: gameCycle_(gameCycle), playerPositions_(new QList <QPair <QColor, FieldId> >), fields_(nullptr)
{
	BoardParser pu(this);
	if (pu.bladWczytywania()) {
		gameCycle_->displayErrorMessage(QString::fromUtf8("Wystąpił błąd przy wczytywaniu ustawienia planszy\n\n") + pu.trescBledu, blad_parsera_ustawienia_planszy);
		return;
	}
	qDebug() << QString::fromUtf8("Ustawienie planszy wczytano poprawnie");
}

Board::~Board()
{
	if (fields_ != nullptr) {
		qDeleteAll(*fields_);
		delete fields_;
	}
}

void Board::setBoardArea(BoardArea *boardArea)
{
	this->boardArea_ = boardArea;
}

void Board::setGameMaster(GameMaster *gameMaster)
{
	this->gameMaster_ = gameMaster;
}

void Board::setPlayers(QList <Player *> *players)
{
	this->players_ = players;
}

const QList <int> & Board::cities()
{
	return cities_;
}

/**
 * @brief Board::ruszGracza Rusza gracza podanego jako parametr. Rysuje planszę, jeśli jeszcze tego nie zrobiono.
 * @param gracz
 */
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

/**
 * @brief Board::ustalOsiagalne	Ustala pola osiągalne dla podanego gracza.
 *					Zapisuje wynik na prywatnej liście "osiągalne".
 * @param gracz
 */
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
			int distance = current.first + fields_->at(index)->moveCost();
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

/**
 * @brief Board::uaktualnijOsiagalne	Metoda wywoływana z zewnątrz.
 *					Uaktualnia i podświetla na nowo osiągalne pola.
 */
void Board::updateReachableFields()
{
	findReachableFields(currentPlayer_);
	boardArea_->highlightFields(showReachableFields());
}

void Board::removePlayer(int index)
{
	boardArea_->removePlayerMarker(index);
}

/**
 * @brief Board::pokazPole	Pokazuje na życzenie pole spod podanego indeksu.
 * @param pole		Indeks pola do pokazania
 * @return Kopia	pola z podanego indeksu
 */
Field * Board::showField(FieldId field)
{
	return fields_->at(fieldIdToIndex(field));
}

QString Board::playerDescription(int index)
{
	QString description;
	Player *player = players_->at(index);
	description += player->name() + description + "\n";
	description += Player::raceString()[player->playerRace()] + " " + Player::classString()[player->playerClass()] + "\n";
	description += QObject::tr("poziom ") + QString::number(player->level()) + "\n";
	description += QObject::tr("zdrowie ") + QString::number(player->healthCurrent()) + "/" + QString::number(player->healthMax());
	return description;
}

/**
 * @brief Board::czyTrwaAnimacja	Podaje informację, czy ruch jest własnie animowany.
 * @return	Jeśli ruch jest właśnie animowany, to zwraca true, w.p.p false.
 */
bool Board::isMoveInProgress()
{
	return boardArea_->animationInProgress();
}

/**
 * @brief Board::pokazOsiagalne	Pokazuje listę osiągalnych pól dla aktualnego gracza.
 * @return	Zwraca kopię listy osiągalnych pól. (Żeby nie można jej było podmienić)
 */
QList <FieldId> Board::showReachableFields()
{
	return reachable_;
}

/**
 * @brief Board::odtworzDroge		Odtwarza drogę od osiągalnego hexa do pozycji aktualnego gracza.
 * @param pole
 * @return
 */
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

/**
 * @brief Board::spiszPozycje		Spisuje pozycje graczy jako listę par <kolor, pozycja>.
 *					Zapamiętuje wynik w zmiennej pozycjeGraczy.
 * @return	Zwraca adres do listy z wynikiem.
 */
QList <QPair <QColor, FieldId> > * Board::collectPlayerPositions()
{
	playerPositions_->clear();
	for (const Player *p : *players_)
		playerPositions_->push_back(qMakePair(p->color(), p->position()));
	return playerPositions_;
}

/**
 * @brief Board::ruchAI	Obsługuje decyzję AI o ruchu.
 * @param pole		pole na które chce się ruszyć AI
 */
void Board::moveAI(FieldId field)
{
	tileClicked(field);
}

/**
 * @brief Board::pokazHex	Przekazuje obszarowi planszy żadanie pokazania hexa o danym id.
 * @param id
 */
void Board::showTile(FieldId field)
{
	boardArea_->showTile(fieldIdToIndex(field));
}

/**
 * @brief Board::blokujRuch	Metoda wywoływana z zewnątrz. Blokuje możliwość ruchu aktualnemu graczowi.
 */
void Board::disablePlayerMove()
{
	playerHasMoved_ = true;

	findReachableFields(currentPlayer_);
	boardArea_->highlightFields(showReachableFields());
}

/**
 * @brief Board::IdToIndeks	Zamienia ID pola zapisane w 2 intach na indeks pola na liście pól czyli 1 int.
 *				Efekt uboczny zapisania ID jako 2 x int.
 * @param pole		ID pola do zamiany
 * @return		indeks pola na liście pól (numerowanie od 0)
 */
int Board::fieldIdToIndex(FieldId field)
{
	return field.y() * boardWidth_ + field.x();
}

/**
 * @brief Board::indeksToID	Zamienia indeks na struct FieldId.
 * @param indeks	indeks do zamiany
 * @return		FieldId odpowiadające danemu indeksowi
 */
FieldId Board::indexToFieldId(int index)
{
	FieldId tmp;
	tmp.rx() = index % boardWidth_;
	tmp.ry() = index / boardWidth_;

	return tmp;
}

/**
 * @brief Board::rozpocznij		Zbiór operacji wykonywanych na początku rozgrywki
 */
void Board::beginGame()
{
	boardArea_->drawBoard(fields_, boardWidth_, boardHeight_, collectPlayerPositions());
}

/**
 * @brief Board::sasiedniePola Zwraca listę pól sąsiadujących z zadanym polem.
 * @param pole
 * @return
 */
QList <FieldId> Board::neighboringFields(FieldId field)
{
	QList <FieldId> result;
	FieldId tmp = field;
	if (field.x() > 0) {
		tmp.rx() = field.x() - 1;
		result.push_back(tmp);
	}
	if (field.x() < boardWidth_ - 1) {
		tmp.rx() = field.x() + 1;
		result.push_back(tmp);
	}
	tmp.rx() = field.x();

	if (field.y() < boardHeight_ - 1) {
		tmp.ry() = field.y() + 1;
		result.push_back(tmp);

		if (field.y() % 2 == 1) {
			if (field.x() < boardWidth_ - 1) {
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
			if (field.x() < boardWidth_ - 1) {
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
