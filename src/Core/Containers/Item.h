#ifndef ITEM_H
#define ITEM_H

#include <QtGui>

//TODO CFiend to powinn być public Item { enum class Type };
enum ItemType {
	bronDwureczna,
	bronJednoreczna,
	tarcza,
	pancerz,
	helm,
	artefakt,
	mikstura
};

static const int NUMBER_OF_POSSIBLE_QUALITIES(4);

enum ItemQuality {
	notApplicable,
	poor,
	normal,
	good
};

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
	Item(QString name,
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
	     ItemQuality quality);

	QString name() const;
	ItemType type() const;
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
	ItemQuality quality() const;

	static const quint8 ArtifactLimit = 5;

private:
	QString name_;
	ItemType type_;
	int bonusMelee_;
	int bonusRanged_;
	int bonusMagical_;
	int bonusDefence_;
	int bonusPerception_;
	int bonusHitPoints_;
	int bonusRegeneration_;
	int restrictions_;
	int value_;
	bool isStrong_;
	ItemQuality quality_;
};

#endif
