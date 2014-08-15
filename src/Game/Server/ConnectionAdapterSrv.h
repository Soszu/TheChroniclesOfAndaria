#pragma once

#include <QtCore>
#include "Game/Server/Strings.h"
#include "Core/Utils/Serial.hpp"
#include "Game/Common/ConnectionAdapter.h"

class ConnectionAdapterSrv : public ConnectionAdapter {
	Q_OBJECT
public:
	ConnectionAdapterSrv();
	void startListen();

public slots:
	virtual void sendMessage(Message &msg, UID recipient) const;

private:
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
