#include "ConnectionAdapter.h"

ConnectionAdapter::ConnectionAdapter() : nextBlockSize_(0)
{}

void ConnectionAdapter::handleRead(QTcpSocket *socket, UID sender)
{
	QDataStream in(socket);
	in.setVersion(QDataStream::Qt_5_3);

	for(;;) {
		if (nextBlockSize_ == 0) {
			if ((size_t)socket->bytesAvailable() < sizeof(msg_size_t))
				break;
			in >>nextBlockSize_;
		}

		if (socket->bytesAvailable() < nextBlockSize_)
			break;

		Message msg(socket->read(nextBlockSize_));
		emit newMessage(msg, sender);

		nextBlockSize_ = 0;
	}
}
