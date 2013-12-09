#include <Core/Containers/ItemWearable.h>

ItemWearable::ItemWearable(QString name,
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
	   bool isComplex)
	: Item(name, 
			 type, 
			 bonusMelee,
			 bonusRanged, 
			 bonusMagical, 
			 bonusDefence, 
			 bonusPerception, 
			 bonusHitPoints, 
			 bonusRegeneration,
			 restrictions,
			 value,
			 isStrong,
			 quality),
	  isComplex_(isComplex)
{
}

ItemWearable::ItemWearable(//UID ID,
	     QString name,
	     //CharacterStats statsModifiers,
	     Item::Type type,
	     //QMap <Player::Class, bool> restriction,
	     int value,
	     Item::Quality quality,
	     bool isComplex)
	: Item(//ID_(ID),
			name,
			//statsModifiers_(statsModifiers),
			type,
			//restrictions_(restrictions),
			value,
			quality),
	  isComplex_(isComplex)
{
}


bool ItemWearable::isComplex() const
{
	return isComplex_;
}
