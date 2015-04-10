/*
Copyright (C) 2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
+Copyright (C) 2015 by Marcin Parafiniuk <jessie [dot] inferno [at] gmail [dot] com>
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

#include <QtGlobal>

enum class Kingdom : quint8;
uint qHash(Kingdom);
QDataStream & operator<<(QDataStream &, const Kingdom &);
QDataStream & operator>>(QDataStream &, Kingdom &);

enum class Race : quint8;
uint qHash(Race);
QDataStream & operator<<(QDataStream &, const Race &);
QDataStream & operator>>(QDataStream &, Race &);

enum class Class : quint8;
uint qHash(Class);
QDataStream & operator<<(QDataStream &, const Class &);
QDataStream & operator>>(QDataStream &, Class &);

enum class Attack : quint8;
uint qHash(Attack);
QDataStream & operator<<(QDataStream &, const Attack &);
QDataStream & operator>>(QDataStream &, Attack &);

enum class Action : quint8;
uint qHash(Action);
QDataStream & operator<<(QDataStream &, const Action &);
QDataStream & operator>>(QDataStream &, Action &);

enum class Difficulty : quint8;
uint qHash(Difficulty);
QDataStream & operator<<(QDataStream &, const Difficulty &);
QDataStream & operator>>(QDataStream &, Difficulty &);
