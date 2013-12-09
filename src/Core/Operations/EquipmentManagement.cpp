#include <QtCore>
#include "Core/Containers/Player.h"
#include "Core/Operations/EquipmentManagement.h"

/**
 * @brief aktywujBonusy		Metoda przypisująca bonusy przedmiotu podanemu graczowi
 * @param przedmiot	przedmiot, którego bonusy mają zostać przepisane graczowi.
 * @param gracz		dane gracza, który zakłada podany przedmiot
 * @param m		modyfikator dla każdego bonusu (domyślnie 1)
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
 * @brief dezaktywujBonusy	Metoda ujmująca bonusy przedmiotu podanemu graczowi
 * @param przedmiot	przedmiot, którego bonusy mają zostać przepisane graczowi.
 * @param gracz		dane gracza, który zakłada podany przedmiot
 */
void deactivateBonus(const Item *item, Player *player)
{
	activateBonus(item, player, -1);
}

/**
 * @brief czyBrakOgraniczenia	Stwierdza, czy klasa o podanym indeksie może używać podanego przedmiotu.
 * @param przedmiot	przedmiot, którego dot. pytanie
 * @param indeks	indeks klasy, której dot. pytanie (gra.h)
 * @return		true, jeśli dana klasa może używać przedmiotu, false w p.p.
 */
bool isAllowedForClass(const Item *item, int index)
{
	int restrictions = item->restrictions();
	restrictions /= qPow(10, PlayerRaceCount - index - 1);
	restrictions %= 10;

	return restrictions != 0;
}

/**
 * @brief czyDozwolony		Stwierdza, czy gracz może aktualnie założyć podany przedmiot.
 * @param przedmiot	przedmiot, którego dotyczy pytanie
 * @param gracz		gracz, ktorego dot. pytanie
 * @return		true, jeśli przedmiot jest dozwolony, false w p.p.
 */
bool isPermitted(const Item *item, const Player *player)
{
	if (item->isStrong() && player->level() < Player::MaxLevel)
		return false;

	return isAllowedForClass(item, player->playerClass());
}

/**
 * @brief dzialanie	Dodaje + albo - przed opisem działania, jeżeli opis jest niezerowy
 * @param bonus
 * @param dzialanie
 * @return		Opis działania, jeżeli bonus jest niezerowy, napis pusty w p.p.``
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
 * @brief czyZalozony	Stierdza, czy dany przedmiot jest już założony.
 * @param rzecz
 * @param gracz
 * @return		true jeśli założony, false w p.p.
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
 * @param gracz		Gracz, który miałby dany przedmiot nosić (do stwierdzenia czy może)
 * @param miejsce	QTextBrowser którego tekst ma być podmieniony na wygenerowany opis.
 */
void generateDescription(const Item *item, const Player *player, QTextBrowser *target)
{
	target->clear();

	QString equipped = isEquipped(item, player) ? "Tak" : "Nie";
	QString permitted = isPermitted(item, player) ? "Tak" : "Nie";
	QString minLevel = item->isStrong() ? QString::number(Player::MaxLevel) : "1";
	QString numberOfArtifacts = QString::number(player->equipment()->usedArtifacts().size());
	QString permittedClasses;
	for (int i = 0; i < PlayerRaceCount; ++i)
		if (isAllowedForClass(item, (PlayerClass)i))
			permittedClasses += PlayerClassString[i] + ". ";
	if (permittedClasses.size() > 2)
		permittedClasses.replace(permittedClasses.size() - 2, 2, "");

	//TODO color title acording to item quality
	target->setFontWeight(QFont::Bold);
	target->insertPlainText(item->name() + QString("\n\n"));
	target->setFontWeight(QFont::Normal);

	QString description;

	description += QString("typ: ") + RODZAJE_PRZEDMIOTOW[toUnderlying(item->type())] + QString("\n");
	if (item->type() == Item::Type::Artifact)
		description += QString::fromUtf8("Założonych artefaktów: (") + numberOfArtifacts + QString("/") + QString::number(Item::ArtifactLimit) + QString(")\n");

	description += QString::fromUtf8("\ndozwolony od poziomu: ") + minLevel +  QString("\n");
	description += QString::fromUtf8("klasy zdolne używać przedmiotu: ") + permittedClasses +  QString("\n");
	description += QString::fromUtf8("czy dozwolony: ") + permitted +  QString("\n");
	description += QString::fromUtf8("czy założony: ") + equipped +  QString("\n\n");

	description += effectString(item->bonusMelee(), QString::fromUtf8("walka wręcz") );
	description += effectString(item->bonusRanged(), QString::fromUtf8("walka bronią dystansową") );
	description += effectString(item->bonusMagical(),  QString::fromUtf8("walka magiczna") );
	description += effectString(item->bonusDefence(), QString::fromUtf8("defence") );
	description += effectString(item->bonusPerception(), QString::fromUtf8("perception"));
	description += effectString(item->bonusHitPoints(), QString::fromUtf8("zdrowie"));
	description += effectString(item->bonusRegeneration(), QString::fromUtf8("regeneracja"));

	description += QString::fromUtf8("\nwartość kupna:  ") + QString::number(item->value());
	description += QString::fromUtf8("\nwartość sprzedaży:  ") + QString::number(item->value() / 2) + QString("\n");

	target->insertPlainText(description);
}

/**
 * @brief zalozPrzedmiot	W miarę możliwości zakłada dany przedmiot na gracza
 * @param rzecz		przedmiot do założenia
 * @param gracz		gracz, który zakłada przedmiot
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
		if (equipment->rightHand()->type() == Item::Type::TwoHanded)
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
 * @brief zdejmijPrzedmiot	W miarę możliwości zdejmuje dany przedmiot z gracza.
 * @param rzecz		Przedmiot do zdjęcia
 * @param gracz		gracz, który zdjejmuje przedmiot
 */
void unequipItem(const Item *item, Player *player)
{
	if (!isEquipped(item, player) || item == nullptr)
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
		qDebug() << QString::fromUtf8("Próbowano założyć nierozpoznany rodzaj ekwipunku.");
	}

	deactivateBonus(item, player);
}
