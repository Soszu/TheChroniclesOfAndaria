#include "NewGameSrv.h"

NewGameSrv::NewGameSrv(GameCycle *gameCycle)
          : gameCycle_(gameCycle),
            connectionAdapter_(gameCycle_->connectionAdapter())
{
	connect(connectionAdapter_, &ConnectionAdapter::newMessage, this, &NewGameSrv::onNewMessage);
}

void NewGameSrv::waitForPlayers()
{
	connect(connectionAdapter_, &ConnectionAdapterSrv::newUser, this, &NewGameSrv::onNewUser);
	connectionAdapter_->startListen();
}

void NewGameSrv::onNewUser(UID userID)
{
}

void NewGameSrv::onNewMessage(Message &msg)
{
}
