#pragma once

#include <QtNetwork>
#include "Game/Common/Message.h"
#include "Core/Util/Serial.hpp"

class ConnectionAdapter : public QObject
{
	Q_OBJECT
public:
	ConnectionAdapter();
	void handleRead(QTcpSocket *socket, UID sender = Serial::EmptyUid);

signals:
	void newMessage(Message &msg, UID sender);

private:
	msg_size_t nextBlockSize_;
};