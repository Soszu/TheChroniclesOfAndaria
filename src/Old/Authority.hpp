#pragma once

#include <QtCore>
#include "Game/Common/Message.hpp"
#include "Core/Utils/Serial.hpp"

class Authority : public QObject {
protected:
	void switchToPredecessor() const;
	Authority *predecessor() const;
	virtual void onNewMessage(Message &msg, UID sender);
	virtual void onBecameReceiver(Authority *predecessor);

private:
	friend class ConnectionAdapter;
	void becameReceiver(Authority *predecessor);

	Authority *predecessor_;

signals:
	//Gives control to specified authority immediately
	//Next msg is guaranteed to be received by specified authority.
	//Writing code after emitting this signal is not recommended.
	void switchAuthority(Authority *authority);

	//Sends msg to recipient
	//Next msg is guaranteed to be received by this authority,
	void send(Message &msg, UID recipient);
};
