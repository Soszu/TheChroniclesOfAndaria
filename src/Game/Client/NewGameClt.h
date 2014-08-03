#pragma once

#include "Core/Containers/PlayerDraft.h"
#include "Game/Client/ConnectionAdapterClt.h"

class NewGameClt : public QObject {
	Q_OBJECT
public:
	NewGameClt(ConnectionAdapterClt *connectionAdapter);
	void start();

	const QVector <PlayerDraft> & otherPlayersDrafts() const;
	const PlayerDraft & myDraft() const;
	bool playerIsReady() const;

public slots:
	void setMyName(const QString &name);
	void setMyRace(Race playerRace);
	void setMyClass(Class playerClass);
	void setMyColor(const QColor &color);
	void switchPlayerIsReady();

private:
	void notifyAboutChanges();

	ConnectionAdapterClt *connectionAdapter_;
	QVector <PlayerDraft> otherPlayersDrafts_;
	PlayerDraft myDraft_;
	bool playerIsReady_;

private slots:
	void onNewMessage(Message &msg);

signals:
	void showGui();
	void newSettings();
	void gameSet();
};
