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

#include "Core/GameCycle.h"

GameCycle::GameCycle(int *parseResult)
	: parseResult_(parseResult), errorMessageBox_(new QDialog)
{
	initGameCycle();
}

GameCycle::~GameCycle()
{
	delete errorMessageBox_;
	qDeleteAll(players_);
	qDeleteAll(computerPlayers_.values());
}

/**
 * @brief GameCycle::setGracze Przyjmuje dane graczy
 * @param gracze
 */
void GameCycle::setPlayers(QList <Player *> players)
{
	playersAlive_ = players.size();
	this->players_ = players;
	board_->setPlayers(&this->players_);
	for(int i = 0; i < players.size(); ++i)
		if (players[i]->isAI())
			computerPlayers_.insert(i, new AI(players[i]));
	gameMaster_->setPlayers(&this->players_);
}

void GameCycle::setMainWindow(MainWindow *mainWindow)
{
	this->mainWindow_ = mainWindow;
}

MainWindow * GameCycle::mainWindow() const
{
	return mainWindow_;
}

/**
 * @brief GameCycle::wystapilBlad	Metoda wywoływana przez Mistrza Gry lub Planszę, żeby zgłosić błąd i przerwać pracę.
 * @param komunikat	komunikat z opisem błądu który ma zostać wyświetlony
 * @param blad		numer błędu do zwrócenia przez program
 */
void GameCycle::displayErrorMessage(const QString &message, int error) const
{
	qDebug() << message;

	QMessageBox::critical(
		errorMessageBox_,
		QString::fromUtf8("Napotkano błąd"),
		message + QString::fromUtf8("\n\nNastąpi zamknięcie programu.")
	);

	*parseResult_ = error;
}

void GameCycle::setGameMaster(GameMaster *gameMaster)
{
	this->gameMaster_ = gameMaster;
}

void GameCycle::setBoard(Board *board)
{
	this->board_ = board;
}

const QList <Player *> & GameCycle::players()
{
	return players_;
}

/**
 * @brief GameCycle::removePlayer Wykreśla aktualnego gracza z listy, i sprawdza, czy nie został przypadkiem tylko 1 gracz - zwycięzca
 */
void GameCycle::removeCurrentPlayer()
{
	QMessageBox::information(
		mainWindow_,
		QString::fromUtf8("Przykro mi, ale ..."),
		players_[currentPlayer_]->name() + QString::fromUtf8(" wypadł z gry.")
	);

	players_[currentPlayer_]->setIsActive(false);
	--playersAlive_;

	if (playersAlive_ == 1) {
		nextPlayer();
		QMessageBox::information(
			mainWindow_,
			QString::fromUtf8("Gratulacje!"),
			players_[currentPlayer_]->name() + QString::fromUtf8(" jest teraz jedynym żywym graczem i tym samym zwycięża.")
		);
		mainWindow_->close();
	} else {
		board_->removePlayer(currentPlayer_);
	}
}

/**
 * @brief GameCycle::graczWygral	ogłasza Zwycięzcę i kończy grę.
 * @param gracz		dane zwycięzcy
 */
void GameCycle::playerHasWon(Player *player)
{
	QMessageBox::information(
		mainWindow_,
		QString::fromUtf8("Gratulacje!"),
		player->name() + QString::fromUtf8(" zwyciężył.")
	);
	mainWindow_->close();
}

/**
 * @brief GameCycle::czySpelnionyWarunekZwyciestwa	Sprawdza, czy został spełniony warunek zwycięstwa.
 * @param gracz		dane gracza, który jest sprawdzany
 * @return	true jeśli warunek jest spełniony, w p.p. false
 */
bool GameCycle::hasPlayerWon(Player *player)
{
	int maxReputations = 0;
	for(int i = 0; i < KingdomCount; ++i)
		if(player->reputation()[i] == MaximumReputation)
			++maxReputations;

	return player->level() == MaximumLevel && maxReputations >= MaximumReputationsToWin;
}

/**
 * @brief GameCycle::rozpocznij	Rozpoczyna rozgrywkę przez wykonanie ruchu pierwszego gracza
 */
void GameCycle::beginGame()
{
	initGameCycle();
	qDebug() << "Player count: " << players_.size();
	mainWindow_->changeDate(day_, week_);
	gameMaster_->beginGame();
	board_->beginGame();
	movePlayer(currentPlayer_);
}

/**
 * @brief GameCycle::ruszGracza	Przekazuje mistrzowi gry i planszy, że zaczyna się ruch gracza o zadanym indeksie
 * @param indeks	indeks poruszanego gracza na liście graczy
 */
void GameCycle::movePlayer(int index)
{
	qDebug() << "Cykl Gry rusza gracza o indeksie: " << currentPlayer_;
	board_->movePlayer(index);
	gameMaster_->movePlayer(index);
}

/**
 * @brief GameCycle::wyznaczKolejnego	Przestawia indeksAktualnego na kolejnego aktywnego gracza.
 */
void GameCycle::nextPlayer()
{
	do {
		++currentPlayer_;
		if(currentPlayer_ >= players_.size())
		{
			newDay();
			currentPlayer_ = 0;
		}
	} while (!players_[currentPlayer_]->isActive());
}

void GameCycle::newDay()
{
	if (day_ < DaysPerWeek) {
		++day_;
	} else {
		day_ = 1;
		++week_;
		gameMaster_->newWeek();
	}
	mainWindow_->changeDate(day_, week_);
}

/**
 * @brief GameCycle::zakonczTure Kończy turę aktualnego gracza, sprawdza, czy spełnił warunek zwycięstwa, jeśli nie wyświetla następnego
 */
void GameCycle::endTurn()
{
	if (hasPlayerWon(players_[currentPlayer_]))
		playerHasWon(players_[currentPlayer_]);

	nextPlayer();
	movePlayer(currentPlayer_);
}

void GameCycle::initGameCycle()
{
	week_ = 1;
	day_ = 1;
	currentPlayer_ = 0;
}
