#ifndef ITEAM_WEARABLE_H
#define ITEAM_WEARABLE_H

#include <Core/Containers/Item.h>

class ItemWearable : public Item {
public:
	ItemWearable(QString name,
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
					 Item::Quality quality,
					 bool isComplex);
	
	ItemWearable(//UID ID,
					 QString name,
					 //CharacterStats statsModifiers,
					 Item::Type type,
					 //QMap <Player::Class, bool> restriction,
					 int value,
					 Item::Quality quality,
					 bool isComplex);
	
	bool isComplex() const;
	
protected:
	const bool isComplex_;
};


#endif