#include "Core/Containers/PlayerDraft.h"

PlayerDraft::PlayerDraft()
: color_(generateRandomColor()),
  name_(generateRandomName()),
  playerClass_(Class::Fighter),
  playerRace_(Race::Human)
{}

const QColor & PlayerDraft::color() const
{
	return color_;
}

const QString & PlayerDraft::name() const
{
	return name_;
}

Class PlayerDraft::playerClass() const
{
	return playerClass_;
}

Race PlayerDraft::playerRace() const
{
	return playerRace_;
}

QDataStream & PlayerDraft::toDataStream(QDataStream &out) const
{
	return out << color_ << name_ << playerClass_ << playerRace_;
}

QDataStream & PlayerDraft::fromDataStream(QDataStream &in)
{
	return in >> color_ >> name_ >> playerClass_ >> playerRace_;
}

void PlayerDraft::setColor(const QColor &color)
{
	color_ = color;
}

void PlayerDraft::setName(const QString &name)
{
	name_ = name;
}

void PlayerDraft::setPlayerClass(Class playerClass)
{
	playerClass_ = playerClass;
}

void PlayerDraft::setPlayerRace(Race playerRace)
{
	playerRace_ = playerRace;
}

QColor PlayerDraft::generateRandomColor()
{
	return QColor(static_cast<Qt::GlobalColor>(qrand() % 20));
}

QString PlayerDraft::generateRandomName()
{
	const int NameLength = 7;
	QString name;
	for (int i = 0; i < NameLength; ++i)
		name += (char)('a'+ qrand() % 26);
	name[0] = name[0].toUpper();
	return name;
}

QDataStream & operator<<(QDataStream &out, const PlayerDraft &draft)
{
	return draft.toDataStream(out);
}

QDataStream & operator>>(QDataStream &in, PlayerDraft &draft)
{
	return draft.fromDataStream(in);
}
