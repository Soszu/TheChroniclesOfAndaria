#ifndef FIGHT_H
#define FIGHT_H

#include <QtWidgets>

#include "Core/Containers/Enemy.h"
#include "Core/Containers/Player.h"
#include "Core/Game.h"
#include "Core/GameMaster.h"
#include "Gui/CustomWidgets/MyTaskbar.h"

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
