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

#include <QtWidgets>

#include "Core/Enums.hpp"

static const int MinPlayers = 2;
static const int MaxPlayers = 8;
static const int MaxNameLength = 20;

struct PlayerDraft {
public:
	PlayerDraft();
	const QColor & color() const;
	const QString & name() const;
	Class playerClass() const;
	Race playerRace() const;
	QDataStream & toDataStream(QDataStream &out) const;

	QDataStream & fromDataStream(QDataStream &in);
	void setAvatar(const QPixmap &pixmap);
	void setColor(const QColor &color);
	void setName(const QString &name);
	void setPlayerClass(Class playerClass);
	void setPlayerRace(Race playerRace);

private:
	QColor generateRandomColor();
	QString generateRandomName();

	QColor color_;
	QString name_;
	Class playerClass_;
	Race playerRace_;
};
