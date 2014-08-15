#pragma once

#include <QtNetwork>
#include "Game/Common/Authority.h"
#include "Core/Utils/Serial.hpp"

class ConnectionAdapter : public QObject {
	Q_OBJECT
public:
	static const quint16 DefaultSrvPort = 42121;
	ConnectionAdapter();

public slots:
	virtual void sendMessage(Message &msg, UID recipient) const;
	void setAuthorityInControl(Authority *authority);

protected:
	void handleRead(QTcpSocket *socket, UID sender = Serial::EmptyUid);

private:
	Authority *authorityInControl_;
	msg_size_t nextBlockSize_;
};
