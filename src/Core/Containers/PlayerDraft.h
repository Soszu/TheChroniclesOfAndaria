#pragma once

#include <QtWidgets>
#include "Core/Strings.h"

enum class Race : quint8 {
	Human,
	Dwarf,
	Elf,
	Halfling
};
uint qHash(Race playerRace);
QDataStream & operator<<(QDataStream &out, const Race &playerRace);
QDataStream & operator>>(QDataStream &in, Race &playerRace);

enum class Class : quint8 {
	Fighter,
	Hunter,
	Mage,
	Druid
};
uint qHash(Class playerClass);
QDataStream & operator<<(QDataStream &out, const Class &playerClass);
QDataStream & operator>>(QDataStream &in, Class &playerClass);


static const int MinPlayers = 2;
static const int MaxPlayers = 8;
static const int MaxNameLength = 20;

struct PlayerDraft {
public:
	PlayerDraft();
	const QColor & color() const;
	const QString & name() const;
	Class playerClass() const;
	Race playerRace() const;
	QDataStream & toDataStream(QDataStream &out) const;

	QDataStream & fromDataStream(QDataStream &in);
	void setAvatar(const QPixmap &pixmap);
	void setColor(const QColor &color);
	void setName(const QString &name);
	void setPlayerClass(Class playerClass);
	void setPlayerRace(Race playerRace);

private:
	QColor generateRandomColor();
	QString generateRandomName();

	QColor color_;
	QString name_;
	Class playerClass_;
	Race playerRace_;
};
