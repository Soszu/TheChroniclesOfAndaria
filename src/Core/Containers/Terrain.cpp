#include "Core/Containers/Terrain.h"

Terrain::Terrain(QString name, QString imagePath, quint8 coefficient, QList <ActionId> actions)
       : actions_(actions), coefficient_(coefficient), imagePath_(imagePath), name_(name)
{}

const QList <ActionId> & Terrain::actions() const
{
	return actions_;
}

quint8 Terrain::coefficient() const
{
	return coefficient_;
}

const QString &Terrain::imagePath() const
{
	return imagePath_;
}

const QString &Terrain::name() const
{
	return name_;
}
