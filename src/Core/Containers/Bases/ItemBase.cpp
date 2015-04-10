/*
Copyright (C) 2013-2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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
#include "ItemBase.hpp"

#include "Core/Utils/EnumHelpers.hpp"
#include "Core/Containers/PlayerDraft.hpp"

inline uint qHash(ItemBase::Type type)
{
	return qHash(toUnderlying(type));
}

QDataStream & operator<<(QDataStream & out, const ItemBase::Type & type)
{
	return out << toUnderlying(type);
}

QDataStream & operator>>(QDataStream & in, ItemBase::Type & type)
{
	return in >> toUnderlyingRef(type);
}

const BiHash <ItemBase::Type, QString> ItemBase::TypeLabels = {
	{ItemBase::Type::Armor,           QObject::tr("Armor")},
	{ItemBase::Type::Artifact,        QObject::tr("Artifact")},
	{ItemBase::Type::Helmet,          QObject::tr("Helmet")},
	{ItemBase::Type::Shield,          QObject::tr("Shield")},
	{ItemBase::Type::OneHandedWeapon, QObject::tr("One Handed Weapon")},
	{ItemBase::Type::TwoHandedWeapon, QObject::tr("Two Handed Weapon")},
	{ItemBase::Type::Potion,          QObject::tr("Potion")}
};

inline uint qHash(ItemBase::Quality quality)
{
	return qHash(toUnderlying(quality));
}

QDataStream & operator<<(QDataStream & out, const ItemBase::Quality & quality)
{
	return out << toUnderlying(quality);
}

QDataStream & operator>>(QDataStream & in, ItemBase::Quality & quality)
{
	return in >> toUnderlyingRef(quality);
}

const BiHash <ItemBase::Quality, QString> ItemBase::QualityLabels = {
	{ItemBase::Quality::NotApplicable, QObject::tr("Not Applicable")},
	{ItemBase::Quality::Standard,      QObject::tr("Standard")},
	{ItemBase::Quality::Magical,       QObject::tr("Magical")},
	{ItemBase::Quality::Legendary,     QObject::tr("Legendary")},
};

ItemBase::ItemBase(UID uid, const QString & name) :
	uid_(uid),
	name_(name),
	type_(Type::Armor),
	price_(0),
	quality_(Quality::NotApplicable),
	canBeDrawn_(true)
{}

ItemBase::ItemBase(UID uid,
                   const QString & name,
                   ItemBase::Type type,
                   quint16 price,
                   ItemBase::Quality quality,
                   bool canBeDrawn,
                   const QList <Effect> effects) :
	uid_(uid),
	name_(name),
	type_(type),
	price_(price),
	quality_(quality),
	canBeDrawn_(canBeDrawn),
	effects_(effects)
{}

const QList <Effect> & ItemBase::effects() const
{
	return effects_;
}

const QString & ItemBase::name() const
{
	return name_;
}

quint16 ItemBase::price() const
{
	return price_;
}

ItemBase::Quality ItemBase::quality() const
{
	return quality_;
}

bool ItemBase::canBeDrawn() const
{
	return canBeDrawn();
}

ItemBase::Type ItemBase::type() const
{
	return type_;
}

UID ItemBase::uid() const
{
	return uid_;
}

bool ItemBase::isRestricted(Class playerClass) const
{
	//TODO map from item <<ItemBase::Type, Class>, bool> or sth like that
	return false;
}

QDataStream & ItemBase::toDataStream(QDataStream & out) const
{
	return out << uid_ << name_ << type_ << price_ << quality_ << canBeDrawn_ << effects_;
}

void ItemBase::addEffect(const Effect & effect)
{
	effects_.append(effect);
}

QDataStream & ItemBase::fromDataStream(QDataStream & in)
{
	return in >> uid_ >> name_ >> type_ >> price_ >> quality_ >> canBeDrawn_ >> effects_;
}

void ItemBase::setEffects(const QList <Effect> & effects)
{
	effects_ = effects;
}

void ItemBase::setName(const QString & name)
{
	name_ = name;
}

void ItemBase::setPrice(quint16 price)
{
	price_ = price;
}

void ItemBase::setQuality(ItemBase::Quality quality)
{
	quality_ = quality;
}

void ItemBase::setCanBeDrawn(bool canBeDrawn)
{
	canBeDrawn_ = canBeDrawn;
}

void ItemBase::setType(ItemBase::Type type)
{
	type_ = type;
}

QDataStream & operator<<(QDataStream & out, const ItemBase & base)
{
	return base.toDataStream(out);
}

QDataStream & operator>>(QDataStream & in, ItemBase & base)
{
	return base.fromDataStream(in);
}
