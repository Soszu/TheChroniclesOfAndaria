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

#ifndef FIGHT_H
#define FIGHT_H

#include <QtWidgets>

#include "Core/DataManager.h"
#include "Core/Containers/Enemy.h"
#include "Core/Containers/Player.h"
#include "Core/Game.h"
#include "Core/GameMaster.h"
#include "Game/CustomWidgets/MyTaskbar.h"

class GameMaster;

enum class FightResult : quint8 {
	Win,
	Lose,
	Retreat
};

class FightWindow : public QDialog {
	Q_OBJECT;
public:
	FightWindow(Player *player, Enemy *enemy, GameMaster *gameMaster);

public slots:
	void beginFight();

private:
	void enemyAttack();
	void playerAttack(int attack);
	void logEnemyAction(Enemy *enemy, const QString &text); //TODO CFiend czy argument enemy jest tutaj potrzebny, skoro mamy w obiekcie FightWindow?
	void logPlayerAction(Player *player, const QString &text); //TODO CFiend czy argument player jest tutaj potrzebny, skoro mamy w obiekcie FightWindow?

	Player *player_;
	Enemy *enemy_;
	GameMaster *gameMaster_;
	QTextBrowser *log;

	int currentEnemyHealth;
	MyTaskbar *enemyHealthBar;
	QLabel *enemyHealthLabel;

	MyTaskbar *playerHealthBar;
	QLabel *playerHealthLabel;

	QPushButton *largePotionButton;
	QPushButton *smallPotionButton;

private slots:
	void attackMagical();
	void attackMelee();
	void attackRanged();
	void retreat();
	void useLargePotion();
	void useSmallPotion();
};

#endif
