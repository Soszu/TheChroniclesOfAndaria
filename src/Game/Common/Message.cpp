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
#include "Message.hpp"

Message::Message(QByteArray &&data) :
	msgType_(MsgType::Undefined),
	data_(data),
	readPos_(0)
{
	QDataStream in(&data_, QIODevice::ReadWrite);
	in.setVersion(QDataStream::Qt_5_3);
	in >> toUnderlyingRef(msgType_);
	readPos_ = in.device()->pos();
}

Message::Message(MsgType msgType) : msgType_(msgType), readPos_(0)
{
	QDataStream out(&data_, QIODevice::ReadWrite);
	out.setVersion(QDataStream::Qt_5_3);
	out << msg_size_t(0) << toUnderlying(msgType_);
	out.device()->seek(0);
	out << msg_size_t(data_.size() - sizeof(msg_size_t));
}

MsgType Message::msgType() const
{
	return msgType_;
}

const QByteArray & Message::data() const
{
	return data_;
}
