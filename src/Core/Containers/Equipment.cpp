#include "Core/Containers/Equipment.h"

Equipment::Equipment()
	: head_(nullptr), torso_(nullptr), leftHand_(nullptr), rightHand_(nullptr),
	  smallPotions_(StartingNumberOfLargePotions), largePotions_(StartingNumberOfLargePotions)
{
}

const Item * Equipment::head() const
{
	return head_;
}

void Equipment::setHead(const Item *item)
{
	head_ = item;
}

const Item * Equipment::torso() const
{
	return torso_;
}

void Equipment::setTorso(const Item *item)
{
	torso_ = item;
}

const Item * Equipment::leftHand() const
{
	return leftHand_;
}

void Equipment::setLeftHand(const Item *item)
{
	leftHand_ = item;
}

const Item * Equipment::rightHand() const
{
	return rightHand_;
}

void Equipment::setRightHand(const Item *item)
{
	rightHand_ = item;
}

quint8 Equipment::smallPotions() const
{
	return smallPotions_;
}

void Equipment::setSmallPotions(quint8 cnt)
{
	smallPotions_ = cnt;
}

quint8 Equipment::largePotions() const
{
	return largePotions_;
}

void Equipment::setLargePotions(quint8 cnt)
{
	largePotions_ = cnt;
}

const QList <const Item *> & Equipment::backpack() const
{
	return backpack_;
}

const QList <const Item *> & Equipment::usedArtifacts() const
{
	return usedArtifacts_;
}

void Equipment::addItem(const Item *item)
{
	backpack_.append(item);
}

void Equipment::removeItem(const Item *item)
{
	backpack_.removeOne(item);
}

void Equipment::addArtifact(const Item *item)
{
	usedArtifacts_.append(item);
}

void Equipment::removeArtifact(const Item *item)
{
	usedArtifacts_.removeOne(item);
}
