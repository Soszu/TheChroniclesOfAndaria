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
#include "QuestBase.hpp"

#include "Core/Enums.hpp"
#include "Core/Utils/EnumHelpers.hpp"

QuestBase::QuestBase(UID uid, QString title) :
	uid_(uid),
	title_(title),
	fraction_(Kingdom::Neutral),
	level_(1),
	difficulty_(Difficulty::Easy),
	isReturnRequired_(false),
	followUp_(Serial::EmptyUid),
	canBeDrawn_(true)
{}

QuestBase::QuestBase(UID uid,
                     const QString & title,
                     const QString & description,
                     Kingdom fraction,
                     int level,
                     Difficulty difficulty,
                     bool isReturnRequired,
                     UID followUp,
                     bool canBeDrawn,
                     const QHash <Coordinates, Test> & objectives,
                     const Prize & reward) :
	uid_(uid),
	title_(title),
	description_(description),
	fraction_(fraction),
	level_(level),
	difficulty_(difficulty),
	isReturnRequired_(isReturnRequired),
	followUp_(followUp),
	canBeDrawn_(canBeDrawn),
	objectives_(objectives),
	reward_(reward)
{}

bool QuestBase::canBeDrawn() const
{
	return canBeDrawn_;
}

const QString & QuestBase::description() const
{
	return description_;
}

const UID QuestBase::followUp() const
{
	return followUp_;
}

Kingdom QuestBase::fraction() const
{
	return fraction_;
}

bool QuestBase::isReturnRequired() const
{
	return isReturnRequired_;
}

int QuestBase::level() const
{
	return level_;
}

Difficulty QuestBase::difficulty() const
{
	return difficulty_;
}

const QHash <Coordinates, Test> & QuestBase::objectives() const
{
	return objectives_;
}

const Prize & QuestBase::reward() const
{
	return reward_;
}

const QString & QuestBase::title() const
{
	return title_;
}

QDataStream & QuestBase::toDataStream(QDataStream & out) const
{
	return out << uid_ << title_ << description_ << fraction_ << level_ << difficulty_
	           << isReturnRequired_ << followUp_ << canBeDrawn_ << objectives_ << reward_;
}

UID QuestBase::uid() const
{
	return uid_;
}

void QuestBase::addObjective(Coordinates coordinates, const Test &test)
{
	objectives_[coordinates] = test;
}

QDataStream & QuestBase::fromDataStream(QDataStream &in)
{
	return in >> uid_ >> title_ >> description_ >> fraction_ >> level_ >> difficulty_
	          >> isReturnRequired_ >> followUp_ >> canBeDrawn_ >> objectives_ >> reward_;
}

void QuestBase::setCanBeDrawn(bool canBeDrawn)
{
	canBeDrawn_ = canBeDrawn;
}

void QuestBase::setDescription(const QString & description)
{
	description_ = description;
}

void QuestBase::setFollowUp(UID followUp)
{
	followUp_ = followUp;
}

void QuestBase::setFraction(Kingdom fraction)
{
	fraction_ = fraction;
}

void QuestBase::setIsReturnRequired(bool isReturnRequired)
{
	isReturnRequired_ = isReturnRequired;
}

void QuestBase::setLevel(int level)
{
	level_ = level;
}

void QuestBase::setDifficulty(Difficulty difficulty)
{
	difficulty_ = difficulty;
}

void QuestBase::setObjectives(const QHash <Coordinates, Test> &objectives)
{
	objectives_ = objectives;
}

void QuestBase::setReward(const Prize &reward)
{
	reward_ = reward;
}

void QuestBase::setTitle(const QString &title)
{
	title_ = title;
}

QDataStream & operator<<(QDataStream & out, const QuestBase & base)
{
	return base.toDataStream(out);
}

QDataStream & operator>>(QDataStream & in, QuestBase & base)
{
	return base.fromDataStream(in);
}
