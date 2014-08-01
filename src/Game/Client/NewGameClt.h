#ifndef NEWGAMECLT_H
#define NEWGAMECLT_H

#include "Game/Client/ConnectionAdapterClt.h"

class NewGameClt : public QObject
{
	Q_OBJECT
public:
	NewGameClt(ConnectionAdapterClt *connectionAdapter);
	void start();

private:
	ConnectionAdapterClt *connectionAdapter_;

private slots:
	void onNewMessage(Message &msg);
};

#endif // NEWGAMECLT_H
