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
#pragma once

#include <QtCore>
#include "Core/Utils/EnumHelpers.hpp"

typedef quint16 msg_size_t;

enum class MsgType : quint16 {
	Undefined,
	JSON
};

class Message {

public:
	Message(QByteArray &&data);
	Message(MsgType msgType);
	MsgType msgType() const;
	const QByteArray & data() const;

	template<typename T>
	void write(T v)
	{
		QDataStream ds(&data_, QIODevice::ReadWrite);
		ds.setVersion(QDataStream::Qt_5_3);
		ds.device()->seek(data_.size());
		ds << v;
		ds.device()->seek(0);
		ds << msg_size_t(data_.size() - sizeof(msg_size_t));
	}

	template<typename T>
	void read(T *v)
	{
		QDataStream in(&data_, QIODevice::ReadWrite);
		in.setVersion(QDataStream::Qt_5_3);
		in.device()->seek(readPos_);
		in >> *v;
		readPos_ = in.device()->pos();
	}

private:
 	MsgType msgType_;
	QByteArray data_;
	qint64 readPos_;
};
