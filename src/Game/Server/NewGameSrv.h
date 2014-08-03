#pragma once

#include "Game/Server/ConnectionAdapterSrv.h"
#include "Game/Server/GameCycle.h"
#include "Game/Common/PlayerDraft.h"

class NewGameSrv : public QObject {
	Q_OBJECT
public:
	NewGameSrv(GameCycle * gameCycle);
	void waitForPlayers();

private:
	GameCycle * gameCycle_;
	ConnectionAdapterSrv *connectionAdapter_;

	QVector <PlayerDraft> playersDrafts_;

private slots:
	void onUserEntered(UID userID);
	void onUserQuit(UID userID);
	void onNewMessage(Message &msg, UID sender);
};
