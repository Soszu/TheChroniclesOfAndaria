#include "Core/Containers/Item.h"

uint qHash(Item::Type type)
{
	return qHash(toUnderlying(type));
}

uint qHash(Item::Quality quality)
{
	return toUnderlying(quality);
}

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

const QHash <Item::Type, QString> & Item::itemTypes()
{
	static const QHash <Item::Type, QString> itemTypes_{
		{Item::Type::OneHanded, QObject::tr("One Handed")},
		{Item::Type::TwoHanded, QObject::tr("Two Handed")},
		{Item::Type::Armor, QObject::tr("Armor")},
		{Item::Type::Artifact, QObject::tr("Artifact")},
		{Item::Type::Helmet, QObject::tr("Helmet")},
		{Item::Type::Potion, QObject::tr("Potion")},
		{Item::Type::Scroll, QObject::tr("Scroll")},
		{Item::Type::Shield, QObject::tr("Shield")}};
	return itemTypes_;
}

const QHash <Item::Quality, QString> & Item::itemQualities()
{
	static const QHash <Item::Quality, QString> itemQualities_{
		{Item::Quality::Good, QObject::tr("Good")},
		{Item::Quality::Normal, QObject::tr("Normal")},
		{Item::Quality::NotApplicable, QObject::tr("NotApplicable")},
		{Item::Quality::Poor, QObject::tr("Poor")}};
	return itemQualities_;
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

QDataStream & operator<<(QDataStream &out, const Item &item)
{
	out //<< item.ID_
		 << item.name_
		 //<< item.statsModifiers_
		 << toUnderlying(item.type_)
		 << item.restrictions_
		 << item.value_
		 << toUnderlying(item.quality_);
	return out;
}

QDataStream & operator>>(QDataStream &in, Item &item)
{
	in //>> item.ID_
		>> item.name_
		//>> item.statsModifiers_
		>> toUnderlyingRef(item.type_)
		>> item.restrictions_
		>> item.value_
		>> toUnderlyingRef(item.quality_);
	return in;
}


