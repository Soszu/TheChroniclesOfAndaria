#include "ConnectionAdapterClt.h"

ConnectionAdapterClt::ConnectionAdapterClt() : tcpSocket_(this)
{
	connect(&tcpSocket_, &QTcpSocket::readyRead, this, &ConnectionAdapterClt::onRead);
	connect(&tcpSocket_, &QTcpSocket::connected, this, &ConnectionAdapterClt::connected);
}

void ConnectionAdapterClt::connectToSrv()
{
	tcpSocket_.connectToHost("localhost", DefaultSrvPort);
}

void ConnectionAdapterClt::sendMessage(Message &msg, UID recipient) const
{
	tcpSocket_.write(msg.data());
}

void ConnectionAdapterClt::onRead()
{
	handleRead(&tcpSocket_);
}
