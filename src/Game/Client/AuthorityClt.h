#pragma once

#include "Game/Common/Authority.h"

class AuthorityClt : public Authority {
protected:
	virtual void onNewMessage(Message &msg, UID sender);
	virtual void onNewMessage(Message &msg);

signals:
	//Sends msg to server
	//Next msg is guaranteed to be received by this authority,
	void send(Message &msg);
};
