#ifndef CONNECTIONADAPTER_H
#define CONNECTIONADAPTER_H

#include <QtCore>
#include "Game/Server/Strings.h"
#include "Core/Util/Serial.hpp"
#include "Game/Common/ConnectionAdapter.h"

class ConnectionAdapterSrv : public ConnectionAdapter
{
	Q_OBJECT
	static const quint16 srvPort = 42121;
	static const int ListenError = 1;

public:
	ConnectionAdapterSrv();
	void startListen();
	void sendToClt(UID userID, Message &msg);

private:
	void initServer();
	QTcpServer tcpServer;
	Serial usersIDs;
	QHash <UID, QTcpSocket *> connectedUsers;

private slots:
	void handleNewConnection();
	void handleMessage(UID userID);

signals:
	void newUser(UID userID);

private:
	QSignalMapper signalMapper_;
};


#endif // CONNECTIONADAPTER_H
