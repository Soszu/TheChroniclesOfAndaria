#include "Core/Containers/Player.h"

Player::Player(QString name, PlayerRace playerRace, PlayerClass playerClass, QColor color, bool isAI)
	: name_(name),
	  playerRace_(playerRace),
	  playerClass_(playerClass),
	  color_(color),
	  isAI_(isAI),
	  position_(StartingPosition[this->playerRace_]),
	  equipment_(new Equipment),
	  level_(StartingLevel),
	  movePoints_(StartingMovePoints),
	  gold_(StartingGold),
	  experience_(StartingExperience),
	  hasFoughtRecently_(false),
	  isActive_(true)
{
	copyStats(InitialStats[this->playerRace_][this->playerClass_]);

	for(int i = 0; i < KingdomCount; ++i)
		this->reputation_[i] = StartingReputation;

	this->healthCurrent_ = this->healthMax_;
}

Player::~Player()
{
	delete equipment_;
}

QString Player::name() const
{
	return name_;
}

PlayerRace Player::playerRace() const
{
	return playerRace_;
}

PlayerClass Player::playerClass() const
{
	return playerClass_;
}

QColor Player::color() const
{
	return color_;
}

bool Player::isAI() const
{
	return isAI_;
}

FieldId Player::position() const
{
	return position_;
}

void Player::setPosition(FieldId id)
{
	this->position_ = id;
}

Equipment * Player::equipment() const
{
	return equipment_;
}

QList <Quest *> * Player::quests()
{
	return &quests_; //TODO CFiend taka implementacja uniemozliwia uczynienie tej metody const
}

Quest * Player::quest(int index) const
{
	return quests_[index];
}

void Player::removeQuest(int questId)
{
	int i = 0;
	while (i < quests_.size() && quests_[i]->id() != questId)
		++i;
	if (i != quests_.size())
		delete quests_.takeAt(i);
}

quint8 Player::level() const
{
	return level_;
}

void Player::setLevel(quint8 level)
{
	this->level_ = level;
}

int * Player::reputation()
{
	return reputation_; //TODO CFiend taka implementacja uniemozliwia uczynienie tej metody const
}

void Player::setReputation(int value, int index)
{
	reputation_[index] = value;
}

int Player::healthMax() const
{
	return healthMax_;
}

void Player::setHealthMax(int value)
{
	healthMax_ = value;
}

int Player::healthCurrent() const
{
	return healthCurrent_;
}

void Player::setHealthCurrent(int value)
{
	healthCurrent_ = value;
}

int Player::regeneration() const
{
	return regeneration_;
}

void Player::setRegeneration(int value)
{
	regeneration_ = value;
}

int Player::attackMelee() const
{
	return attackMelee_;
}

void Player::setAttackMelee(int value)
{
	attackMelee_ = value;
}

int Player::attackRanged() const
{
	return attackRanged_;
}

void Player::setAttackRanged(int value)
{
	attackRanged_ = value;
}

int Player::attackMagical() const
{
	return attackMagical_;
}

void Player::setAttackMagical(int value)
{
	attackMagical_ = value;
}

int Player::defence() const
{
	return defence_;
}

void Player::setDefence(int value)
{
	defence_ = value;
}

int Player::perception() const
{
	return perception_;
}

void Player::setPerception(int value)
{
	perception_ = value;
}

quint8 Player::movePoints() const
{
	return movePoints_;
}

void Player::setMovePoints(quint8 value)
{
	movePoints_ = value;
}

quint16 Player::gold() const
{
	return gold_;
}

void Player::setGold(quint16 value)
{
	gold_ = value;
}

quint16 Player::experience() const
{
	return experience_;
}

void Player::setExperience(quint16 value)
{
	experience_ = value;
}

bool Player::hasFoughtRecently() const
{
	return hasFoughtRecently_;
}

void Player::setHasFoughtRecently(bool value)
{
	hasFoughtRecently_ = value;
}

void Player::setIsActive(bool value)
{
	isActive_ = value;
}

bool Player::isActive() const
{
	return isActive_;
}

/**
 * @brief Gracz::przepiszStaty Przepisuje statystyki zebrane w jedym miejscu.
 * @param stats konkretne wartości do przepisania. Zdefiniowane w gra.h
 */
void Player::copyStats(CharacterStats stats)
{
	this->healthMax_ = stats.healthMax;
	this->regeneration_ = stats.regeneration;
	this->attackMelee_ = stats.attackMelee;
	this->attackRanged_ = stats.attackRanged;
	this->attackMagical_ = stats.attackMagical;
	this->defence_ = stats.defence;
	this->perception_ = stats.perception;
}
