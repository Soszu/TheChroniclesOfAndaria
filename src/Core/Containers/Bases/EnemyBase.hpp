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

#include <QtGui>

#include "Core/Containers/Prize.hpp"
#include "Core/Containers/Effect.hpp"
#include "Core/Utils/Serial.hpp"
#include "Core/EnumsDeclarations.hpp"

enum class Attack : quint8 ;

class EnemyBase {
public:
	enum class Type : quint8 {
		Beast,
		Deamon,
		Humanoid,
		Undead,
	};
	static const BiHash <Type, QString> TypeLabels;

	EnemyBase(UID uid = Serial::MinUid, QString name = QString());

	const QString & name() const;
	const QString & imageName() const;
	const QPixmap & avatar() const;
	quint8 level() const;
	Type type() const;
	Attack defaultAttack() const;
	const QList <Effect> & baseStats() const;
	const Prize & prize() const;
	QDataStream & toDataStream(QDataStream &out) const;
	UID uid() const;

	void setName(const QString & name);
	void setImageName(const QString & imageName);
	void setLevel(quint8 level);
	void setType(Type type);
	void setDefaultAttack(Attack type);
	void addStat(const Effect & effect);
	QDataStream & fromDataStream(QDataStream & in);
	void setBaseStats(const QList <Effect> & baseStats);
	void setPrize(const Prize & prize);

private:
	UID uid_;
	QString name_;
	QString imageName_;
	qint8 level_;
	Type type_;
	Attack defaultAttack_;
	QList <Effect> baseStats_;
	Prize prize_;
};
Q_DECLARE_METATYPE(EnemyBase::Type)
uint qHash(EnemyBase::Type t);
QDataStream & operator<<(QDataStream &out, const EnemyBase &base);
QDataStream & operator>>(QDataStream &in, EnemyBase &base);
