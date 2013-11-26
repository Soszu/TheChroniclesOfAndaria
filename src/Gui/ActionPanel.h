#ifndef ACTIONPANEL_H
#define ACTIONPANEL_H

#include <QtWidgets>

#include "Core/Game.h"
#include "Core/GameMaster.h"
#include "Gui/CustomWidgets/MyButton.h"

class GameMaster;

//TODO CFiend przemyslec te klase, uzyc QSignalMapper gdzies?
class ActionPanel : public QObject {
	Q_OBJECT;
public:
	ActionPanel(QGroupBox *box);
	void displayActions(QList<QPair<int, QString> > *dzialania);
	void setGameMaster(GameMaster *gameMaster);

private:
	void wyczyscPanel();

	QVBoxLayout *uklad;
	QGroupBox *panel;
	GameMaster *gameMaster_;
	QList <MyButton *> przyciski;

private slots:
	void kliknietoPrzycisk(int n);
};

#endif
