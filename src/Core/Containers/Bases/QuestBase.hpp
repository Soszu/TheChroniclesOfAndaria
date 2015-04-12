/*
Copyright (C) 2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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

#include "Core/EnumsDeclarations.hpp"
#include "Core/Utils/BiHash.hpp"
#include "Core/Utils/Serial.hpp"
#include "Core/Containers/Coordinates.hpp"
#include "Core/Containers/Tests/TestData.hpp"
#include "Core/Containers/Prize.hpp"

class QuestBase {

public:
	QuestBase(UID uid = Serial::EmptyUid, QString title = {});
	QuestBase(UID uid,
	          const QString & title,
	          const QString & description,
	          Kingdom fraction,
	          int level,
	          Difficulty difficulty,
	          bool isReturnRequired,
	          UID followUp,
	          bool canBeDrawn,
	          const QHash<Coordinates, TestData> & objectives,
	          const Prize & reward);

	bool canBeDrawn() const;
	const QString & description() const;
	const UID followUp() const;
	Kingdom fraction() const;
	bool isReturnRequired() const;
	int level() const;
	Difficulty difficulty() const;
	const QHash<Coordinates, TestData> & objectives() const;
	const Prize & reward() const;
	const QString & title() const;
	QDataStream & toDataStream(QDataStream & out) const;
	UID uid() const;

	void addObjective(Coordinates coordinates, const TestData & test);
	QDataStream & fromDataStream(QDataStream & in);
	void setCanBeDrawn(bool canBeDrawn);
	void setDescription (const QString & description);
	void setFollowUp(UID followUp);
	void setFraction(Kingdom fraction);
	void setIsReturnRequired(bool isReturnRequired);
	void setLevel(int level);
	void setDifficulty(Difficulty difficulty);
	void setObjectives(const QHash<Coordinates, TestData> & objectives);
	void setReward(const Prize & reward);
	void setTitle(const QString & title);

private:
	UID uid_;
	QString title_;
	QString description_;
	Kingdom fraction_;
	int level_;
	Difficulty difficulty_;
	bool isReturnRequired_;
	UID followUp_;
	bool canBeDrawn_;
	QHash<Coordinates, TestData> objectives_;
	Prize reward_;
};
QDataStream & operator<<(QDataStream & out, const QuestBase & base);
QDataStream & operator>>(QDataStream & in, QuestBase & base);
