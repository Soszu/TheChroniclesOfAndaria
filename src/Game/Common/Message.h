#pragma once

#include <QtCore>
#include "Core/Utils/EnumHelpers.hpp"

typedef quint16 msg_size_t;

enum class MsgType : quint16 {
	Undefined,
	JSON
};

class Message
{
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
