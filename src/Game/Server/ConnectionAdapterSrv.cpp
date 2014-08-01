#include "ConnectionAdapterSrv.h"

ConnectionAdapterSrv::ConnectionAdapterSrv() : tcpServer(this), signalMapper_(this)
{
	initServer();
	connect(&tcpServer, &QTcpServer::newConnection, this, &ConnectionAdapterSrv::handleNewConnection);
	connect(&signalMapper_, static_cast<void (QSignalMapper::*)(int)>(&QSignalMapper::mapped), this, &ConnectionAdapterSrv::handleMessage);
}

void ConnectionAdapterSrv::startListen()
{
	if (!tcpServer.listen(QHostAddress::Any, srvPort)) {
		qDebug() << Server::Errors::ListenFail.arg(tcpServer.errorString());
		return;
	}
	qDebug() << Server::Logs::ServerIsListening.arg(QString::number(srvPort));
}

void ConnectionAdapterSrv::sendToClt(UID userID, Message &msg)
{
	connectedUsers[userID]->write(msg.data());
}

void ConnectionAdapterSrv::initServer()
{}

void ConnectionAdapterSrv::handleNewConnection()
{
	qDebug() << Server::Logs::ClientConnected;

	UID userID = usersIDs.next();
	QTcpSocket *nextConnection = tcpServer.nextPendingConnection();
	connectedUsers.insert(userID, nextConnection);

	connect(nextConnection, &QTcpSocket::readyRead, &signalMapper_, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
	signalMapper_.setMapping(nextConnection, userID);

	emit newUser(userID);
}

void ConnectionAdapterSrv::handleMessage(UID userID)
{
	handleRead(connectedUsers[userID], userID);
}
