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
#include "Game/Server/ConnectionAdapterSrv.hpp"

class NewGameSrv : public QObject {
	Q_OBJECT

public:
	NewGameSrv() = default;

public slots:
	void onNewMessage(Message &msg, UID sender);
	void onUserEntered(UID userID);
	void onUserQuit(UID userID);

private:
	void gameReady();

	QHash <UID, PlayerDraft> playersDrafts_;
	QSet <UID> playersReady_;

signals:
	void gameSet(const QHash <UID, PlayerDraft> &);
};
