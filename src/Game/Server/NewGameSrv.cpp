#include "NewGameSrv.h"

NewGameSrv::NewGameSrv(GameCycle *gameCycle)
          : gameCycle_(gameCycle),
            connectionAdapter_(gameCycle_->connectionAdapter())
{
	connect(connectionAdapter_, &ConnectionAdapter::newMessage, this, &NewGameSrv::onNewMessage);
}

void NewGameSrv::waitForPlayers()
{
	connect(connectionAdapter_, &ConnectionAdapterSrv::newUser, this, &NewGameSrv::onUserEntered);
	connect(connectionAdapter_, &ConnectionAdapterSrv::userDisconnected, this, &NewGameSrv::onUserQuit);
	connectionAdapter_->startListen();
}

void NewGameSrv::onUserEntered(UID userID)
{
	// if not too much players
	//send playerDrafts

	// else send specific msg
}

void NewGameSrv::onUserQuit(UID userID)
{
	// remove draft
// 	send info
}

void NewGameSrv::onNewMessage(Message &msg, UID sender)
{
	// update info (sender may not has own draft yet)

	//if last ready -> begin (check number of players )

	//send to all but sender new info
}
