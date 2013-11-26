#ifndef PRIZEWINDOW_H
#define PRIZEWINDOW_H

#include <QtWidgets>

#include "Core/Containers/Item.h"
#include "Core/Containers/Prize.h"
#include "Core/Containers/Player.h"
#include "Core/Game.h"
#include "Core/GameCycle.h"

class GameCycle;

class PrizeWindow : public QDialog {
	Q_OBJECT;
public:
	PrizeWindow(Player *player, Prize *prize, const QList <const Item *> &prizeItems, GameCycle *gameCycle, bool isEndOfTurn); //TODO CFiend bool w API jest podejrzany

public slots:
	void displayPrizeWindow();

private:
	void increaseAttribute(atrybut index);
	QString prizeDescription() const;

	Player *player_;
	Prize *prize_;
	QList <const Item *> prizeItems_;
	GameCycle *gameCycle_;
	bool isEndOfTurn_;

	QListWidget *itemListWidget;
	QTextBrowser *itemDescriptionWidget;
	QTextBrowser *prizeDescriptionWidget;

	bool isLevelUp;
	QList <QComboBox *> attributePointChoice;

private slots:
	void displayItemDescription(const QModelIndex &index);
	void confirm();
};

#endif
