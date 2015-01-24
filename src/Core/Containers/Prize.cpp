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

#include "Core/Containers/Prize.h"
#include "Core/Containers/Field.h"

Prize::Prize() : experience_(0), gold_(0)
{}

Prize::Prize(QList <Effect> effects,
             quint16 experience,
             QList <Item> items,
             quint16 gold,
             QHash <Kingdom, qint8> reputations)
     : effects_(effects),
       experience_(experience),
//       items_(items),
       gold_(gold),
       reputations_(reputations)
{}

const QList <Effect> & Prize::effects() const
{
	return effects_;
}

quint16 Prize::experience() const
{
	return experience_;
}

quint16 Prize::gold() const
{
	return gold_;
}
/*
const QList <Item> & Prize::items() const
{
	return items_;
}*/

const qint8 Prize::reputation(Kingdom kingdom) const
{
	return reputations_[kingdom];
}

const QHash <Kingdom, qint8> & Prize::reputations() const
{
	return reputations_;
}

QDataStream & Prize::toDataStream(QDataStream &out) const
{
	return out << effects_ << experience_ /*<< items_ */<< gold_ << reputations_;
}

void Prize::addReputation(Kingdom kingdom, qint8 reputation)
{
	reputations_[kingdom] = reputation;
}

QDataStream & Prize::fromDataStream(QDataStream &in)
{
	return in >> effects_ >> experience_ >> /*items_ >> */gold_ >> reputations_;
}

void Prize::setEffects(QList <Effect> effects)
{
	effects_ = effects;
}

void Prize::setExperience(quint16 experience)
{
	experience_ = experience;
}

void Prize::setGold(quint16 gold)
{
	gold_ = gold;
}
/*
void Prize::setItems(QList <Item> items)
{
	items_ = items;
}*/

void Prize::setReputations(QHash <Kingdom, qint8> reputations)
{
	reputations_ = reputations;
}

QDataStream & operator<<(QDataStream &out, const Prize &prize)
{
	return prize.toDataStream(out);
}

QDataStream & operator>>(QDataStream &in, Prize &prize)
{
	return prize.fromDataStream(in);
}