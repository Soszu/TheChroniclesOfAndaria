#pragma once

#include "Core/Containers/PlayerDraft.h"
#include "Game/Server/ConnectionAdapterSrv.h"
#include "Game/Server/GameCycleSrv.h"

class NewGameSrv : public QObject {
	Q_OBJECT
public:
	NewGameSrv(ConnectionAdapterSrv *connAdapter);
	void waitForPlayers();

private:
	void gameReady();

	ConnectionAdapterSrv *connAdapter_;
	QHash <UID, PlayerDraft> playersDrafts_;
	QSet <UID> playersReady_;

private slots:
	void onUserEntered(UID userID);
	void onUserQuit(UID userID);
	void onNewMessage(Message &msg, UID sender);

signals:
	void gameSet(const QHash <UID, PlayerDraft> &);
};
