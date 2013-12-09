#ifndef ITEM_H
#define ITEM_H

#include <QtGui>
#include <Core/Containers/EnumHelpers.hpp>
#include <Core/Containers/Serial.hpp>

static const int NUMBER_OF_POSSIBLE_QUALITIES(4);

static const quint8 LICZBA_RODZAJOW_PRZEDMIOTOW = 7;

static const QString RODZAJE_PRZEDMIOTOW[LICZBA_RODZAJOW_PRZEDMIOTOW] = {
	QString::fromUtf8("broń dwuręczna"),
	QString::fromUtf8("broń jednoręczna"),
	QString::fromUtf8("tarcza"),
	QString::fromUtf8("pancerz"),
	QString::fromUtf8("hełm"),
	QString::fromUtf8("artefakt"),
	QString::fromUtf8("mikstura"),
};

class Item {

public:
	
	enum class Type : quint8 {
		// Wearable items:
		TwoHanded,
		OneHanded,
		Shield,
		Armor,
		Helmet,
		Artifact,
		//One-time use items:  
		Potion,
		Scroll
		//and more
	};
	
	enum class Quality : quint8 {
		NotApplicable,
		Poor,
		Normal,
		Good
	};
	
	Item(QString name,
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
	     Item::Quality quality);
	
	Item(//UID ID,
	     QString name,
	     //CharacterStats statsModifiers,
	     Item::Type type,
	     //QMap <Player::Class, bool> restriction,
	     int value,
	     Item::Quality quality);

	//UID ID() const;
	QString name() const;
	Item::Type type() const;
	int bonusMelee() const;
	int bonusRanged() const;
	int bonusMagical() const;
	int bonusDefence() const;
	int bonusPerception() const;
	int bonusHitPoints() const;
	int bonusRegeneration() const;
	int restrictions() const;
	int value() const;
	bool isStrong() const;
	Item::Quality quality() const;

	friend QDataStream & operator>>(QDataStream &out, const Item &item);
	
	static const quint8 ArtifactLimit = 5;

protected:
	//const UID ID_; 
	QString name_;
	//const CharacterStats statsModifiers_;
	Type type_;
	int bonusMelee_;
	int bonusRanged_;
	int bonusMagical_;
	int bonusDefence_;
	int bonusPerception_;
	int bonusHitPoints_;
	int bonusRegeneration_;
	int restrictions_;
	//const QMap <Player::Class, bool> restrictions_; //QMap or QHash
	int value_;
	bool isStrong_;
	Item::Quality quality_;
};

#endif
