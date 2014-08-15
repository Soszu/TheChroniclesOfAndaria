#pragma once

#include "Game/Common/ConnectionAdapter.h"

class ConnectionAdapterClt : public ConnectionAdapter {
	Q_OBJECT
public:
	ConnectionAdapterClt();
	void connectToSrv();

public slots:
	virtual void sendMessage(Message &msg, UID recipient) const;

private slots:
	void onRead();

private:
	QTcpSocket tcpSocket_;

signals:
	void connected();
};
