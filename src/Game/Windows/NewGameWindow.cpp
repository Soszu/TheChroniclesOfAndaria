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

#include "Game/Windows/NewGameWindow.h"

NewGameWindow::NewGameWindow(QWidget *parent)
	: QDialog(parent), playerCount_(MinPlayers)
{
	messageBox = new QMessageBox(this);
	messageBox->setWindowTitle(QString::fromUtf8("Błąd"));

	this->setWindowTitle("Ustalanie graczy");
	this->setSizeGripEnabled(false);

	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);

	QVBoxLayout *playerSelectionRowsLayout = new QVBoxLayout();
	for (int i = 0; i < MaxPlayers; ++i) {
		playerSelectionRowLayouts[i] = new QHBoxLayout;
		playerSelectionRowsLayout->addLayout(playerSelectionRowLayouts[i]);
	}

	QPushButton *addPlayerButton = new QPushButton("Dodaj gracza", this);
	addPlayerButton->setToolTip("Dodaj kolejnego gracza do rozgrywki.<br>"
				"Limit to 8 graczy.");
	connect(addPlayerButton, SIGNAL(clicked()), this, SLOT(addPlayerSelectionRow()));

	QPushButton *removePlayerButton = new QPushButton(QString::fromUtf8("Usuń gracza"), this);
	removePlayerButton->setToolTip(QString::fromUtf8("Usun ostatniego gracza.<br>"
						 "Musi być co najmniej 2 graczy."));
	connect(removePlayerButton, SIGNAL(clicked()), this, SLOT(removePlayerSelectionRow()));

	QPushButton *cancelButton = new QPushButton("Anuluj", this);
	cancelButton->setToolTip(QString::fromUtf8("Anuluj wpisywanie graczy i wyjdź z programu."));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));

	QPushButton *confirmButton = new QPushButton("OK", this);
	confirmButton->setToolTip(QString::fromUtf8("Zatwierdź ustawienia i rozpocznij rozgrywkę."));
	connect(confirmButton, SIGNAL(clicked()), this, SLOT(validate()));

	QHBoxLayout *buttonLayout = new QHBoxLayout();
	buttonLayout->addWidget(addPlayerButton);
	buttonLayout->addWidget(removePlayerButton);
	buttonLayout->addStretch();
	buttonLayout->addWidget(cancelButton);
	buttonLayout->addWidget(confirmButton);

	for (int i = 0; i < playerCount_; ++i) {
		PlayerSelectionRow newRow;
		fillPlayerSelectionRow(&newRow, i);
		playerRows.append(newRow);
	}

	mainLayout->addLayout(playerSelectionRowsLayout);
	mainLayout->addStretch();
	mainLayout->addLayout(buttonLayout);

}

NewGameWindow::~NewGameWindow()
{
	//TODO CFiend add dtor to PlayerSelectionRow instead of this?
	while (!playerRows.empty()) {
		delete playerRows.back().nameEdit;
		delete playerRows.back().playerClassCombo;
		delete playerRows.back().playerRaceCombo;
		delete playerRows.back().colorCombo;
		delete playerRows.back().isAiCheckBox;

		playerRows.pop_back();
	}
}

void NewGameWindow::setGameCycle(GameCycle *gameCycle)
{
	this->gameCycle_ = gameCycle;
}

void NewGameWindow::setMainWindow(QMainWindow *mainWindow)
{
	this->mainWindow_ = mainWindow;
}

/**
 * @brief OknoNowejGry::wypelnij Wypełnia zadany wiersz w formularzu opcjami do wyboru.
 * @param wiersz struct ze wskaźnikami na Elements do wypełnienia
 * @param numer numer aktualnego wiersza
 */
void NewGameWindow::fillPlayerSelectionRow(NewGameWindow::PlayerSelectionRow *row, int playerNumber)
{
	row->nameEdit = new QLineEdit("Gracz"+QString::number(playerNumber + 1));
	row->nameEdit->setToolTip(QString::fromUtf8("Wpisz nazwę postaci.<br>"
						    "Nie więcej niż 20 znaków."));
	row->playerRaceCombo = new QComboBox();
	row->playerRaceCombo->setToolTip(QString::fromUtf8("Wybierz rasę postaci."));
	row->playerClassCombo = new QComboBox();
	row->playerClassCombo->setToolTip(QString::fromUtf8("Wybierz klasę postaci."));
	row->colorCombo = new QComboBox();
	row->colorCombo->setToolTip(QString::fromUtf8("Wybierz kolor pionka."));
	row->isAiCheckBox = new QCheckBox();
	row->isAiCheckBox->setToolTip(QString::fromUtf8("Czy ruchami gracza ma sterować komputer?"));

	for (int i = 0; i < PlayerRaceCount; ++i)
		row->playerRaceCombo->addItem(PlayerRaceString[i]);

	for (int i = 0; i < PlayerClassCount; ++i)
		row->playerClassCombo->addItem(PlayerClassString[i]);

	for (int i = 0; i < LICZBA_MOZLIWYCH_KOLOROW; ++i)
		row->colorCombo->addItem(MOZLIWE_KOLORY[i]);

	row->colorCombo->setCurrentIndex(playerNumber);
	row->isAiCheckBox->setText("Komputer?");

	playerSelectionRowLayouts[playerNumber]->addWidget(row->nameEdit);
	playerSelectionRowLayouts[playerNumber]->addWidget(row->playerRaceCombo);
	playerSelectionRowLayouts[playerNumber]->addWidget(row->playerClassCombo);
	playerSelectionRowLayouts[playerNumber]->addWidget(row->colorCombo);
	playerSelectionRowLayouts[playerNumber]->addWidget(row->isAiCheckBox);
}

/**
 * @brief OknoNowejGry::przekazDane Sprawdza poprawnośc danych, przepisuje dane z formularza i wypycha je dalej
 */
void NewGameWindow::validate()
{
	for (int i = 0; i < playerCount_; ++i) {
		if (playerRows[i].nameEdit->text().size() == 0) {
			messageBox->setText(QString::fromUtf8("Nazwa co najmniej jednego z graczy nie została wpisana poprawnie."));
			messageBox->show();
			return;
		}

		if (playerRows[i].nameEdit->text().size() > MAKSYMALNA_DLUGOSC_NAZWY) {//TODO CFiend to raczej trzeba ustawic na poziome QLineEdit
			messageBox->setText(QString::fromUtf8("Nazwa co najmniej jednego z graczy jest za długa. Limit to ") + QString::number(MAKSYMALNA_DLUGOSC_NAZWY)+ QString::fromUtf8("znaków."));
			messageBox->show();
			return;
		}

		for (int j = i + 1; j < playerCount_; ++j)
			if (playerRows[i].colorCombo->currentText() == playerRows[j].colorCombo->currentText()) {
				messageBox->setText(QString::fromUtf8("Co najmniej jeden kolor się powtarza."));
				messageBox->show();
				return;
			}
	}

	QList <Player *> playerList;
	for (int i = 0; i < playerCount_; ++i ){
		playerList.push_back(new Player(playerRows[i].nameEdit->text(),
					(PlayerRace)playerRows[i].playerRaceCombo->currentIndex(),
					(PlayerClass)playerRows[i].playerClassCombo->currentIndex(),
					KOLORY[playerRows[i].colorCombo->currentIndex()],
					playerRows[i].isAiCheckBox->checkState()));
	}
	//korzystam tutaj z faktu, że pola w przyciskach są w takiej kolejności jak w tablicy,
	//a tam, są w takiej kolejności jak w enumach
	//TODO CFiend powyzszy komentarz do wywalenia po przerzuceniu enum na enum class

	gameCycle_->setPlayers(playerList);
	gameCycle_->beginGame();
	mainWindow_->showMaximized();
	this->close();
}

/**
 * @brief OknoNowejGry::dodajWiersz Dodaje na końcu wiersz do wprowadzenia danych gracza
 */
void NewGameWindow::addPlayerSelectionRow()
{
	if (playerCount_ >= MaxPlayers)
		return;

	PlayerSelectionRow newRow;
	fillPlayerSelectionRow(&newRow, playerCount_);
	playerRows.push_back(newRow);
	++playerCount_;
}

/**
 * @brief OknoNowejGry::usunWiersz Usuwa ostatni wiersz z danymi gracza.
 */
void NewGameWindow::removePlayerSelectionRow()
{
	if (playerCount_ <= MinPlayers)
		return;

	--playerCount_;
	PlayerSelectionRow tmp = playerRows.back();

	playerSelectionRowLayouts[playerCount_]->removeWidget(tmp.nameEdit);
	playerSelectionRowLayouts[playerCount_]->removeWidget(tmp.playerRaceCombo);
	playerSelectionRowLayouts[playerCount_]->removeWidget(tmp.playerClassCombo);
	playerSelectionRowLayouts[playerCount_]->removeWidget(tmp.colorCombo);
	playerSelectionRowLayouts[playerCount_]->removeWidget(tmp.isAiCheckBox);

	delete tmp.nameEdit;
	delete tmp.playerClassCombo;
	delete tmp.playerRaceCombo;
	delete tmp.colorCombo;
	delete tmp.isAiCheckBox;

	playerRows.pop_back();
}
