#ifndef HEALERWINDOW_H
#define HEALERWINDOW_H

#include <QtWidgets>

#include "Core/Containers/Player.h"
#include "Core/Game.h"
#include "Gui/PlayerWindow.h"

class HealerWindow : public QDialog {
	Q_OBJECT;
public:
	HealerWindow(Player *player, PlayerWindow *playerWindow);

private:
	Player *player_;
	PlayerWindow *playerWindow_;
	int wounds;
	int healthAfterHealing;

	QSlider *slider;
	QLabel *decisionLabel;

private slots:
	void confirm();
	void updateDecision(int goldPaid);
};

#endif
