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
