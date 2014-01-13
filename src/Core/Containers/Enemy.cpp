#include "Core/Containers/Enemy.h"

Enemy::Enemy(QString name, 
				 QString pictureName, 
				 qint8 attackMin,
				 //qint8 attackRange, NOTE change this after applying new mechanics
				 qint8 attackMax, 
				 qint8 defence, 
				 qint8 perception, 
				 qint8 healthMax,
				 AttackType defaultAttack,
				 Prize *prize)
	: FightParticipant(name, pictureName, healthMax),
	  baseStats_({healthMax, 
	              defence, 
	              perception, 
	              {{AttackType::Melee, {attackMin, attackMax - attackMin}}, 
	               {AttackType::Magical, {attackMin, attackMax - attackMin}}, 
	               {AttackType::Ranged, {attackMin, attackMax - attackMin}}}}),
	  defaultAttack_(defaultAttack),
	  prize_(prize)
{
}

QString Enemy::name() const
{
	return name_;
}

QString Enemy::pictureName() const
{
	return imageFile_;
}

int Enemy::attackMin() const
{
	return baseStats_.attacks_[defaultAttack_].first;
}

int Enemy::attackRange() const
{
	return baseStats_.attacks_[defaultAttack_].second;
}

int Enemy::attackMax() const
{
	return baseStats_.attacks_[defaultAttack_].second + baseStats_.attacks_[defaultAttack_].first;
}

int Enemy::defence() const
{
	return baseStats_.defence_;
}

int Enemy::perception() const
{
	return baseStats_.perception_;
}

int Enemy::healthMax() const
{
	return baseStats_.healthMax_;
}

Prize * Enemy::prize() const
{
	return prize_;
}
