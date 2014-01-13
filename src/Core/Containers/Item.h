#ifndef ITEM_H
#define ITEM_H

#include <QtGui>
#include "Core/Util/EnumHelpers.hpp"
#include "Core/Util/Serial.hpp"

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
	
	Item(QString name = QString("Default"),
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
	     Item::Quality quality = Quality::Normal);
	
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

	friend QDataStream & operator<<(QDataStream &out, const Item &item);
	friend QDataStream & operator>>(QDataStream &in, Item &item);
	
	static const quint8 ArtifactLimit = 5;
	static const QHash <Item::Type, QString> &itemTypes();
	static const QHash <Item::Quality, QString> &itemQualities();

protected:
	//UID ID_; 
	QString name_;
	//Player::CharacterStats statsModifiers_;
	Type type_;
	int bonusMelee_;
	int bonusRanged_;
	int bonusMagical_;
	int bonusDefence_;
	int bonusPerception_;
	int bonusHitPoints_;
	int bonusRegeneration_;
	int restrictions_;
	//QMap <Player::Class, bool> restrictions_; //QMap or QHash
	int value_;
	bool isStrong_;
	Item::Quality quality_;
};

uint qHash(Item::Type type);
uint qHash(Item::Quality quality);

#endif