#ifndef ITEAM_WEARABLE_H
#define ITEAM_WEARABLE_H

#include <Core/Containers/Item.h>

class ItemWearable : public Item {
public:
	ItemWearable(QString name = QString("Default"),
	     Item::Type type = Type::OneHanded,
	     int bonusMelee = 0,
	     int bonusRanged = 0,
	     int bonusMagical = 0,
	     int bonusDefence =  0,
	     int bonusPerception = 0,
	     int bonusHitPoints  = 0,
	     int bonusRegeneration = 0,
	     int restrictions = 0,
	     int value = 1,
	     bool isStrong = false,
	     Item::Quality quality = Quality::Normal,
	     bool isComplex = false);
	
	ItemWearable(//UID ID,
					 QString name,
					 //CharacterStats statsModifiers,
					 Item::Type type,
					 //QMap <Player::Class, bool> restriction,
					 int value,
					 Item::Quality quality,
					 bool isComplex);
	
	bool isComplex() const;
	
	friend QDataStream & operator<<(QDataStream &out, const ItemWearable &itemWearable);
	friend QDataStream & operator>>(QDataStream &in, ItemWearable &itemWearable);
protected:
	const bool isComplex_;
};


#endif