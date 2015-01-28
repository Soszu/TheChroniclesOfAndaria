/*
 * Copyright (C) 2013 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
 * This file is part of The Chronicles Of Andaria Project.
 *
 *	The Chronicles of Andaria Project is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	The Chronicles of Andaria Project is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with The Chronicles Of Andaria.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "Core/Utils/BiHash.hpp"
#include "Core/Utils/Serial.hpp"
#include "Core/Containers/Coordinates.hpp"
#include "Core/Containers/Test.h"
#include "Core/Containers/Prize.h"

class QuestBase {
public:
	enum class Level : quint8 {
		Easy,
		Medium,
		Hard
	};
	static const BiHash <Level, QString> LevelLabels;

	QuestBase(UID uid, QString title);
	QuestBase(UID uid,
	          const QString &title,
	          const QString &description,
	          Kingdom fraction,
	          Level level,
	          bool isReturnRequired,
	          UID followUp,
	          bool canBeDrawn,
	          const QHash <Coordinates, Test> &objectives,
	          const Prize &prize);

	bool canBeDrawn() const;
	const QString & description() const;
	const UID followUp() const;
	Kingdom fraction() const;
	bool isReturnRequired() const;
	Level level() const;
	const QHash <Coordinates, Test> & objectives() const;
	const Prize & prize() const;
	const QString & title() const;
	QDataStream & toDataStream(QDataStream &out) const;
	UID uid() const;

	void addObjective(Coordinates coordinates, const Test &test);
	QDataStream & fromDataStream(QDataStream &in);
	void setCanBeDrawn(bool canBeDrawn);
	void setDescription (const QString &description);
	void setFollowUp(UID followUp);
	void setFraction(Kingdom fraction);
	void setIsReturnRequired(bool isReturnRequired);
	void setLevel(Level level);
	void setObjectives(const QHash <Coordinates, Test> &objectives);
	void setPrize(const Prize &prize);
	void setTitle(const QString &title);

private:
	UID uid_;
	QString title_;
	QString description_;
	Kingdom fraction_;
	Level level_;
	bool isReturnRequired_;
	UID followUp_;
	bool canBeDrawn_;
	QHash <Coordinates, Test> objectives_;
	Prize prize_;
};
QDataStream & operator<<(QDataStream &out, const QuestBase &base);
QDataStream & operator>>(QDataStream &in, QuestBase &base);
uint qHash(QuestBase::Level level);
QDataStream & operator<<(QDataStream &out, const QuestBase::Level &level);
QDataStream & operator>>(QDataStream &in, QuestBase::Level &level);
