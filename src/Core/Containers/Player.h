#ifndef PLAYER_H
#define PLAYER_H

#include "Core/Containers/Equipment.h"
#include "Core/Containers/Field.h"
#include "Core/Containers/Quest.h"

struct CharacterStats {
	int healthMax;
	int regeneration;
	int attackMelee;
	int attackRanged;
	int attackMagical;
	int defence;
	int perception;
};

//TODO CFiend porzadek musi byc, enum class i te sprawy

static const quint8 KingdomCount = 4;

static const QString KingdomString[KingdomCount] = {
	QString::fromUtf8("Ludzie"),
	"Krasnoludy",
	"Elfy",
	QString::fromUtf8("Niziołki")
};

static const quint8 PlayerRaceCount = 4;
static const quint8 PlayerClassCount = 4;

// NOTE should it be here? Maybe GameInitSettings later on?
static const CharacterStats InitialStats[PlayerRaceCount][PlayerClassCount] = {
	{{15,2,10,3,1,10,1},	//Człowiek wojownik:
	{13,3,5,9,1,8,7},	//Człowiek łowca
	{11,3,2,1,11,7,4},	//Człowiek mag
	{13,5,2,2,8,10,3}},	//Człowiek druid:

	{{15,2,10,5,1,10,1},	//Krasnolud wojownik
	{13,3,5,9,1,8,7},	//Krasnolud łowca
	{11,3,2,1,11,7,4},	//Krasnolud mag
	{13,5,2,2,8,9,3}},	//Krasnolud druid

	{{15,2,10,5,1,10,1},	//Elf wojownik
	{13,3,5,9,1,8,7},	//Elf łowca
	{11,3,2,1,11,7,4},	//Elf mag
	{13,5,2,2,8,9,3}},	//Elf druid

	{{15,2,10,5,1,10,1},	//Niziołek wojownik
	{13,3,5,9,1,8,7},	//Niziołek łowca
	{11,3,2,1,11,7,4},	//Niziołek mag
	{13,5,2,2,8,9,3}}	//Niziołek druid
};

//index nazwy rasy jest równoznaczny z wartością enumeratora PlayerRace, dla tej rasy
static const QString PlayerRaceString[PlayerRaceCount] = {
	QString::fromUtf8("Człowiek"),
	"Krasnolud",
	"Elf",
	QString::fromUtf8("Niziołek")
};

enum PlayerRace {
	czlowiek = 0,
	krasnolud = 1,
	elf = 2,
	niziolek = 3
};

//index nazwy klasy jest równoznaczny z wartością enumeratora PlayerClass, dla tej rasy
static const QString PlayerClassString[PlayerClassCount] = {
	"Wojownik",
	QString::fromUtf8("Łowca"),
	"Mag",
	"Druid"
};

enum PlayerClass {
	wojownik,
	lowca,
	mag,
	druid
};

//index ustawienia początkowego jest równoznaczna z wartością enumeratora Rasa, dla tej rasy
//TODO CFiend KILL IT WITH FIRE
// should be solved by decent content editor or by reading with board setup
static const FieldId StartingPosition[PlayerRaceCount] = {
	{18,3}, //czlowiek
	{14,18}, //krasnolud
	{28,8}, //elf
	{2,8}  //niziołek
};

//TODO CFiend te rozne rodzaje ataku to moze tez powinien byc enum?
//TODO CFiend i atrybuty tak samo

class Player {

public:
	Player(QString name, PlayerRace playerRace, PlayerClass playerClass, QColor color, bool isAI);
	virtual ~Player();

	QString name() const;
	PlayerRace playerRace() const;
	PlayerClass playerClass() const;
	QColor color() const;
	bool isAI() const;
	FieldId position() const;
	void setPosition(FieldId id);
	Equipment * equipment() const;
	QList <Quest *> * quests();
	Quest * quest(int index) const;
	void removeQuest(int questId);
	quint8 level() const;
	void setLevel(quint8 level);
	int * reputation(); //TODO CFiend moze lepiej, zeby to bylo cos mocniejszego niz int *
	void setReputation(int value, int index);
	int healthMax() const;
	void setHealthMax(int value);
	int healthCurrent() const;
	void setHealthCurrent(int value);
	int regeneration() const;
	void setRegeneration(int value);
	int attackMelee() const;
	void setAttackMelee(int value);
	int attackRanged() const;
	void setAttackRanged(int value);
	int attackMagical() const;
	void setAttackMagical(int value);
	int defence() const;
	void setDefence(int value);
	int perception() const;
	void setPerception(int value);
	quint8 movePoints() const;
	void setMovePoints(quint8 value);
	quint16 gold() const;
	void setGold(quint16 value);
	quint16 experience() const;
	void setExperience(quint16 value);
	bool hasFoughtRecently() const;
	void setHasFoughtRecently(bool value);
	bool isActive() const;
	void setIsActive(bool value);

	static const quint8 StartingExperience = 0;
	static const quint8 StartingGold = 3;
	static const quint8 StartingLevel = 1;
	static const quint8 StartingMovePoints = 8;
	static const quint8 StartingReputation = 0;

	static const quint8 MaxLevel = 5;

private:
	void copyStats(CharacterStats stats);

	QString name_;
	PlayerRace playerRace_;
	PlayerClass playerClass_;
	QColor color_;
	bool isAI_;
	FieldId position_;
	Equipment *equipment_; //TODO CFiend sprawdzic czy nie lepiej dac twardy obiekt
	QList <Quest *> quests_;
	QList <FieldId> importantFields_;
	quint8 level_;
	int reputation_[KingdomCount];
	int healthMax_;
	int healthCurrent_;
	int regeneration_;
	int attackMelee_;
	int attackRanged_;
	int attackMagical_;
	int defence_;
	int perception_;
	quint8 movePoints_;
	quint16 gold_;
	quint16 experience_;
	bool hasFoughtRecently_;
	bool isActive_;
};

#endif
