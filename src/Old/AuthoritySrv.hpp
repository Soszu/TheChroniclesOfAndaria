#pragma once

#include <QtCore>
#include "Game/Common/Message.hpp"
#include "Core/Utils/Serial.hpp"

class Authority : public QObject {
public slots:

protected:
	void cedeControlToPredecessor() const;
	Authority *predecessor() const;
	virtual void onBecameReceiver(Authority *predecessor);
	virtual void onNewMessage(Message &msg, UID sender);

private:
	Authority *predecessor_;

private slots:
	friend class ConnectionAdapter;
	void becameReceiver(Authority *predecessor);

signals:
	//Gives control to specified authority immediately
	//Next msg is guaranteed to be received by specified authority.
	//Writing code after emitting this signal is not recommended.
	void cedeControl(Authority *authority);

	//Sends msg to recipient
	//Next msg is guaranteed to be received by this authority,
	void send(Message &msg, UID recipient);
};
