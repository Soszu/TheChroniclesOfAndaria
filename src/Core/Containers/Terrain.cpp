#include "Core/Containers/Terrain.h"

Terrain::Terrain() :
	uid_(Serial::EmptyUid),
	moveCost_(100)
{}

Terrain::Terrain(const QString &name, const QString &pixmapName,
                 quint8 moveCost, const QList<Action> &actions) :
	uid_(Serial::EmptyUid),
	name_(name),
	pixmapName_(pixmapName),
	moveCost_(moveCost),
	actions_(actions)
{}

UID Terrain::uid() const
{
	return uid_;
}

const QString &Terrain::name() const
{
	return name_;
}

const QString &Terrain::pixmapName() const
{
	return pixmapName_;
}

quint8 Terrain::moveCost() const
{
	return moveCost_;
}

const QList<Action> &Terrain::actions() const
{
	return actions_;
}

QDataStream &Terrain::toDataStream(QDataStream &out) const
{
	return out << name_ << pixmapName_ << moveCost_ << actions_;
}

void Terrain::setUid(UID uid)
{
	uid_ = uid;
}

void Terrain::setName(const QString &name)
{
	name_ = name;
}

void Terrain::setPixmapName(const QString &pixmapName)
{
	pixmapName_ = pixmapName;
}

void Terrain::setMoveCost(quint8 moveCost)
{
	moveCost_ = moveCost;
}

void Terrain::setActions(const QList<Action> &actions)
{
	actions_ = actions;
}

void Terrain::addAction(Action action)
{
	actions_.append(action);
}

QDataStream &Terrain::fromDataStream(QDataStream &in)
{
	return in << name_ << pixmapName_ << moveCost_ << actions_;
}

QDataStream &operator<<(QDataStream& out, const Terrain &terrain)
{
	return terrain.toDataStream(out);
}

QDataStream &operator>>(QDataStream& in, Terrain &terrain)
{
	return terrain.fromDataStream(in);
}
