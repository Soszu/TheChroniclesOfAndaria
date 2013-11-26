#ifndef ENEMY_H
#define ENEMY_H

#include "Core/Containers/Prize.h"

class Enemy {

public:
	Enemy(QString name, QString pictureName, int attackMin, int attackMax, int defence, int perception, int healthMax, Prize *prize);

	QString name() const;
	QString pictureName() const;
	int attackMin() const;
	int attackMax() const;
	int defence() const;
	int perception() const;
	int healthMax() const;
	Prize * prize() const;

private:
	QString name_;
	QString pictureName_;
	int attackMin_;
	int attackMax_;
	int defence_;
	int perception_;
	int healthMax_;
	Prize *prize_; //TODO CFiend const Prize * ?
};

#endif
