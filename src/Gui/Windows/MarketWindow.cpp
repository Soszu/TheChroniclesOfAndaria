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

#include "Gui/Windows/MarketWindow.h"

MarketWindow::MarketWindow(Player *player, PlayerWindow *playerWindow, const QList <const Item *> &wares)
	: player_(player), playerWindow_(playerWindow), wares_(wares)
{
	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	setWindowTitle("Bazar");

	QLabel *playerItemsLabel = new QLabel("Twoje przedmioty");
	playerItemList = new QListWidget();
	playerItemList->setToolTip(QString::fromUtf8("Lista posiadanych przedmiotów."));
	QLabel *availableWaresLabel = new QLabel(QString::fromUtf8("Przedmioty dostępne na bazarze"));
	wareList = new QListWidget();
	wareList->setToolTip(QString::fromUtf8("Lista towarów dostępnych do kupienia na bazarze."));
	populateListWidgets();

	QVBoxLayout *leftPartLayout = new QVBoxLayout();
	leftPartLayout->addWidget(playerItemsLabel);
	leftPartLayout->addWidget(playerItemList);
	leftPartLayout->addWidget(availableWaresLabel);
	leftPartLayout->addWidget(wareList);

	QHBoxLayout *upperPartLayout = new QHBoxLayout();
	upperPartLayout->addLayout(leftPartLayout);

	itemDescriptionWidget = new QTextBrowser();
	itemDescriptionWidget->setToolTip(QString::fromUtf8("opis aktualnie zaznaczonego przedmiotu."));
	upperPartLayout->addWidget(itemDescriptionWidget);
	mainLayout->addLayout(upperPartLayout);

	QLabel *smallPotionIcon = new QLabel();
	smallPotionIcon->setPixmap(IKONKA_MALA_MIKSTURA_ZDROWIA);
	smallPotionCountLabel = new QLabel(QString::number(player->equipment()->smallPotions()));
	smallPotionButton = new QPushButton(QString("Kup(") +
	                                    QString::number(CENA_MALEJ_MIKSTURY) +
	                                    QString(")"));
	smallPotionButton->setEnabled(player->gold() >= CENA_MALEJ_MIKSTURY);

	QLabel *largePotionIcon = new QLabel();
	largePotionIcon->setPixmap(IKONKA_DUZA_MIKSTURA_ZDROWIA);
	largePotionCountLabel = new QLabel(QString::number(player->equipment()->largePotions()));
	largePotionButton = new QPushButton(QString("Kup(") +
	                                    QString::number(CENA_DUZEJ_MIKSTURY) +
	                                    QString(")"));
	largePotionButton->setEnabled(player->gold() >= CENA_DUZEJ_MIKSTURY);

	buyButton = new QPushButton();
	buyButton->setToolTip(QString::fromUtf8("Zależnie od okoliczności, przycisk pozwala na kupno albo sprzedaż aktualnie zaznaczonego przedmiotu."));
	buyButton->setVisible(false);
	equipButton = new QPushButton();
	equipButton->setToolTip(QString::fromUtf8("Zależnie od okoliczności, przycisk pozwala na założenie albo zdjęcie aktualnie zaznaczonego przedmiotu z Twojej postaci."));
	equipButton->setVisible(false);
	confirmButton = new QPushButton("Ok");

	QHBoxLayout *bottomPartLayout = new QHBoxLayout();
	bottomPartLayout->addWidget(smallPotionIcon);
	bottomPartLayout->addWidget(smallPotionCountLabel);
	bottomPartLayout->addWidget(smallPotionButton);
	bottomPartLayout->addWidget(largePotionIcon);
	bottomPartLayout->addWidget(largePotionCountLabel);
	bottomPartLayout->addWidget(largePotionButton);
	bottomPartLayout->addStretch();
	bottomPartLayout->addWidget(buyButton);
	bottomPartLayout->addWidget(equipButton);
	bottomPartLayout->addWidget(confirmButton);
	mainLayout->addLayout(bottomPartLayout);

	connect(wareList, SIGNAL(clicked(const QModelIndex &)), this, SLOT(displayMarketItem(const QModelIndex &)));
	connect(playerItemList, SIGNAL(clicked(const QModelIndex &)), this, SLOT(displayPlayerItem(const QModelIndex &)));

	connect(smallPotionButton, SIGNAL(clicked()), this, SLOT(buySmallPotion()));
	connect(largePotionButton, SIGNAL(clicked()), this, SLOT(buyLargePotion()));
	connect(confirmButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(equipButton, SIGNAL(clicked()), this, SLOT(equip()));
	connect(buyButton, SIGNAL(clicked()), this, SLOT(buy()));
}

/**
 * @brief OknoBazaru::wypelnijListy	Wypełnia listę przedmiotów własnych i do kupienia odpowiednimi namemi.
 */
void MarketWindow::populateListWidgets()
{
	const Equipment *equipment = player_->equipment();
	const QList <const Item *> &backpack = equipment->backpack();

	playerItemList->clear();
	for (const Item *item : backpack)
		playerItemList->addItem(item->name());

	wareList->clear();
	for (const Item *item : wares_)
		wareList->addItem(item->name());
}

/**
 * @brief OknoBazaru::wyswietlOpisDlaGracza	Wyświetla opis przedmiotu z listy posiadanych przez gracza
 * @param element	dane wpisu, który został wybrany.
 */
void MarketWindow::displayPlayerItem(const QModelIndex &index)
{
	wareList->setCurrentRow(-1);
	buyButton->setText(sellText);
	buyButton->setVisible(true);
	buyButton->setEnabled(true);

	const Item *item = player_->equipment()->backpack().at(index.row());
	equipButton->setVisible(true);
	if (isEquipped(item, player_))
		equipButton->setText(unequipText);
	else
		equipButton->setText(equipText);

	equipButton->setEnabled(isPermitted(item, player_));
	generateDescription(item, player_, itemDescriptionWidget);
}

/**
 * @brief OknoBazaru::wyswietlOpisDlaBazaru	Wyświetla opis przedmiotu z listy dostępnych na bazarze.
 * @param element	dane wpisu, który został wybrany
 */
void MarketWindow::displayMarketItem(const QModelIndex& element)
{
	playerItemList->setCurrentRow(-1);
	const Item *item = wares_.at(element.row());

	equipButton->setVisible(false);
	buyButton->setVisible(true);
	buyButton->setText(buyText);
	buyButton->setEnabled(player_->gold() >= item->value());

	generateDescription(item, player_, itemDescriptionWidget);
}

/**
 * @brief OknoBazaru::kupMalaMiksture	Przeprowadza kupno małej mikstury zdrowia.
 */
void MarketWindow::buySmallPotion()
{
	Equipment *equipment = player_->equipment();
	equipment->setSmallPotions(equipment->smallPotions() + 1);
	player_->setGold(player_->gold() - CENA_MALEJ_MIKSTURY);

	playerWindow_->update();
	smallPotionCountLabel->setText(QString::number(player_->equipment()->smallPotions()));

	largePotionButton->setEnabled(player_->gold() >= CENA_DUZEJ_MIKSTURY);
	smallPotionButton->setEnabled(player_->gold() >= CENA_MALEJ_MIKSTURY);
}

/**
 * @brief OknoBazaru::kupDuzaMiksture	Przeprowadza kupno dużej mikstury zdrowia.
 */
void MarketWindow::buyLargePotion()
{
	Equipment *equipment = player_->equipment();
	equipment->setLargePotions(equipment->largePotions() + 1);
	player_->setGold(player_->gold() - CENA_DUZEJ_MIKSTURY);

	playerWindow_->update();
	smallPotionCountLabel->setText(QString::number(player_->equipment()->largePotions()));

	largePotionButton->setEnabled(player_->gold() >= CENA_DUZEJ_MIKSTURY);
	smallPotionButton->setEnabled(player_->gold() >= CENA_MALEJ_MIKSTURY);
}

/**
 * @brief OknoBazaru::zaloz	Odpowiednio zakłada lub zdejmuje aktualnie zaznaczony przedmiot z listy						przedmiotów gracza
 */
void MarketWindow::equip()
{
	const QList <const Item *> backpack = player_->equipment()->backpack();
	const Item *item = backpack.at(playerItemList->currentRow());

	if (equipButton->text() == unequipText) //NOTE do I really want string comparision? Maybe boolean flag?
		unequipItem(item, player_);
	else
		equipItem(item, player_);

	generateDescription(item, player_, itemDescriptionWidget);
	playerWindow_->update();

	if (isEquipped(item, player_))
		equipButton->setText(unequipText);
	else
		equipButton->setText(equipText);
}

/**
 * @brief OknoBazaru::kup	Kupuje lub sprzedaje aktualnie zaznaczony przedmiot z listy przedmiotów na					bazarze.
 */
void MarketWindow::buy()
{
	Equipment *equipment = player_->equipment();
	if (buyButton->text() == sellText) {
		const Item *item = equipment->backpack().at(playerItemList->currentRow());
		unequipItem(item, player_);

		equipment->removeItem(item);
		wares_.push_back(item);
		player_->setGold(player_->gold() + item->value() / 2);
	} else {
		const Item *item = wares_.at(wareList->currentRow());
		if (player_->gold() < item->value())
			return;
		equipment->addItem(item);

		wares_.removeAt(wares_.indexOf(item));
		player_->setGold(player_->gold() - item->value());
	}
	populateListWidgets();
	playerWindow_->update();
	largePotionButton->setEnabled(player_->gold() >= CENA_DUZEJ_MIKSTURY);
	smallPotionButton->setEnabled(player_->gold() >= CENA_MALEJ_MIKSTURY);
}
