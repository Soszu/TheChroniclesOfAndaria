#include "Core/Operations/QuestManagement.h"
#include "Gui/Windows/QuestWindow.h"

QuestWindow::QuestWindow(Player *player, Board *board)
	: player_(player), board_(board)
{
	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	setWindowTitle("Twoje zadania");

	questListWidget = new QListWidget();
	questListWidget->setToolTip(QString::fromUtf8("Lista zadań, które aktualnie wykonujesz."));

	for (Quest *q : *player->quests())
		questListWidget->addItem(q->title());

	QHBoxLayout *upperLayout = new QHBoxLayout();
	upperLayout->addWidget(questListWidget);

	questDescriptionWidget = new QTextBrowser();
	questDescriptionWidget->setToolTip(QString::fromUtf8("Dokładny opis zaznaczonego zadania"));
	upperLayout->addWidget(questDescriptionWidget);
	mainLayout->addLayout(upperLayout);

	showDestinationButton = new QPushButton(QString::fromUtf8("Pokaz hex z celem"));
	showDestinationButton->setToolTip(QString::fromUtf8("Wyszczególnia hex, na który trzeba się aktualnie udać, by wykonać zadanie."));
	showDestinationButton->setEnabled(false);
	QPushButton *confirmButton = new QPushButton("Ok");

	QHBoxLayout *lowerLayout = new QHBoxLayout();
	lowerLayout->addStretch();
	lowerLayout->addWidget(showDestinationButton);
	lowerLayout->addWidget(confirmButton);
	mainLayout->addLayout(lowerLayout);

	connect(questListWidget, SIGNAL(clicked(const QModelIndex &)), this, SLOT(displayQuestDescription(const QModelIndex &)));
	connect(confirmButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(showDestinationButton, SIGNAL(clicked()), this, SLOT(showDestination()));
}

/**
 * @brief OknoZadania::wyswietlOpis	Wyświetla opis podjętego zadania.
 * @param element	dane zaznaczonego elementu
 */
void QuestWindow::displayQuestDescription(const QModelIndex &index)
{
	showDestinationButton->setEnabled(true);
	Quest *quest = player_->quest(index.row());
	generateDescription(quest, questDescriptionWidget);
}

/**
 * @brief OknoZadania::pokaz	Wysyła planszy żądanie podświetlenia konkretnego hexa.
 */
void QuestWindow::showDestination()
{
	Quest *quest = player_->quest(questListWidget->currentRow());
	board_->showTile(quest->targetField());
}
