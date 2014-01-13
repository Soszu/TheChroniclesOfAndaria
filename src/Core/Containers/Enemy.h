#ifndef ENEMY_H
#define ENEMY_H

#include "Core/Containers/Prize.h"
#include "FightParticipant.h"

class Enemy : public FightParticipant {

public:
	
	static const size_t NUMBER_OF_ENEMIES_GROUPS = 5;
	
	Enemy(QString name, 
			QString pictureName, 
			qint8 attackMin,
			//qint8 attackRange, NOTE change this after applying new mechanics
			qint8 attackMax, 
			qint8 defence, 
			qint8 perception, 
			qint8 healthMax,
			AttackType defaultAttack,
			Prize *prize);

	QString name() const;
	QString pictureName() const;
	int attackMin() const;
	int attackRange() const;
	int attackMax() const;
	int defence() const;
	int perception() const;
	int healthMax() const;
	Prize * prize() const;

protected:
	BattleStats baseStats_;
	AttackType defaultAttack_;
	Prize *prize_; //TODO CFiend const Prize * ?
};

#endif
