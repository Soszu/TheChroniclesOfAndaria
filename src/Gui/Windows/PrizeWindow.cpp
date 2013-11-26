#include "Core/Operations/EquipmentManagement.h"
#include "Gui/Windows/PrizeWindow.h"

PrizeWindow::PrizeWindow(Player *player, Prize *prize, const QList <const Item *> &prizeItems, GameCycle *gameCycle, bool isEndOfTurn)
	: player_(player), prize_(prize), prizeItems_(prizeItems), gameCycle_(gameCycle), isEndOfTurn_(isEndOfTurn)
{
	QVBoxLayout *mainLayout = new QVBoxLayout(this);

	if (player_->level() < MaximumLevel && player_->experience() >= GRANICE_POZIOMOW[player_->level()]) {
		player_->setLevel(player_->level() + 1);
		isLevelUp = true;
	} else {
		isLevelUp = false;
	}

	QLabel *itemListLabel = new QLabel(QString::fromUtf8("Otrzymujesz następujące przedmioty:"));
	itemListWidget = new QListWidget();
	for (int i = 0; i < prizeItems_.size(); ++i)
		itemListWidget->addItem(prizeItems_[i]->name());

	QLabel *prizeLabel = new QLabel(QString::fromUtf8("Otrzymujesz również:"));
	prizeDescriptionWidget = new QTextBrowser();
	prizeDescriptionWidget->setText(prizeDescription());

	QVBoxLayout *descriptionLayoutLeft = new QVBoxLayout();
	descriptionLayoutLeft->addWidget(itemListLabel);
	descriptionLayoutLeft->addWidget(itemListWidget);
	descriptionLayoutLeft->addWidget(prizeLabel);
	descriptionLayoutLeft->addWidget(prizeDescriptionWidget);

	itemDescriptionWidget = new QTextBrowser();

	QHBoxLayout *descriptionLayout = new QHBoxLayout();
	descriptionLayout->addLayout(descriptionLayoutLeft);
	descriptionLayout->addWidget(itemDescriptionWidget);
	mainLayout->addLayout(descriptionLayout);

	QHBoxLayout *levelUpLayout = new QHBoxLayout();
	QLabel *levelUpLabel = new QLabel(QString::fromUtf8("Awansowałeś na kolejny poziom, przydziel punkty:"));
	levelUpLayout->addWidget(levelUpLabel);
	for (int i = 0; i < AttributePointsPerLevel; ++i) {
		attributePointChoice.push_back(new QComboBox());
		for (int j = 0; j < LICZBA_ATRYBOTOW_DO_AWANSU; ++j)
			attributePointChoice[i]->addItem(MOZLIWE_AWANSE[j]);
		attributePointChoice[i]->setVisible(isLevelUp);
		levelUpLayout->addWidget(attributePointChoice[i]);
	}
	levelUpLayout->addStretch();

	levelUpLabel->setVisible(isLevelUp);
	mainLayout->addLayout(levelUpLayout);

	QHBoxLayout *buttonLayout = new QHBoxLayout();
	QPushButton *okButton = new QPushButton("Ok");
	buttonLayout->addStretch();
	buttonLayout->addWidget(okButton);
	mainLayout->addLayout(buttonLayout);

	connect(okButton, SIGNAL(clicked()), this, SLOT(confirm()));
	connect(itemListWidget, SIGNAL(clicked(const QModelIndex &)), this, SLOT(displayItemDescription(const QModelIndex &)));
}

/**
 * @brief OknoNagrody::zwiekszAtrybut	Zwiększa odpowiedni atrybut w statystykach gracza.
 * @param indeks	wartosc enumeratora atrybut (opisany w gra.h)
 */
void PrizeWindow::increaseAttribute(atrybut index)
{
	switch (index) {
	case Awrecz:
		player_->setAttackMelee(player_->attackMelee() + 1);
		break;
	case Adystansowy:
		player_->setAttackRanged(player_->attackRanged() + 1);
		break;
	case Amagiczny:
		player_->setAttackMagical(player_->attackMagical() + 1);
		break;
	case defence:
		player_->setDefence(player_->defence() + 1);
		break;
	case perception:
		player_->setPerception(player_->perception() + 1);
		break;
	default:
		break;
	}
}

/**
 * @brief OknoNagrody::generujOpisNagrody	Generuje opis nagrody, zapisanej w atrybucie prywatnym klasy
 * @return	QString z opisem nagrody
 */
QString PrizeWindow::prizeDescription() const
{
	QString description;

	if (prize_->experience() != 0)
		description += QString::fromUtf8("Zdobyte doświadczenie: ") + QString::number(prize_->experience());

	if (prize_->gold() != 0)
		description += QString::fromUtf8("\n\nZdobyte złoto: ") + QString::number(prize_->gold()) + QString("\n\n");

	for (int i = 0; i < KingdomCount; ++i) {
		int reputationChange = prize_->reputation()[i];
		if (reputationChange > 0)
			description += QString("+");
		if (reputationChange < 0)
			description += QString("-");
		if (reputationChange != 0)
			description += QString::number(reputationChange) + QString(" reputacja (") + KingdomString[i] +  QString(")\n");
	}

	return description;
}

/**
 * @brief OknoNagrody::rozpocznij	Ustala czy jednocześnie nastąpił awans oraz wyświetla okno.
 */
void PrizeWindow::displayPrizeWindow()
{
	if (isLevelUp) {
		QMessageBox::information(
			this,
			QString("Awans"),
			QString::fromUtf8("Awansowałeś na kolejny poziom.\nPamiętaj o rozdzieleniu punktów.")
		);
	}
	show();
}

/**
 * @brief OknoNagrody::wyswietlOpis	Wyświetla opis zdobytego przedmiotu.
 * @param element	aktualnie zaznaczony element
 */
void PrizeWindow::displayItemDescription(const QModelIndex &index)
{
	const Item *item = prizeItems_[index.row()];
	generateDescription(item, player_, itemDescriptionWidget);
}

/**
 * @brief OknoNagrody::zakoncz	Powiększa wybrane atrybuty i kończy turę.
 */
void PrizeWindow::confirm()
{
	if (isLevelUp) {
		for (int i = 0; i < AttributePointsPerLevel; ++i)
			increaseAttribute((atrybut)attributePointChoice[i]->currentIndex());
		player_->setHealthMax(player_->healthMax() + HealthIncreasePerLevel);
		player_->setHealthCurrent(player_->healthCurrent() + HealthIncreasePerLevel);
	}
	if (isEndOfTurn_)
		gameCycle_->endTurn();
	close();
}
