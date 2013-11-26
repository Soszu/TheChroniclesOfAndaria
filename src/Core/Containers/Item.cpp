#include "Core/Containers/Item.h"

Item::Item(QString name,
	   ItemType type,
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
	   QColor fontColor)
	: name_(name),
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
	  fontColor_(fontColor)
{
}

QString Item::name() const
{
	return name_;
}

ItemType Item::type() const
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

QColor Item::fontColor() const
{
	return fontColor_;
}

int Item::bonusRegeneration() const
{
	return bonusRegeneration_;
}

int Item::bonusHitPoints() const
{
	return bonusHitPoints_;
}
