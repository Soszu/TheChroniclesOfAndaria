#include "Core/Containers/Bases/QuestBase.h"

#include "Core/Utils/EnumHelpers.hpp"

const BiHash <QuestBase::Level, QString> QuestBase::LevelLabels = {
	{QuestBase::Level::Easy,   Labels::Quest::Levels::Easy},
	{QuestBase::Level::Medium, Labels::Quest::Levels::Medium},
	{QuestBase::Level::Hard,   Labels::Quest::Levels::Hard}
};

inline uint qHash(QuestBase::Level level)
{
	return qHash(toUnderlying(level));
}

QDataStream & operator<<(QDataStream &out, const QuestBase::Level &level)
{
	return out << toUnderlying(level);
}

QDataStream & operator>>(QDataStream &in, QuestBase::Level &level)
{
	return in >> toUnderlyingRef(level);
}

QuestBase::QuestBase(UID uid, QString title)
: uid_(uid),
  title_(title),
  fraction_(Kingdom::Neutral),
  level_(Level::Easy),
  isReturnRequired_(false),
  followUp_(Serial::EmptyUid),
  canBeDrawn_(true)
{}

QuestBase::QuestBase(UID uid,
                     const QString &title,
                     const QString &description,
                     Kingdom fraction,
                     QuestBase::Level level,
                     bool isReturnRequired,
                     UID followUp,
                     bool canBeDrawn,
                     const QHash <Coordinates, Test> &objectives,
                     const Prize &reward)
: uid_(uid),
  title_(title),
  description_(description),
  fraction_(fraction),
  level_(level),
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

QuestBase::Level QuestBase::level() const
{
	return level_;
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

QDataStream & QuestBase::toDataStream(QDataStream &out) const
{
	return out << uid_ << title_ << description_ << fraction_ << level_ << isReturnRequired_
	           << followUp_ << canBeDrawn_ << objectives_ << reward_;
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
	return in >> uid_ >> title_ >> description_ >> fraction_ >> level_ >> isReturnRequired_
	          >> followUp_ >> canBeDrawn_ >> objectives_ >> reward_;
}

void QuestBase::setCanBeDrawn(bool canBeDrawn)
{
	canBeDrawn_ = canBeDrawn;
}

void QuestBase::setDescription(const QString &description)
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

void QuestBase::setLevel(QuestBase::Level level)
{
	level_ = level;
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

QDataStream & operator<<(QDataStream &out, const QuestBase &base)
{
	return base.toDataStream(out);
}

QDataStream & operator>>(QDataStream &in, QuestBase &base)
{
	return base.fromDataStream(in);
}
