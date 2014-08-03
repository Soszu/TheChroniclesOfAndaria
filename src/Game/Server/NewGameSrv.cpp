#include "NewGameSrv.h"

NewGameSrv::NewGameSrv(ConnectionAdapterSrv *connAdapter) : connAdapter_(connAdapter)
{}

void NewGameSrv::waitForPlayers()
{
	connect(connAdapter_, &ConnectionAdapterSrv::newUser, this, &NewGameSrv::onUserEntered);
	connect(connAdapter_, &ConnectionAdapterSrv::userDisconnected, this, &NewGameSrv::onUserQuit);
	connect(connAdapter_, &ConnectionAdapter::newMessage, this, &NewGameSrv::onNewMessage);
	connAdapter_->startListen();
}

void NewGameSrv::gameReady()
{
// TODO	send game ready
	disconnect(connAdapter_, &ConnectionAdapterSrv::newUser, this, &NewGameSrv::onUserEntered);
	disconnect(connAdapter_, &ConnectionAdapterSrv::userDisconnected, this, &NewGameSrv::onUserQuit);
	disconnect(connAdapter_, &ConnectionAdapter::newMessage, this, &NewGameSrv::onNewMessage);
	emit gameSet(playersDrafts_);
}

void NewGameSrv::onUserEntered(UID userID)
{
	// if not too much players
	//send playerDrafts

	// else send specific 'too much' msg
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
	if (playersDrafts_.count() >= MinPlayers && playersReady_.count() == playersDrafts_.count())
		gameReady();

	//send to all but sender new info
}
