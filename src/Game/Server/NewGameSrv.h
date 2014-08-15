#pragma once

#include "Core/Containers/PlayerDraft.h"
#include "Game/Server/ConnectionAdapterSrv.h"
#include "Game/Common/Authority.h"

class NewGameSrv : public Authority {
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
