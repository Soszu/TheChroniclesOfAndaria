#ifndef EQUIPMENTMANAGEMENT_H
#define EQUIPMENTMANAGEMENT_H

#include <QtWidgets>

#include "Core/Containers/Item.h"
#include "Core/Containers/Player.h"

//TODO CFiend czy to nie powinny byc metody Player albo Equipment?
void activateBonus(const Item *item, Player *player, int multiplier = 1);
void deactivateBonus(const Item *item, Player *player);

bool isPermitted(const Item *item, const Player *player);
bool isAllowedForClass(Item *item, PlayerClass index);

QString effectString(int bonus, QString effect);
void generateDescription(const Item *item, const Player *player, QTextBrowser *target);

bool isEquipped(const Item *item, const Player *player);
void equipItem(const Item *item, Player *player);
void unequipItem(const Item *item, Player *player);

#endif
