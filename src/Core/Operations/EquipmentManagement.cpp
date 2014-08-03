/*
Copyright (C) 2013 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
Copyright (C) 2013 Łukasz Piesiewicz <wookesh [at] gmail [dot] com>
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

#include <QtCore>
#include "Core/Containers/Player.h"
#include "Core/Operations/EquipmentManagement.h"

/**
 * @brief aktywujBonusy		Metoda przypisujÄca bonusy przedmiotu podanemu graczowi
 * @param przedmiot	przedmiot, ktÃ³rego bonusy majÄ zostaÄ przepisane graczowi.
 * @param gracz		dane gracza, ktÃ³ry zakÅada podany przedmiot
 * @param m		modyfikator dla kaÅ¼dego bonusu (domyÅlnie 1)
 */
void activateBonus(const Item *item, Player *player, int multiplier)
{
	player->setAttackMelee(player->attackMelee() + item->bonusMelee() * multiplier);
	player->setAttackRanged(player->attackRanged() + item->bonusRanged() * multiplier);
	player->setAttackMagical(player->attackMagical() + item->bonusMagical() * multiplier);
	player->setDefence(player->defence() + item->bonusDefence() * multiplier);
	player->setPerception(player->perception() + item->bonusPerception() * multiplier);
	player->setHealthMax(player->healthMax() + item->bonusHitPoints() * multiplier);
	player->setHealthCurrent(player->healthCurrent() + item->bonusHitPoints() * multiplier);
	player->setRegeneration(player->regeneration() + item->bonusRegeneration() * multiplier);
}

/**
 * @brief dezaktywujBonusy	Metoda ujmujÄca bonusy przedmiotu podanemu graczowi
 * @param przedmiot	przedmiot, ktÃ³rego bonusy majÄ zostaÄ przepisane graczowi.
 * @param gracz		dane gracza, ktÃ³ry zakÅada podany przedmiot
 */
void deactivateBonus(const Item *item, Player *player)
{
	activateBonus(item, player, -1);
}

/**
 * @brief czyBrakOgraniczenia	Stwierdza, czy klasa o podanym indeksie moÅ¼e uÅ¼ywaÄ podanego przedmiotu.
 * @param przedmiot	przedmiot, ktÃ³rego dot. pytanie
 * @param indeks	indeks klasy, ktÃ³rej dot. pytanie (gra.h)
 * @return		true, jeÅli dana klasa moÅ¼e uÅ¼ywaÄ przedmiotu, false w p.p.
 */
bool isAllowedForClass(const Item *item, Player::Class playerClass)
{
// 	int restrictions = item->restrictions();
// 	restrictions /= qPow(10, PlayerRaceCount - index - 1);
// 	restrictions %= 10;
//
// 	return restrictions != 0;

//NOTE Wookesh line below will work after finishing item serialization, till this moment all items are alowed for everyone
// 	return item->restrictions()[playerClass];
	return true;
}

/**
 * @brief czyDozwolony		Stwierdza, czy gracz moÅ¼e aktualnie zaÅoÅ¼yÄ podany przedmiot.
 * @param przedmiot	przedmiot, ktÃ³rego dotyczy pytanie
 * @param gracz		gracz, ktorego dot. pytanie
 * @return		true, jeÅli przedmiot jest dozwolony, false w p.p.
 */
bool isPermitted(const Item *item, const Player *player)
{
	if (item->isStrong() && player->level() < Player::MaxLevel)
		return false;

	return isAllowedForClass(item, player->playerClass());
}

/**
 * @brief dzialanie	Dodaje + albo - przed opisem dziaÅania, jeÅ¼eli opis jest niezerowy
 * @param bonus
 * @param dzialanie
 * @return		Opis dziaÅania, jeÅ¼eli bonus jest niezerowy, napis pusty w p.p.``
 */
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

/**
 * @brief czyZalozony	Stierdza, czy dany przedmiot jest juÅ¼ zaÅoÅ¼ony.
 * @param rzecz
 * @param gracz
 * @return		true jeÅli zaÅoÅ¼ony, false w p.p.
 */
bool isEquipped(const Item *item, const Player *player)
{
	const Equipment *equipment = player->equipment();

	for (const Item *i : {equipment->head(), equipment->torso(), equipment->leftHand(), equipment->rightHand()})
		if (item == i)
			return true;

	return equipment->usedArtifacts().contains(item);
}

/**
 * @brief wygenerujOpis		Generuje opis dla danego przedmiotu.
 * @param rzecz
 * @param gracz		Gracz, ktÃ³ry miaÅby dany przedmiot nosiÄ (do stwierdzenia czy moÅ¼e)
 * @param miejsce	QTextBrowser ktÃ³rego tekst ma byÄ podmieniony na wygenerowany opis.
 */
void generateDescription(const Item *item, const Player *player, QTextBrowser *target)
{
	target->clear();

	QString equipped = isEquipped(item, player) ? "Tak" : "Nie";
	QString permitted = isPermitted(item, player) ? "Tak" : "Nie";
	QString minLevel = item->isStrong() ? QString::number(Player::MaxLevel) : "1";
	QString numberOfArtifacts = QString::number(player->equipment()->usedArtifacts().size());
	//TODO
// 	QString permittedClasses;
// 	for (Player::Class playerClass: Player::classLabel())
// 		if (isAllowedForClass(item, playerClass))
// 			permittedClasses += Player::classString()[playerClass] + ". ";
// 	if (permittedClasses.size() > 2)
// 		permittedClasses.replace(permittedClasses.size() - 2, 2, "");

	//TODO color title acording to item quality
	target->setFontWeight(QFont::Bold);
	target->insertPlainText(item->name() + QString("\n\n"));
	target->setFontWeight(QFont::Normal);

	QString description;

	description += QString("typ: ") + RODZAJE_PRZEDMIOTOW[toUnderlying(item->type())] + QString("\n");
	if (item->type() == Item::Type::Artifact)
		description += QString::fromUtf8("ZaÅoÅ¼onych artefaktÃ³w: (") + numberOfArtifacts + QString("/") + QString::number(Item::ArtifactLimit) + QString(")\n");

	description += QString::fromUtf8("\ndozwolony od poziomu: ") + minLevel +  QString("\n");
// 	description += QString::fromUtf8("klasy zdolne uÅ¼ywaÄ przedmiotu: ") + permittedClasses +  QString("\n");
	description += QString::fromUtf8("czy dozwolony: ") + permitted +  QString("\n");
	description += QString::fromUtf8("czy zaÅoÅ¼ony: ") + equipped +  QString("\n\n");

	description += effectString(item->bonusMelee(), QString::fromUtf8("walka wrÄcz") );
	description += effectString(item->bonusRanged(), QString::fromUtf8("walka broniÄ dystansowÄ") );
	description += effectString(item->bonusMagical(),  QString::fromUtf8("walka magiczna") );
	description += effectString(item->bonusDefence(), QString::fromUtf8("defence") );
	description += effectString(item->bonusPerception(), QString::fromUtf8("perception"));
	description += effectString(item->bonusHitPoints(), QString::fromUtf8("zdrowie"));
	description += effectString(item->bonusRegeneration(), QString::fromUtf8("regeneracja"));

	description += QString::fromUtf8("\nwartoÅÄ kupna:  ") + QString::number(item->value());
	description += QString::fromUtf8("\nwartoÅÄ sprzedaÅ¼y:  ") + QString::number(item->value() / 2) + QString("\n");

	target->insertPlainText(description);
}

/**
 * @brief zalozPrzedmiot	W miarÄ moÅ¼liwoÅci zakÅada dany przedmiot na gracza
 * @param rzecz		przedmiot do zaÅoÅ¼enia
 * @param gracz		gracz, ktÃ³ry zakÅada przedmiot
 */
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

/**
 * @brief zdejmijPrzedmiot	W miarÄ moÅ¼liwoÅci zdejmuje dany przedmiot z gracza.
 * @param rzecz		Przedmiot do zdjÄcia
 * @param gracz		gracz, ktÃ³ry zdjejmuje przedmiot
 */
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
