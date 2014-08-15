#include "Core/Containers/Bases/QuestBase.h"
#include "Core/Utils/EnumHelpers.hpp"

static const BiHash <QuestBase::Level, QString> LevelLabels = {
	{QuestBase::Level::Easy, Label::Quest::Easy},
	{QuestBase::Level::Hard, Label::Quest::Medium},
	{QuestBase::Level::Hard, Label::Quest::Hard}
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
         : uid_(uid)
         , title_(title)
         , fraction_(Kingdom::Humans)
         , level_(Level::Easy)
         , isReturnRequired_(false)
         , followUp_(Serial::EmptyUid)
         , canBeDrawn_(true)
{}

QuestBase::QuestBase(UID uid,
                     const QString &title,
                     const QString &description,
                     Kingdom fraction,
                     QuestBase::Level level,
                     bool isReturnRequired,
                     UID followUp,
                     bool canBeDrawn,
                     const QMap <Coordinates, TestBase> &objectives,
                     const Prize &prize)
         : uid_(uid),
           title_(title),
           description_(description),
           fraction_(fraction),
           level_(level),
           isReturnRequired_(isReturnRequired),
           followUp_(followUp),
           canBeDrawn_(canBeDrawn),
           objectives_(objectives),
           prize_(prize)
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

const QMap <Coordinates, TestBase> & QuestBase::objectives() const
{
	return objectives_;
}

const Prize & QuestBase::prize() const
{
	return prize_;
}

const QString & QuestBase::title() const
{
	return title_;
}

QDataStream & QuestBase::toDataStream(QDataStream &out) const
{
	return out << uid_ << title_ << description_ << fraction_ << level_ << isReturnRequired_
	           << followUp_ << canBeDrawn_ /*<< objectives_ */<< prize_;
}

UID QuestBase::uid() const
{
	return uid_;
}

void QuestBase::addObjective(Coordinates coordinates, const TestBase &test)
{
// 	objectives_[coordinates] = test;
}

QDataStream & QuestBase::fromDataStream(QDataStream &in)
{
	return in >> uid_ >> title_ >> description_ >> fraction_ >> level_ >> isReturnRequired_
	          >> followUp_ >> canBeDrawn_ /*>> objectives_*/ >> prize_;
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

void QuestBase::setObjectives(const QMap <Coordinates, TestBase> &objectives)
{
	objectives_ = objectives;
}

void QuestBase::setPrize(const Prize &prize)
{
	prize_ = prize;
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
