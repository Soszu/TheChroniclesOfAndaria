/*
Copyright (C) 2013-2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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
#pragma once

#include "Core/Containers/Bases/ItemBase.hpp"
#include "Core/Enums.hpp"
#include "Core/Containers/PlayerDraft.hpp"

class Item {
public:
	Item(ItemBase *base = nullptr);

	QList <Effect> effects() const;
	bool isRestricted(Class playerClass) const;
	QString name() const;
	quint16 price() const;
	ItemBase::Quality quality() const;
	bool canBeDrawn() const;
	QDataStream & toDataStream(QDataStream &out) const;
	ItemBase::Type type() const;

	QDataStream & fromDataStream(QDataStream &in);

private:
	ItemBase *base_;
};

QDataStream & operator<<(QDataStream &out, const Item &item);
QDataStream & operator>>(QDataStream &in, Item &item);
