/*
Copyright (C) 2013 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
This file is part of The Chronicles Of Andaria Project.

	The Chronicles of Andaria Project is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	The Chronicles of Andaria Project is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with The Chronicles Of Andaria.  If not, see <http://www.gnu.org/licenses/>.
*/

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
