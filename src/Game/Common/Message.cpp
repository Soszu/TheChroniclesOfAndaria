#include "Message.h"

Editor::Messages::Message(QByteArray &&data) : msgType_(MsgType::Undefined), data_(data), readPos_(0)
{
	QDataStream in(&data_, QIODevice::ReadWrite);
	in.setVersion(QDataStream::Qt_5_3);
	in >> toUnderlyingRef(msgType_);
	readPos_ = in.device()->pos();
}

Editor::Messages::Message(MsgType msgType) : msgType_(msgType), readPos_(0)
{
	QDataStream out(&data_, QIODevice::ReadWrite);
	out.setVersion(QDataStream::Qt_5_3);
	out << msg_size_t(0) << toUnderlying(msgType_);
	out.device()->seek(0);
	out << msg_size_t(data_.size() - sizeof(msg_size_t));
}

MsgType Editor::Messages::msgType() const
{
	return msgType_;
}

const QByteArray & Editor::Messages::data() const
{
	return data_;
}
