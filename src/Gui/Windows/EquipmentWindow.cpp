#include "Gui/Windows/EquipmentWindow.h"

EquipmentWindow::EquipmentWindow(Player *player, PlayerWindow *playerWindow)
	: player_(player), playerWindow_(playerWindow)
{
	Equipment *equipment = player->equipment();
	const QList <const Item *> &backpack = equipment->backpack();
	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	setWindowTitle("Ekwipunek");

	itemList_ = new QListWidget();
	itemList_->setToolTip(QString::fromUtf8("Lista posiadanych przedmiotów."));

	for (const Item *item : backpack)
		itemList_->addItem(item->name());

	itemDescription_ = new QTextBrowser();
	itemDescription_->setToolTip(QString::fromUtf8("opis aktualnie zaznaczonego przedmiotu."));
	QHBoxLayout *upperLayout = new QHBoxLayout();
	upperLayout->addWidget(itemList_);
	upperLayout->addWidget(itemDescription_);
	mainLayout->addLayout(upperLayout);

	buttonSmallPotion_ = new QPushButton();
	buttonSmallPotion_->setIcon(QIcon(IKONKA_MALA_MIKSTURA_ZDROWIA));
	buttonSmallPotion_->setText(QString("(") + QString::number(player->equipment()->smallPotions()) + QString(")"));
	if (player->equipment()->smallPotions() == 0)
		buttonSmallPotion_->setEnabled(false);

	buttonLargePotion_ = new QPushButton();
	buttonLargePotion_->setIcon(QIcon(IKONKA_DUZA_MIKSTURA_ZDROWIA));
	buttonLargePotion_->setText(QString("(") + QString::number(player->equipment()->largePotions()) + QString(")"));
	if (player->equipment()->largePotions() == 0)
		buttonLargePotion_->setEnabled(false);

	buttonEquip_ = new QPushButton(QString::fromUtf8("Załóż przedmiot"));
	buttonEquip_->setToolTip(QString::fromUtf8("Zależnie od okoliczności przycisk pozwala na założenie lub zdjęcie zaznaczonego przedmiotu z Twojej postaci."));
	buttonEquip_->setEnabled(false);
	buttonOk_ = new QPushButton("Ok");

	QHBoxLayout *lowerLayout = new QHBoxLayout();
	lowerLayout->addWidget(buttonSmallPotion_);
	lowerLayout->addWidget(buttonLargePotion_);
	lowerLayout->addStretch();
	lowerLayout->addWidget(buttonEquip_);
	lowerLayout->addWidget(buttonOk_);
	mainLayout->addLayout(lowerLayout);

	connect(itemList_, SIGNAL(clicked(const QModelIndex &)), this, SLOT(showDescription(const QModelIndex &)));

	connect(buttonSmallPotion_, SIGNAL(clicked()), this, SLOT(useLargePotion()));
	connect(buttonLargePotion_, SIGNAL(clicked()), this, SLOT(useSmallPotion()));
	connect(buttonOk_, SIGNAL(clicked()), this, SLOT(close()));
	connect(buttonEquip_, SIGNAL(clicked()), this, SLOT(equip()));
}

void EquipmentWindow::useSmallPotion()
{
	player_->equipment()->setLargePotions(player_->equipment()->largePotions() - 1);
	buttonLargePotion_->setText(QString("(") + QString::number(player_->equipment()->largePotions()) + QString(")"));
	if (player_->equipment()->largePotions() == 0)
		buttonLargePotion_->setEnabled(false);
	player_->setHealthCurrent(qMin(player_->healthMax(), player_->healthCurrent() + DZIALANIE_DUZYCH_POTOW));
	playerWindow_->update();
}

void EquipmentWindow::useLargePotion()
{
	player_->equipment()->setSmallPotions(player_->equipment()->smallPotions() - 1);
	buttonSmallPotion_->setText(QString("(") + QString::number(player_->equipment()->smallPotions()) + QString(")"));
	if (player_->equipment()->smallPotions() == 0)
		buttonSmallPotion_->setEnabled(false);
	player_->setHealthCurrent(qMin(player_->healthMax(), player_->healthCurrent() + DZIALANIE_MALYCH_POTOW));
	playerWindow_->update();
}

/**
 * @brief OknoEkwipunek::wyswietlOpis	Wyświetla opis aktualnie zaznaczonego elementu na liscie posiadanych						przedmiotow
 * @param element	dane elementu z listy przedmiotow.
 */
void EquipmentWindow::showDescription(const QModelIndex& index)
{
	const Item *item = player_->equipment()->backpack().at(index.row());
	generateDescription(item, player_, itemDescription_);

	if (isPermitted(item, player_)) {
		buttonEquip_->setEnabled(true);
		if (isEquipped(item, player_))
			buttonEquip_->setText("Zdejmij");
		else
			buttonEquip_->setText(QString::fromUtf8("Załóż"));
	} else {
		buttonEquip_->setText(QString::fromUtf8("Załóż"));
		buttonEquip_->setEnabled(false);
	}
}

/**
 * @brief OknoEkwipunek::zaloz		Zakłada lub zdejmuje aktualnie zaznaczony przedmiot.
 */
void EquipmentWindow::equip()
{
	const Item *item = player_->equipment()->backpack().at(itemList_->currentRow());

	if (isEquipped(item, player_)) {
		unequipItem(item, player_);
		buttonEquip_->setText(QString::fromUtf8("Załóż"));
	} else {
		equipItem(item, player_);
		buttonEquip_->setText("Zdejmij");
	}
	playerWindow_->update();
	generateDescription(item, player_, itemDescription_);
}
