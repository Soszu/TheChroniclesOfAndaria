#include "ConnectionAdapter.h"

ConnectionAdapter::ConnectionAdapter() : authorityInControl_(nullptr), nextBlockSize_(0)
{}

void ConnectionAdapter::sendMessage(Message &msg, UID recipient) const
{}

void ConnectionAdapter::setAuthorityInControl(Authority *authority)
{
	if (authorityInControl_ != nullptr) {
		disconnect(authorityInControl_, &Authority::send, this, &ConnectionAdapter::sendMessage);
		disconnect(authorityInControl_, &Authority::switchAuthority, this, &ConnectionAdapter::setAuthorityInControl);
	}

	authorityInControl_ = authority;
	connect(authorityInControl_, &Authority::send, this, &ConnectionAdapter::sendMessage);
	connect(authorityInControl_, &Authority::switchAuthority, this, &ConnectionAdapter::setAuthorityInControl);
	authority->becameReceiver();
}

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
		authorityInControl_->onNewMessage(msg, sender);

		nextBlockSize_ = 0;
	}
}
