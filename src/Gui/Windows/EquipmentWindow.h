#ifndef EQUIPMENTWINDOW_H
#define EQUIPMENTWINDOW_H

#include <QtWidgets>

#include "Core/Containers/Item.h"
#include "Core/Containers/Player.h"
#include "Core/Operations/EquipmentManagement.h"
#include "Gui/PlayerWindow.h"

class PlayerWindow;

class EquipmentWindow : public QDialog {
	Q_OBJECT;
public:
	EquipmentWindow(Player *player, PlayerWindow *playerWindow);

private:
	Player *player_;
	PlayerWindow *playerWindow_;
	QTextBrowser *itemDescription_;
	QListWidget *itemList_;

	QPushButton *buttonEquip_;
	QPushButton *buttonOk_;
	QPushButton *buttonLargePotion_;
	QPushButton *buttonSmallPotion_;;

private slots:
	void equip();
	void showDescription(const QModelIndex &index);
	void useLargePotion();
	void useSmallPotion();
};

#endif
