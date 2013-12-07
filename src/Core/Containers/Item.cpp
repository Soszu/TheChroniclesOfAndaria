#include "Core/Containers/Item.h"

Item::Item(QString name,
	   Item::Type type,
	   int bonusMelee,
	   int bonusRanged,
	   int bonusMagical,
	   int bonusDefence,
	   int bonusPerception,
	   int bonusHitPoints,
	   int bonusRegeneration,
	   int restrictions,
	   int value,
	   bool isStrong,
	   Item::Quality quality)
	: name_(name),
	  type_(type),
	  bonusMelee_(bonusMelee),
	  bonusRanged_(bonusRanged),
	  bonusMagical_(bonusMagical),
	  bonusDefence_(bonusDefence),
	  bonusPerception_(bonusPerception),
	  bonusHitPoints_(bonusHitPoints),
	  bonusRegeneration_(bonusRegeneration),
	  restrictions_(restrictions),
	  value_(value),
	  isStrong_(isStrong),
	  quality_(quality)
{
}

Item::Item(//UID ID,
	     QString name,
	     //CharacterStats statsModifiers,
	     Item::Type type,
	     //QMap <Player::Class, bool> restriction,
	     int value,
	     Item::Quality quality)
	: //ID_(ID),
	  name_(name),
	  //statsModifiers_(statsModifiers),
	  type_(type),
	  //restrictions_(restrictions),
	  value_(value),
	  quality_(quality)
{
}

// UID Item::ID() const
// {
// 	return ID_;
// }

QString Item::name() const
{
	return name_;
}

Item::Type Item::type() const
{
	return type_;
}

int Item::bonusMelee() const
{
	return bonusMelee_;
}

int Item::bonusRanged() const
{
	return bonusRanged_;
}

int Item::bonusMagical() const
{
	return bonusMagical_;
}

int Item::bonusDefence() const
{
	return bonusDefence_;
}

int Item::bonusPerception() const
{
	return bonusPerception_;
}

int Item::restrictions() const
{
	return restrictions_;
}

int Item::value() const
{
	return value_;
}

bool Item::isStrong() const
{
	return isStrong_;
}

Item::Quality Item::quality() const
{
	return quality_;
}

int Item::bonusRegeneration() const
{
	return bonusRegeneration_;
}

int Item::bonusHitPoints() const
{
	return bonusHitPoints_;
}
