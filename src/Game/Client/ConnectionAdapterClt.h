#ifndef CONNECTIONADAPTERCLT_H
#define CONNECTIONADAPTERCLT_H

#include "Game/Common/ConnectionAdapter.h"

class ConnectionAdapterClt : public ConnectionAdapter
{
	Q_OBJECT
public:
	ConnectionAdapterClt();
	void connectToSrv();
	void sendToSrv(Message &msg);

private slots:
	void onRead();

private:
	QTcpSocket tcpSocket_;

};

#endif // CONNECTIONADAPTERCLT_H
