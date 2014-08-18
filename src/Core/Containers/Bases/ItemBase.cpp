#include "ItemBase.h"
#include "Core/Utils/EnumHelpers.hpp"
#include "Core/Containers/PlayerDraft.h"


inline uint qHash(ItemBase::Type type)
{
	return qHash(toUnderlying(type));
}

QDataStream & operator<<(QDataStream &out, const ItemBase::Type &type)
{
	return out << toUnderlying(type);
}

QDataStream & operator>>(QDataStream &in, ItemBase::Type &type)
{
	return in >> toUnderlyingRef(type);
}

const BiHash <ItemBase::Type, QString> ItemBase::TypeLabels = {
	{ItemBase::Type::Armor, Label::Item::Armor},
	{ItemBase::Type::Artifact, Label::Item::Artifact},
	{ItemBase::Type::Helmet, Label::Item::Helmet},
	{ItemBase::Type::Shield, Label::Item::Shield},
	{ItemBase::Type::OneHandedWeapon, Label::Item::OneHandedWeapon},
	{ItemBase::Type::TwoHandedWeapon, Label::Item::TwoHandedWeapon},
	{ItemBase::Type::Potion, Label::Item::Potion}
};

inline uint qHash(ItemBase::Quality quality)
{
	return qHash(toUnderlying(quality));
}

QDataStream & operator<<(QDataStream &out, const ItemBase::Quality &quality)
{
	return out << toUnderlying(quality);
}

QDataStream & operator>>(QDataStream &in, ItemBase::Quality &quality)
{
	return in >> toUnderlyingRef(quality);
}

const BiHash <ItemBase::Quality, QString> ItemBase::QualityLabels = {
	{ItemBase::Quality::NotApplicable, Label::Item::NotApplicable},
	{ItemBase::Quality::Standard,      Label::Item::Standard},
	{ItemBase::Quality::Magical,       Label::Item::Magical},
	{ItemBase::Quality::Legendary,     Label::Item::Legendary},
};

ItemBase::ItemBase(UID uid, const QString &name)
        : uid_(uid),
          name_(name),
          type_(Type::Armor),
          price_(0),
          quality_(Quality::NotApplicable)
{}

ItemBase::ItemBase(UID uid,
                   const QString &name,
                   ItemBase::Type type,
                   quint16 price,
                   ItemBase::Quality quality,
                   const QList <Effect> effects)
        : uid_(uid),
          name_(name),
          type_(type),
          price_(price),
          quality_(quality),
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

ItemBase::Type ItemBase::type() const
{
	return type_;
}

UID ItemBase::uid() const
{
	return uid_;
}

QDataStream & ItemBase::toDataStream(QDataStream &out) const
{
	return out << uid_ << name_ << type_ << price_ << quality_ << effects_;
}

void ItemBase::addEffect(const Effect &effect)
{
	effects_.append(effect);
}

QDataStream & ItemBase::fromDataStream(QDataStream &in)
{
	return in >> uid_ >> name_ >> type_ >> price_ >> quality_ >> effects_;
}

void ItemBase::setEffects(const QList <Effect> &effects)
{
	effects_ = effects;
}

void ItemBase::setName(const QString &name)
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

void ItemBase::setType(ItemBase::Type type)
{
	type_ = type;
}

QDataStream & operator<<(QDataStream &out, const ItemBase &base)
{
	return base.toDataStream(out);
}

QDataStream & operator>>(QDataStream &in, ItemBase &base)
{
	return base.fromDataStream(in);
}
