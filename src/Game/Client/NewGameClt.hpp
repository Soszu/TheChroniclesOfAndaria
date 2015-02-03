/*
Copyright (C) 2014-2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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

#include "Core/Containers/PlayerDraft.hpp"
#include "Game/Client/ConnectionAdapterClt.hpp"

class NewGameClt : public QObject {
	Q_OBJECT
public:
	NewGameClt(ConnectionAdapterClt *connectionAdapter);
	void start();

	const QVector <PlayerDraft> & otherPlayersDrafts() const;
	const PlayerDraft & myDraft() const;
	bool playerIsReady() const;

public slots:
	void setMyName(const QString &name);
	void setMyRace(Race playerRace);
	void setMyClass(Class playerClass);
	void setMyColor(const QColor &color);
	void switchPlayerIsReady();

private:
	void notifyAboutChanges();

	ConnectionAdapterClt *connectionAdapter_;
	QVector <PlayerDraft> otherPlayersDrafts_;
	PlayerDraft myDraft_;
	bool playerIsReady_;

private slots:
	void onNewMessage(Message &msg);

signals:
	void showGui();
	void newSettings();
	void gameSet();
};
