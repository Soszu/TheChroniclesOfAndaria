#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#include <QtWidgets>

#include "Core/Containers/Player.h"
#include "Core/Game.h"
#include "Gui/CustomWidgets/MyTaskbar.h"
#include "Gui/Windows/EquipmentWindow.h"
#include "Gui/Windows/QuestWindow.h"

class EquipmentWindow;
class QuestWindow;
class GameMaster;

//TODO CFiend general cleanup

class PlayerWindow : public QObject {
	friend class EquipmentWindow;
	Q_OBJECT;
public:
	PlayerWindow(QFrame *frame);
	void displayPlayer(Player *player);
	void update();
	void setGameMaster(GameMaster *gameMaster);

private:
	GameMaster *gameMaster_;
	EquipmentWindow *equipmentWindow_;
	QuestWindow *questWindow_;
	Player *currentPlayer;

	QHBoxLayout* reputacja;
	QHBoxLayout* linijkaZdrowia;
	QHBoxLayout* linijkaDoswiadczenia;
	QHBoxLayout* linijkaObrony;
	QHBoxLayout* linijkaAtakow;
	QHBoxLayout* linijkaZlota;
	QHBoxLayout* linijkaPrzyciskow;

	QLabel* pierwszaLinijka;

	QLabel* opisPrzedZdrowiem;
	MyTaskbar* wskaznikZdrowia;

	QLabel* opisPrzedDoswiadczeniem;
	MyTaskbar* wskaznikDoswiadczenia;

	QVBoxLayout* slupkiLayouts[KingdomCount];
	QLabel* podpisy[KingdomCount];
	MyTaskbar* slupki[KingdomCount];

	QLabel* obrona;
	QLabel* obronaIkona;
	QLabel* percepcja;
	QLabel* percepcjaIkona;
	QLabel* ruch;
	QLabel* ruchIkona;

	QLabel* wrecz;
	QLabel* wreczIkona;
	QLabel* dystans;
	QLabel* dystansIkona;
	QLabel* magia;
	QLabel* magiaIkona;

	QLabel* zloto;
	QLabel* zlotoIkona;

	QPushButton* ekwipunek;
	QPushButton* zadania;
	Player* gracz;

	QString odmiana(int n); //TODO CFiend kill it for now

private slots:
	void showEquipment();
	void showQuests();
};

#endif
