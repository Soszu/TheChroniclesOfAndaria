#include "NewGameSrv.h"

void NewGameSrv::gameReady()
{
	emit gameSet(playersDrafts_);
	switchToPredecessor();
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
