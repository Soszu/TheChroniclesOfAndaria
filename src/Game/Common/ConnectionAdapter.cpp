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
#include "ConnectionAdapter.hpp"

ConnectionAdapter::ConnectionAdapter() :
	nextBlockSize_(0)
{}

void ConnectionAdapter::sendMessage(Message &msg, UID recipient) const
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

		nextBlockSize_ = 0;
	}
}
