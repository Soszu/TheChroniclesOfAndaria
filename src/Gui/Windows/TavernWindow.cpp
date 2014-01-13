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

#include "Core/Operations/QuestManagement.h"
#include "Gui/Windows/TavernWindow.h"

TavernWindow::TavernWindow(Player *player, Board *board, GameMaster *gameMaster, PlayerWindow *playerWindow, QList <Quest *> *availableQuests)
	: player_(player), board_(board), gameMaster_(gameMaster), playerWindow_(playerWindow), availableQuests_(availableQuests)
{
	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	setWindowTitle("Tawerna");
	questRejected = false;

	QLabel *currentQuestsLabel = new QLabel("Twoje dotychczasowe zadania");
	currentQuestsWidget = new QListWidget();
	currentQuestsWidget->setToolTip(QString::fromUtf8("Lista zadań, które aktualnie wykonujesz."));

	QLabel *availableQuestsLabel = new QLabel(QString::fromUtf8("Zadania dostępne do przyjęcia\n(możesz jednocześnie wykonywać ") +
					 QString::number(MaximumNumberOfQuestsTaken) +
					 QString::fromUtf8(" zadań)"));
	availableQuestsWidget = new QListWidget();
	availableQuestsWidget->setToolTip(QString::fromUtf8("Lista zadań, które możesz przyjąć w tym miejscu."));

	fillQuestListWidgets();

	QVBoxLayout *leftLayout = new QVBoxLayout();
	leftLayout->addWidget(currentQuestsLabel);
	leftLayout->addWidget(currentQuestsWidget);
	leftLayout->addWidget(availableQuestsLabel);
	leftLayout->addWidget(availableQuestsWidget);
	QHBoxLayout *upperLayout = new QHBoxLayout();
	upperLayout->addLayout(leftLayout);

	questDescriptionWidget = new QTextBrowser();
	questDescriptionWidget->setToolTip(QString::fromUtf8("Dokładny opis zaznaczonego zadania"));
	upperLayout->addWidget(questDescriptionWidget);
	mainLayout->addLayout(upperLayout);

	showDestinationButton = new QPushButton(QString::fromUtf8("Pokaz hex z celem"));
	showDestinationButton->setToolTip(QString::fromUtf8("Wyszczególnia hex, do którego należy się aktualnie udać, aby wykonać zadanie."));
	showDestinationButton->setEnabled(false);
	acceptQuestButton = new QPushButton("Przyjmij");
	acceptQuestButton->setToolTip(QString::fromUtf8("Zależnie od sytuacji, przycisk pozwala przyjąć lub odrzucić zaznaczone zadanie"));
	acceptQuestButton->setEnabled(false);
	QPushButton *confirmButton = new QPushButton("Ok");

	QHBoxLayout *lowerLayout = new QHBoxLayout();
	lowerLayout->addStretch();
	lowerLayout->addWidget(showDestinationButton);
	lowerLayout->addWidget(acceptQuestButton);
	lowerLayout->addWidget(confirmButton);
	mainLayout->addLayout(lowerLayout);

	connect(currentQuestsWidget, SIGNAL(clicked(const QModelIndex &)), this, SLOT(displayPlayerQuest(const QModelIndex &)));
	connect(availableQuestsWidget, SIGNAL(clicked(const QModelIndex &)), this, SLOT(displayAvailableQuest(const QModelIndex &)));

	connect(confirmButton, SIGNAL(clicked()), this, SLOT(generateQuests()));
	connect(confirmButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(showDestinationButton, SIGNAL(clicked()), this, SLOT(showDestination()));
	connect(acceptQuestButton, SIGNAL(clicked()), this, SLOT(processQuest()));
}

/**
 * @brief OknoTawerny::wypelnijListy	Wypełnia listy własnych i oferowanych zadań namemi.
 */
void TavernWindow::fillQuestListWidgets()
{
	currentQuestsWidget->clear();
	for (Quest *q : *player_->quests())
		currentQuestsWidget->addItem(q->title());

	availableQuestsWidget->clear();
	for (Quest *q : *availableQuests_)
		availableQuestsWidget->addItem(q->title());
}

/**
 * @brief OknoTawerny::wyswietlOpisDlaWlasnych		Wyświetla opis dla wykonywanego zadania.
 * @param element	dane zaznaczonego elementu
 */
void TavernWindow::displayPlayerQuest(const QModelIndex &index)
{
	availableQuestsWidget->setCurrentRow(-1);

	Quest *quest = player_->quest(index.row());
	lastDisplayedQuest = quest;

	showDestinationButton->setEnabled(true);
	acceptQuestButton->setEnabled(!questRejected);
	acceptQuestButton->setText(abandonText);

	generateDescription(quest, questDescriptionWidget);
}

/**
 * @brief OknoTawerny::wyswietlOpisDlaMozliwych		Wyświetla opis dla zadania oferowanego.
 * @param element	dane zaznaczonego elementu
 */
void TavernWindow::displayAvailableQuest(const QModelIndex &index)
{
	currentQuestsWidget->setCurrentRow(-1);

	Quest *quest = availableQuests_->at(index.row());
	lastDisplayedQuest = quest;

	showDestinationButton->setEnabled(true);
	bool playerHasMaxQuests = player_->quests()->size() == MaximumNumberOfQuestsTaken;
	bool alreadyTaken;
	for (Quest *q : *player_->quests())
		if (quest->id() == q->id())
			alreadyTaken = true;
	acceptQuestButton->setEnabled(!playerHasMaxQuests && !alreadyTaken);
	acceptQuestButton->setText(acceptText);

	generateDescription(quest, questDescriptionWidget);
}

/**
 * @brief OknoTawerny::przyjmij		Zależnie od zaznaczenia przyjmuje oferowane zadanie albo odrzuca jedno z podjętych
 */
void TavernWindow::processQuest()
{
	if (acceptQuestButton->text() == acceptText) {  //NOTE do I really want string comparision? Maybe boolean flag?
		int index = availableQuestsWidget->currentRow();
		player_->quests()->push_back(new Quest(availableQuests_->at(index)));
		player_->quest(player_->quests()->size() - 1)->setEmployerField(player_->position());
		availableQuests_->removeAt(index);
	} else {
		Quest *quest = player_->quest(currentQuestsWidget->currentRow());
		player_->removeQuest(quest->id());
		questRejected = true;
		player_->setGold(qMax(0, player_->gold() - QuestDeclineCost));
		playerWindow_->displayPlayer(player_);
	}
	fillQuestListWidgets();
	acceptQuestButton->setEnabled(false);
	showDestinationButton->setEnabled(false);
}

/**
 * @brief OknoTawerny::pokaz	Wysyła do planszy żądanie podświetlenia przycisku.
 */
void TavernWindow::showDestination()
{
	board_->showTile(lastDisplayedQuest->targetField());
}

/**
 * @brief OknoTawerny::dolosujZadania		Informuje mistrza gry o potrzebie dolosowania zadań
 */
void TavernWindow::generateQuests()
{
	gameMaster_->generateQuests();
}
