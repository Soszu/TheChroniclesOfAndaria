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
#include "Item.hpp"

Item::Item(ItemBase * base) :
	base_(base)
{}

QList<Effect> Item::effects() const
{
	return base_->effects();
}

bool Item::isRestricted(Class playerClass) const
{
	return base_->isRestricted(playerClass);
}

QString Item::name() const
{
	return base_->name();
}

quint16 Item::price() const
{
	return base_->price();
}

ItemBase::Quality Item::quality() const
{
	return base_->quality();
}

bool Item::canBeDrawn() const
{
	return base_->canBeDrawn();
}

QDataStream & Item::toDataStream(QDataStream & out) const
{
	return out << base_->uid();
}

ItemBase::Type Item::type() const
{
	return base_->type();
}
/*
QDataStream & Item::fromDataStream(QDataStream & in)
{
	UID uid;
	in >> uid;
	//base_ = DataKeeper::giveItemByUid(uid);
	return in;
}*/

QDataStream & operator<<(QDataStream & out, const Item & item)
{
	return item.toDataStream(out);
}
/*
QDataStream & operator>>(QDataStream & in, Item & item)
{
	return item.fromDataStream(in);
}*/
