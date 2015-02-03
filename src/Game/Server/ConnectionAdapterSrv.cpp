/*
Copyright (C) 2014-2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
This file is part of The Chronicles Of Andaria Project.

	The Chronicles of Andaria Project is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	The Chronicles of Andaria Project is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with The Chronicles Of Andaria.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "ConnectionAdapterSrv.hpp"

ConnectionAdapterSrv::ConnectionAdapterSrv() :
	tcpServer_(this),
	msgSignalMapper_(this),
	disconnectSignalMapper_(this)
{
	connect(&tcpServer_, &QTcpServer::newConnection, this, &ConnectionAdapterSrv::handleNewConnection);
	connect(&msgSignalMapper_, static_cast<void (QSignalMapper::*)(int)>(&QSignalMapper::mapped),
	        this, &ConnectionAdapterSrv::handleMessage);
	connect(&disconnectSignalMapper_, static_cast<void (QSignalMapper::*)(int)>(&QSignalMapper::mapped),
			this, &ConnectionAdapterSrv::handleDisconnected);
}

void ConnectionAdapterSrv::startListen()
{
	if (!tcpServer_.listen(QHostAddress::Any, DefaultSrvPort)) {
		qDebug() << Server::Errors::ListenFail.arg(tcpServer_.errorString());
		return;
	}
	qDebug() << Server::Logs::ServerIsListening.arg(QString::number(DefaultSrvPort));
}

void ConnectionAdapterSrv::sendMessage(Message &msg, UID recipient) const
{
	connectedUsers_[recipient]->write(msg.data());
}

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
