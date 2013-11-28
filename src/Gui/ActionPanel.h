#ifndef ACTIONPANEL_H
#define ACTIONPANEL_H

#include <QtWidgets>

#include "Core/Game.h"
#include "Core/GameMaster.h"

class GameMaster;

class ActionPanel : public QGroupBox {
	Q_OBJECT;
public:
	ActionPanel(GameMaster *gameMaster);
	void displayActions(const QList <QPair <int, QString> > &actions);

private:
	void clearPanel();

	GameMaster *const gameMaster_;

	QVBoxLayout *buttonLayout;
	QSignalMapper *buttonMapper;
	QList <QPushButton *> buttons;

private slots:
	void executeAction(int actionId);
};

#endif
