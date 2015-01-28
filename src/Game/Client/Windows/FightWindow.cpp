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

#include "Game/Windows/FightWindow.h"

FightWindow::FightWindow(Player *player, Enemy *enemy, GameMaster *gameMaster)
	: player_(player), enemy_(enemy), gameMaster_(gameMaster)
{
	setWindowTitle("Walka");

//---ENEMY
	QHBoxLayout *mainLayout = new QHBoxLayout(this);
	QVBoxLayout *enemyPartLayout = new QVBoxLayout();
	QVBoxLayout *playerPartLayout = new QVBoxLayout();

	mainLayout->addLayout(enemyPartLayout);
	mainLayout->addLayout(playerPartLayout);

	QLabel *enemyImage = new QLabel();
	enemyImage->setAlignment(Qt::AlignCenter);
	QString enemyPixmapPath = Path::EnemiesPrefix + enemy->pictureName();
	enemyImage->setPixmap(DataManager::pixmap(enemyPixmapPath));
	enemyPartLayout->addWidget(enemyImage);

	QLabel *enemyNameLabel = new QLabel(enemy->name());
	enemyPartLayout->addWidget(enemyNameLabel);

	enemyHealthBar = new MyTaskbar(1, Qt::darkRed);
	currentEnemyHealth = enemy->maxHealth();
	enemyHealthLabel = new QLabel(QString::number(currentEnemyHealth) + "/" + QString::number(enemy->maxHealth()));

	QHBoxLayout *enemyHealthLayout = new QHBoxLayout();
	enemyHealthLayout->addWidget(enemyHealthBar);
	enemyHealthLayout->addWidget(enemyHealthLabel);
	enemyPartLayout->addLayout(enemyHealthLayout);

	QLabel *enemyAttackIcon = new QLabel();
	enemyAttackIcon->setPixmap(DataManager::pixmap(Path::IconAttack));
	QLabel *enemyAttackLabel = new QLabel(QString::number(enemy->attackMin()) + " - " + QString::number(enemy->attackMax()));
	QLabel *enemyDefenceIcon = new QLabel();
	enemyDefenceIcon->setPixmap(DataManager::pixmap(Path::IconDefence));
	QLabel *enemyDefenceLabel = new QLabel(QString::number(enemy->defence()));
	QLabel *enemyPerceptionIcon = new QLabel();
	enemyPerceptionIcon->setPixmap(DataManager::pixmap(Path::IconPerception));
	QLabel *enemyPerceptionLabel = new QLabel(QString::number(enemy->perception()));

	QHBoxLayout *enemyInformationLayout = new QHBoxLayout();
	enemyInformationLayout->addWidget(enemyAttackIcon);
	enemyInformationLayout->addWidget(enemyAttackLabel);
	enemyInformationLayout->addWidget(enemyDefenceIcon);
	enemyInformationLayout->addWidget(enemyDefenceLabel);
	enemyInformationLayout->addWidget(enemyPerceptionIcon);
	enemyInformationLayout->addWidget(enemyPerceptionLabel);
	enemyInformationLayout->addStretch();
	enemyPartLayout->addLayout(enemyInformationLayout);

//---PLAYER
	log = new QTextBrowser();
	log->insertPlainText(QString::fromUtf8("Rozpoczęto walkę\n"));
	playerPartLayout->addWidget(log);

	QLabel *playerNameLabel = new QLabel(player->name());

	playerHealthBar = new MyTaskbar((qreal)player->currentHealth() / player->maxHealth(), player->regeneration() / player->maxHealth(), Qt::red, Qt::green);
	playerHealthLabel = new QLabel(QString::number(player->currentHealth()) + "/" + QString::number(player->maxHealth()));
	QHBoxLayout *playerHealthLayout = new QHBoxLayout();
	playerHealthLayout->addWidget(playerNameLabel);
	playerHealthLayout->addWidget(playerHealthBar);
	playerHealthLayout->addWidget(playerHealthLabel);
	playerPartLayout->addLayout(playerHealthLayout);

	QLabel *playerDefenceIcon = new QLabel();
	playerDefenceIcon->setPixmap(DataManager::pixmap(Path::IconDefence));
	QLabel *playerDefenceLabel = new QLabel(QString::number(player->defence()));

	QLabel *playerPerceptionIcon = new QLabel();
	playerPerceptionIcon->setPixmap(DataManager::pixmap(Path::IconPerception));
	QLabel *playerPerceptionLabel = new QLabel(QString::number(player->perception()));
	QHBoxLayout *playerInformationLayout = new QHBoxLayout();
	playerInformationLayout->addWidget(playerDefenceIcon);
	playerInformationLayout->addWidget(playerDefenceLabel);
	playerInformationLayout->addWidget(playerPerceptionIcon);
	playerInformationLayout->addWidget(playerPerceptionLabel);
	playerInformationLayout->addStretch();
	playerPartLayout->addLayout(playerInformationLayout);

	QPushButton *attackMeleeButton = new QPushButton();
	attackMeleeButton->setIcon(DataManager::pixmap(Path::IconMelee));
	attackMeleeButton->setText(QString::number(player->attackMelee()) +
	                           QString(" - ") +
	                           QString::number(PlayerDice + player->attackMelee()));

	QPushButton *attackRangedButton = new QPushButton();
	attackRangedButton->setIcon(DataManager::pixmap(Path::IconRanged));
	attackRangedButton->setText(QString::number(player->attackRanged()) +
	                            QString(" - ") +
	                            QString::number(PlayerDice + player->attackRanged()));

	QPushButton *attackMagicalButton = new QPushButton();
	attackMagicalButton->setIcon(DataManager::pixmap(Path::IconMagic));
	attackMagicalButton->setText(QString::number(player->attackMagical()) +
	                             QString(" - ") +
	                             QString::number(PlayerDice + player->attackMagical()));

	QHBoxLayout *playerAttacksLayout = new QHBoxLayout();
	playerAttacksLayout->addWidget(attackMeleeButton);
	playerAttacksLayout->addWidget(attackRangedButton);
	playerAttacksLayout->addWidget(attackMagicalButton);
	playerPartLayout->addLayout(playerAttacksLayout);

	smallPotionButton = new QPushButton();
	smallPotionButton->setIcon(DataManager::pixmap(Path::IconSmallHealthMixture));
	smallPotionButton->setText(QString("(") + QString::number(player->equipment()->smallPotions()) + QString(")"));
	if (player->equipment()->smallPotions() == 0)
		smallPotionButton->setEnabled(false);
	largePotionButton = new QPushButton();
	largePotionButton->setIcon(DataManager::pixmap(Path::IconBigHealthMixture));
	largePotionButton->setText(QString("(") + QString::number(player->equipment()->largePotions()) + QString(")"));
	if (player->equipment()->largePotions() == 0)
		largePotionButton->setEnabled(false);
	QPushButton *retreatButton = new QPushButton("Uciekaj");
	QHBoxLayout *playerButtonsLayout = new QHBoxLayout();
	playerButtonsLayout->addWidget(smallPotionButton);
	playerButtonsLayout->addWidget(largePotionButton);
	playerButtonsLayout->addWidget(retreatButton);
	playerPartLayout->addLayout(playerButtonsLayout);

	connect(attackMeleeButton, SIGNAL(clicked()), this, SLOT(attackMelee()));
	connect(attackRangedButton, SIGNAL(clicked()), this, SLOT(attackRanged()));
	connect(attackMagicalButton, SIGNAL(clicked()), this, SLOT(attackMagical()));
	connect(smallPotionButton, SIGNAL(clicked()), this, SLOT(useSmallPotion()));
	connect(largePotionButton, SIGNAL(clicked()), this, SLOT(useLargePotion()));
	connect(retreatButton, SIGNAL(clicked()), this, SLOT(retreat()));
}

/**
 * @brief Walka::ruchEnemya	Wykonuje atak przeciwnika, a po nim sprawdza czy koniec walki
 */
void FightWindow::enemyAttack()
{
	int attackPower = qrand() % (enemy_->attackMax() + 1 - enemy_->attackMin()) + enemy_->attackMin();

	logEnemyAction(enemy_, QString::fromUtf8("atakuje z siłą ") + QString::number(attackPower));
	log->verticalScrollBar()->setSliderPosition(log->verticalScrollBar()->maximum());

	int damageReceived = qMax(attackPower - player_->defence(), 0);
	log->insertPlainText(QString::fromUtf8("Zadane obrażenia: ") + QString::number(damageReceived) + QString("\n"));

	player_->setHealthCurrent(qMax(player_->currentHealth() - damageReceived, 0));
	playerHealthLabel->setText(QString::number(player_ ->currentHealth()) + "/" + QString::number(player_->maxHealth()));
	playerHealthBar->fillFirst((qreal)player_->currentHealth() / player_->maxHealth());
	this->repaint();

	if (player_->currentHealth() == 0) {
		QString text(enemy_->name() + QString::fromUtf8(" wygrał walkę"));
		QMessageBox::information(
			this,
			QString::fromUtf8("Zakończono walkę"),
			text
		);
		qDebug() << player_->name() << "przegrywa walke.";
		close();
		gameMaster_->endFight(enemy_, FightResult::Lose);
	}
}

/**
 * @brief Walka::atakGracza	Wykonuje atak gracza z daną siłą, a po nim sprawdza czy koniec walki
 * @param atak		siła z jaką atakuje gracz
 */
void FightWindow::playerAttack(int attack)
{
	int damageCaused = qMax(attack - enemy_->defence(), 0);

	log->insertPlainText(QString::fromUtf8("Zadane obrażenia: ") + QString::number(damageCaused) + QString("\n"));
	log->verticalScrollBar()->setSliderPosition(log->verticalScrollBar()->maximum());

	currentEnemyHealth = qMax(0, currentEnemyHealth - damageCaused);
	enemyHealthLabel->setText(QString::number(currentEnemyHealth) + "/" + QString::number(enemy_->maxHealth()));
	enemyHealthBar->fill((qreal)currentEnemyHealth / enemy_->maxHealth());
	this->repaint();

	if(currentEnemyHealth == 0) {
		QString text(player_->name() + QString::fromUtf8(" wygrał walkę"));
		QMessageBox::information(
			this,
			QString::fromUtf8("Zakończono walkę"),
			text
		);
		qDebug() << player_->name() << "Wygrywa walke.";
		close();
		gameMaster_->endFight(enemy_, FightResult::Win);
	} else {
		enemyAttack();
	}
}

/**
 * @brief Walka::wpisGracza	Wpisuje czynność wykonaną przez gracza podaną jako tekst do loga.
 * @param gracz		Gracz, który wykonuje działanie.
 * @param tekst		tekst będący opisem czynności
 */
void FightWindow::logPlayerAction(Player *player, const QString &text)
{
	log->setTextColor(QColor(Qt::green));
	log->setFontWeight(QFont::Bold);
	log->insertPlainText(QString("\n") + player->name());
	log->setFontWeight(QFont::Normal);
	log->setTextColor(QColor(Qt::black));
	log->insertPlainText(QString(" ") + text + "\n");
	log->verticalScrollBar()->setSliderPosition(log->verticalScrollBar()->maximum());

}

/**
 * @brief Walka::wpisEnemya	Wpisuje czynność wykonaną przez przeciwnika podaną jako tekst do loga.
 * @param przeciwnik	Enemy który wykonuje działanie.
 * @param tekst		tekst będący opisem czynności
 */
void FightWindow::logEnemyAction(Enemy *enemy, const QString &text)
{
	log->setTextColor(QColor(Qt::red));
	log->setFontWeight(QFont::Bold);
	log->insertPlainText(QString("\n") + enemy->name());
	log->setFontWeight(QFont::Normal);
	log->setTextColor(QColor(Qt::black));
	log->insertPlainText(QString(" ") + text + "\n");
	log->verticalScrollBar()->setSliderPosition(log->verticalScrollBar()->maximum());
}

/**
 * @brief Walka::rozpocznij	Rozpoczyna walkę wyświetlając informacje o rozpoczynającym.
 */
void FightWindow::beginFight()
{
	show();
	QMessageBox::information(
		this,
		QString::fromUtf8("Rozpoczynający"),
		enemy_->perception() > player_->perception() ?
			QString::fromUtf8("Walkę rozpoczyna ") + enemy_->name() + QString(".") :
			QString::fromUtf8("Walkę rozpoczyna ") + player_->name() + QString(".")
	);

	if (enemy_->perception() > player_->perception())
		enemyAttack();
}

/**
 * @brief Walka::atakWrecz	Zleca wykonanie ataku wręcz, jako następne działanie gracza.
 */
void FightWindow::attackMelee()
{
	int attackPower = qrand() % PlayerDice + player_->attackMelee() + 1;
	logPlayerAction(player_, QString::fromUtf8(" atakuje wręcz z siłą ") + QString::number(attackPower));
	playerAttack(attackPower);
}

/**
 * @brief Walka::atakDystansowy		Zleca wykonanie ataku bronią dystansową, jako następne działanie gracza.
 */
void FightWindow::attackRanged()
{
	int attackPower = qrand() % PlayerDice + player_->attackRanged() + 1;
	logPlayerAction(player_, QString::fromUtf8(" atakuje bronią dystansową z siłą ") + QString::number(attackPower));
	playerAttack(attackPower);
}

/**
 * @brief Walka::atakMagiczny		Zleca wykonanie ataku magicznego, jako następne działanie gracza.
 */
void FightWindow::attackMagical()
{
	int attackPower = qrand() % PlayerDice + player_->attackMagical() + 1;
	logPlayerAction(player_, QString::fromUtf8(" atakuje magicznie z siłą ") + QString::number(attackPower));
	playerAttack(attackPower);
}

/**
 * @brief Walka::uciekaj	Wykonuje ucieczke gracza z walki i zamyka okno.
 */
void FightWindow::retreat()
{
	qDebug() << player_->name() << "Ucieka z pola walki.";
	close();
	gameMaster_->endFight(enemy_, FightResult::Retreat);
}

/**
 * @brief Walka::uzyjDuzejMikstury	Zleca użycie dużej mikstury zdrowia.
 */
void FightWindow::useLargePotion()
{
	logPlayerAction(player_, QString::fromUtf8("używa dużej mikstury zdrowia."));

	player_->equipment()->setLargePotions(player_->equipment()->largePotions() - 1);
	largePotionButton->setText(QString("(") + QString::number(player_->equipment()->largePotions()) + QString(")"));
	if (player_->equipment()->largePotions() == 0)
		largePotionButton->setEnabled(false);
	player_->setHealthCurrent(qMin(player_->maxHealth(), player_->currentHealth() + (int)DZIALANIE_DUZYCH_POTOW));
	enemyAttack();
}

/**
 * @brief Walka::uzyjMalejMikstury	Zleca użycie małej mikstury zdrowia.
 */
void FightWindow::useSmallPotion()
{
	logPlayerAction(player_, QString::fromUtf8("używa małej mikstury zdrowia."));

	player_->equipment()->setSmallPotions(player_->equipment()->smallPotions() - 1);
	smallPotionButton->setText(QString("(") + QString::number(player_->equipment()->smallPotions()) + QString(")"));
	if (player_->equipment()->smallPotions() == 0)
		smallPotionButton->setEnabled(false);
	player_->setHealthCurrent(qMin(player_->maxHealth(), player_->currentHealth() + (int)DZIALANIE_MALYCH_POTOW));
	enemyAttack();
}
