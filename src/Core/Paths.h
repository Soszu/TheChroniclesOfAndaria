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

#ifndef PATHS_H
#define PATHS_H

#include <QtCore>

//to be wiped out with parsers
static const QString PLIK_PRZEDMIOTOW = "data/przedmioty.txt";
static const QString PLIK_PRZECIWNIKOW = "data/przeciwnicy.txt";
static const QString PLIK_NAGROD = "data/nagrody.txt";
static const QString PLIK_ZADAN = "data/zadania.txt";
static const QString PLIK_USTAWIENIA_PLANSZY = "data/plansza.txt";

namespace TCOA {
	namespace Paths {
		static const QString IMAGES_PREFIX  = "img/";
		static const QString ICONS_PREFIX   = IMAGES_PREFIX + "icons/";
		static const QString HEXES_PREFIX   = IMAGES_PREFIX + "hexes/";
		static const QString ENEMIES_PREFIX = IMAGES_PREFIX + "enemies/";

		static const QString ICON_MELEE        = ICONS_PREFIX + "melee.png";
		static const QString ICON_RANGED       = ICONS_PREFIX + "ranged.png";
		static const QString ICON_MAGIC        = ICONS_PREFIX + "magic.png";
		static const QString ICON_DEFENCE      = ICONS_PREFIX + "defence.png";
		static const QString ICON_ATTACK       = ICONS_PREFIX + "melee.png";
		static const QString ICON_PERCEPTION   = ICONS_PREFIX + "perception.png";
		static const QString ICON_MOVEMENT     = ICONS_PREFIX + "movement.png";
		static const QString ICON_GOLD         = ICONS_PREFIX + "gold.png";
		static const QString ICON_REGENERATION = ICONS_PREFIX + "regeneration.png";

		static const QString ICON_FIGHT_SYMBOL = ICONS_PREFIX + "fight_symbol.png";

		static const QString ICON_SMALL_HEALTH_MIXTURE = ICONS_PREFIX + "small_hp_mixture.png";
		static const QString ICON_BIG_HEALTH_MIXTURE   = ICONS_PREFIX + "big_hp_mixture.png";
	}

	QString resolvePath(const QString &path);
}

#endif // PATHS_H
