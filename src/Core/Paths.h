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

#pragma once

#include <QtCore>

//to be wiped out with parsers
static const QString PLIK_PRZECIWNIKOW = "data/przeciwnicy.txt";
static const QString PLIK_NAGROD = "data/nagrody.txt";
static const QString PLIK_PRZEDMIOTOW = "data/przedmioty.txt";
static const QString PLIK_ZADAN = "data/zadania.txt";
static const QString PLIK_USTAWIENIA_PLANSZY = "data/plansza.txt";

//To be wiped out with editor & mod & .qrc file
namespace Path {
	static const QString DataPrefix = "data/";

	static const QString ModsDir   = DataPrefix + "mods/";
	static const QString NativeMod = ModsDir + "native.tcoa";

	static const QString ImagesPrefix   = DataPrefix + "images/";
	static const QString IconsPrefix    = ImagesPrefix + "icons/";
	static const QString TerrainsPrefix = ImagesPrefix + "terrains/";
	static const QString EnemiesPrefix  = ImagesPrefix + "enemies/";

	static const QString IconColor        = IconsPrefix + "color.png";
	static const QString IconMelee        = IconsPrefix + "melee.png";
	static const QString IconRanged       = IconsPrefix + "ranged.png";
	static const QString IconMagic        = IconsPrefix + "magic.png";
	static const QString IconDefence      = IconsPrefix + "defence.png";
	static const QString IconAttack       = IconsPrefix + "melee.png";
	static const QString IconPerception   = IconsPrefix + "perception.png";
	static const QString IconMovement     = IconsPrefix + "movement.png";
	static const QString IconGold         = IconsPrefix + "gold.png";
	static const QString IconRegeneration = IconsPrefix + "regeneration.png";

	static const QString IconFightSymbol = IconsPrefix + "fight_symbol.png";

	static const QString IconSmallHealthMixture = IconsPrefix + "small_hp_mixture.png";
	static const QString IconBigHealthMixture   = IconsPrefix + "big_hp_mixture.png";
}

QString resolvePath(const QString &path);
QString resolveEnemyImage(const QString &imageName);
