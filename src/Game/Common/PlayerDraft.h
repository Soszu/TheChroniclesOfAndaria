#pragma once

#include "Core/Containers/Player.h"

static const int MinPlayers = 2;
static const int MaxPlayers = 8;
static const int MaxNameLength = 20;

struct PlayerDraft {
public:
	PlayerDraft();
	const QString & name() const;
	const QColor & color() const;
	Race playerRace() const;
	Class playerClass() const;
	void setName(const QString &name);
	void setPlayerRace(Race playerRace);
	void setPlayerClass(Class playerClass);
	void setColor(const QColor &color);

private:
	QString generateRandomName();
	QColor generateRandomColor();

	QString name_;
	Race playerRace_;
	Class playerClass_;
	QColor color_;
};
