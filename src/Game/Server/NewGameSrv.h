#ifndef NEWGAMESRV_H
#define NEWGAMESRV_H

#include "Game/Server/ConnectionAdapterSrv.h"
#include "Game/Server/GameCycle.h"

class NewGameSrv : public QObject
{
	Q_OBJECT
public:
	NewGameSrv(GameCycle * gameCycle);
	void waitForPlayers();

private:
	GameCycle * gameCycle_;
	ConnectionAdapterSrv *connectionAdapter_;

private slots:
	void onNewUser(UID userID);
	void onNewMessage(Message &msg);
};

#endif // NEWGAMESRV_H
