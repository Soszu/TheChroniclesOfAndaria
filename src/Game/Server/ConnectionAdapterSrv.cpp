#include "ConnectionAdapterSrv.h"

ConnectionAdapterSrv::ConnectionAdapterSrv() : tcpServer_(this), msgSignalMapper_(this), disconnectSignalMapper_(this)
{
	initServer();
	connect(&tcpServer_, &QTcpServer::newConnection, this, &ConnectionAdapterSrv::handleNewConnection);
	connect(&msgSignalMapper_, static_cast<void (QSignalMapper::*)(int)>(&QSignalMapper::mapped),
	        this, &ConnectionAdapterSrv::handleMessage);
	connect(&disconnectSignalMapper_, static_cast<void (QSignalMapper::*)(int)>(&QSignalMapper::mapped),
			this, &ConnectionAdapterSrv::handleDisconnected);
}

void ConnectionAdapterSrv::startListen()
{
	if (!tcpServer_.listen(QHostAddress::Any, srvPort)) {
		qDebug() << Server::Errors::ListenFail.arg(tcpServer_.errorString());
		return;
	}
	qDebug() << Server::Logs::ServerIsListening.arg(QString::number(srvPort));
}

void ConnectionAdapterSrv::sendToClt(UID userID, Message &msg)
{
	connectedUsers_[userID]->write(msg.data());
}

void ConnectionAdapterSrv::initServer()
{}

void ConnectionAdapterSrv::handleNewConnection()
{
	UID userID = usersIDs_.next();
	qDebug() << Server::Logs::ClientConnected.arg(QString::number(userID));

	QTcpSocket *nextConnection = tcpServer_.nextPendingConnection();
	connectedUsers_.insert(userID, nextConnection);

	connect(nextConnection, &QTcpSocket::readyRead,
	        &msgSignalMapper_, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
	msgSignalMapper_.setMapping(nextConnection, userID);
	connect(nextConnection, &QTcpSocket::disconnected,
			&disconnectSignalMapper_, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
	disconnectSignalMapper_.setMapping(nextConnection, userID);

	emit newUser(userID);
}

void ConnectionAdapterSrv::handleMessage(UID userID)
{
	handleRead(connectedUsers_[userID], userID);
}

void ConnectionAdapterSrv::handleDisconnected(UID userID)
{
	qDebug() << Server::Logs::ClientDisconnected.arg(QString::number(userID));
	emit userDisconnected(userID);
}
