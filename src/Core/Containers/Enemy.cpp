#include "Core/Containers/Enemy.h"

Enemy::Enemy(QString name, QString pictureName, int attackMin, int attackMax, int defence, int perception, int healthMax, Prize *prize)
	: name_(name),
	  pictureName_(pictureName),
	  attackMin_(attackMin),
	  attackMax_(attackMax),
	  defence_(defence),
	  perception_(perception),
	  healthMax_(healthMax),
	  prize_(prize)
{
}

QString Enemy::name() const
{
	return name_;
}

QString Enemy::pictureName() const
{
	return pictureName_;
}

int Enemy::attackMin() const
{
	return attackMin_;
}

int Enemy::attackMax() const
{
	return attackMax_;
}

int Enemy::defence() const
{
	return defence_;
}

int Enemy::perception() const
{
	return perception_;
}

int Enemy::healthMax() const
{
	return healthMax_;
}

Prize * Enemy::prize() const
{
	return prize_;
}
