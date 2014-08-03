#include "PlayerDraft.h"

PlayerDraft::PlayerDraft()
           : name_(generateRandomName()),
             playerRace_(Race::Human),
             playerClass_(Class::Fighter),
             color_(generateRandomColor())
{}

const QString & PlayerDraft::name() const
{
	return name_;
}

Race PlayerDraft::playerRace() const
{
	return playerRace_;
}

Class PlayerDraft::playerClass() const
{
	return playerClass_;
}

const QColor& PlayerDraft::color() const
{
	return color_;
}

void PlayerDraft::setName(const QString &name)
{
	name_ = name;
}

void PlayerDraft::setPlayerRace(Race playerRace)
{
	playerRace_ = playerRace;
}

void PlayerDraft::setPlayerClass(Class playerClass)
{
	playerClass_ = playerClass;
}

void PlayerDraft::setColor(const QColor &color)
{
	color_ = color;
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

QColor PlayerDraft::generateRandomColor()
{
	return QColor(static_cast<Qt::GlobalColor>(qrand() % 20));
}
