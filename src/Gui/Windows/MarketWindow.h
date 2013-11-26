#ifndef MARKETWINDOW_H
#define MARKETWINDOW_H

#include <QtWidgets>

#include "Core/GameMaster.h"
#include "Core/Game.h"
#include "Core/Operations/EquipmentManagement.h"
#include "Core/Containers/Item.h"

class GameMaster;
class PlayerWindow;

class MarketWindow : public QDialog {
	Q_OBJECT;
public:
	MarketWindow(Player *player, PlayerWindow *playerWindow, const QList <const Item *> &wares);

private:
	void populateListWidgets();

	Player *player_;
	PlayerWindow *playerWindow_;
	QList <const Item *> wares_;

	QListWidget *playerItemList;
	QListWidget *wareList;
	QTextBrowser *itemDescriptionWidget;
	QLabel *largePotionCountLabel;
	QLabel *smallPotionCountLabel;

	QPushButton* buyButton;
	QPushButton* confirmButton;
	QPushButton* equipButton;
	QPushButton* largePotionButton;
	QPushButton* smallPotionButton;

private slots:
	void buy();
	void buyLargePotion();
	void buySmallPotion();
	void displayMarketItem(const QModelIndex &index);
	void displayPlayerItem(const QModelIndex &index);
	void equip();
};

#endif
