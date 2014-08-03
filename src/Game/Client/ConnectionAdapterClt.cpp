#include "ConnectionAdapterClt.h"

ConnectionAdapterClt::ConnectionAdapterClt() : tcpSocket_(this)
{
	connect(&tcpSocket_, &QTcpSocket::readyRead, this, &ConnectionAdapterClt::onRead);
	connect(&tcpSocket_, &QTcpSocket::connected, this, &ConnectionAdapterClt::connected);
}

void ConnectionAdapterClt::connectToSrv()
{
	tcpSocket_.connectToHost("localhost", 42121);
}

void ConnectionAdapterClt::sendToSrv(Message &msg)
{
	tcpSocket_.write(msg.data());
}

void ConnectionAdapterClt::onRead()
{
	handleRead(&tcpSocket_);
}
