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

#include "Equipment.h"

Equipment::Equipment(Class playerClass) : playerClass_(playerClass)
{}

QList <Effect> Equipment::activeEffects() const
{
	//TODO
	return {};
}

void Equipment::addItems(const QList <UID> &items)
{
//TODO
}

/*
QString effectString(int bonus, QString effect)
{
	QString result;
	if (bonus > 0)
		result = "+";
	if (bonus < 0)
		result = "-";
	if (bonus != 0)
		result += QString::number(bonus) + " " + effect + "\n";

	return result;
}

void equipItem(const Item *item, Player *player)
{
	Equipment *equipment = player->equipment();

	if (item == nullptr || isEquipped(item, player) || (item->type() == Item::Type::Artifact && equipment->usedArtifacts().size() >= Item::ArtifactLimit))
		return;

	switch (item->type()) {
		case Item::Type::TwoHanded:
			unequipItem(equipment->rightHand(), player);
			unequipItem(equipment->leftHand(), player);
			equipment->setRightHand(item);
			break;
		case Item::Type::OneHanded:
			unequipItem(equipment->rightHand(), player);
			equipment->setRightHand(item);
			break;
		case Item::Type::Shield:
			if (equipment->rightHand() != nullptr && equipment->rightHand()->type() == Item::Type::TwoHanded)
				unequipItem(equipment->rightHand(), player);
			unequipItem(equipment->leftHand(), player);
			equipment->setLeftHand(item);
			break;
		case Item::Type::Armor:
			unequipItem(equipment->torso(), player);
			equipment->setTorso(item);
			break;
		case Item::Type::Helmet:
			unequipItem(equipment->head(), player);
			equipment->setHead(item);
			break;
		case Item::Type::Artifact:
			if (equipment->usedArtifacts().size() < Item::ArtifactLimit)
				equipment->addArtifact(item);
		case Item::Type::Potion:
			qDebug() << "Proba zalozenia mikstury";
	}

	activateBonus(item, player);
}

void unequipItem(const Item *item, Player *player)
{
	if (item == nullptr || !isEquipped(item, player))
		return;

	Equipment *equipment = player->equipment();

	switch (item->type()) {
		case Item::Type::TwoHanded:
		case Item::Type::OneHanded:
			equipment->setRightHand(nullptr);
			break;
		case Item::Type::Shield:
			equipment->setLeftHand(nullptr);
			break;
		case Item::Type::Armor:
			equipment->setTorso(nullptr);
			break;
		case Item::Type::Helmet:
			equipment->setHead(nullptr);
			break;
		case Item::Type::Artifact:
			equipment->removeArtifact(item);
			break;
		default:
			qDebug() << QString::fromUtf8("PrÃ³bowano zaÅoÅ¼yÄ nierozpoznany rodzaj ekwipunku.");
	}

	deactivateBonus(item, player);
}
*/