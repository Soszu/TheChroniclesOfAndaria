#pragma once

#include <QtCore>
#include "Game/Server/Strings.h"
#include "Core/Util/Serial.hpp"
#include "Game/Common/ConnectionAdapter.h"

class ConnectionAdapterSrv : public ConnectionAdapter {
	Q_OBJECT
public:
	ConnectionAdapterSrv();
	void startListen();

	static const quint16 srvPort = 42121;
	static const int ListenError = 1;

public slots:
	void sendToClt(UID userID, Message &msg);

private:
	void initServer();

	QTcpServer tcpServer_;
	Serial usersIDs_;
	QHash <UID, QTcpSocket *> connectedUsers_;
	QSignalMapper msgSignalMapper_;
	QSignalMapper disconnectSignalMapper_;

private slots:
	void handleNewConnection();
	void handleMessage(UID userID);
	void handleDisconnected(UID userID);

signals:
	void newUser(UID userID);
	void userDisconnected(UID userID);
};
