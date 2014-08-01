#include "NewGameClt.h"

NewGameClt::NewGameClt(ConnectionAdapterClt *connectionAdapter) : connectionAdapter_(connectionAdapter)
{
	connect(connectionAdapter_, &ConnectionAdapter::newMessage, this, &NewGameClt::onNewMessage);
}

void NewGameClt::start()
{
	connectionAdapter_->connectToSrv();
}

void NewGameClt::onNewMessage(Message &msg)
{
}
