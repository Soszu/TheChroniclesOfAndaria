#ifndef QUESTWINDOW_H
#define QUESTWINDOW_H

#include <QtWidgets>

#include "Core/Containers/Player.h"
#include "Core/Containers/Quest.h"
#include "Core/Board.h"

class Board;

class QuestWindow : public QDialog {
	Q_OBJECT;
public:
	QuestWindow(Player *player, Board *board);

private:
	Player *player_;
	Board *board_;

	QTextBrowser *questDescriptionWidget;
	QListWidget *questListWidget;
	QPushButton *showDestinationButton;

private slots:
	void displayQuestDescription(const QModelIndex &index);
	void showDestination();
};

#endif
