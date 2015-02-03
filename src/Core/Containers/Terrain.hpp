/*
Copyright (C) 2014-2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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

#include <QtGui>

#include "Core/Enums.hpp"
#include "Core/Utils/Serial.hpp"

class Terrain {

public:
	Terrain();
	Terrain(const QString& name, const QString &pixmapName,
	        quint8 moveCost, const QList<Action> &actions);

	UID uid() const;
	const QString& name() const ;
	const QString& pixmapName() const;
	quint8 moveCost() const;
	const QList<Action>& actions() const;
	QDataStream& toDataStream(QDataStream &out) const;

	void setUid(UID uid);
	void setName(const QString &name);
	void setPixmapName(const QString &pixmapName);
	void setMoveCost(quint8 moveCost);
	void setActions(const QList<Action> &actions);
	void addAction(Action action);
	QDataStream& fromDataStream(QDataStream &in);

private:
	UID uid_;
	QString name_;
	QString pixmapName_;
	quint8 moveCost_;
	QList<Action> actions_;
};
QDataStream &operator<<(QDataStream &out, const Terrain &terrain);
QDataStream &operator>>(QDataStream &in, Terrain &terrain);
