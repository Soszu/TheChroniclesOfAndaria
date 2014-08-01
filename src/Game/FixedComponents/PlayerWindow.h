/*
Copyright (C) 2013-2014 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
This file is part of The Chronicles Of Andaria Project.

	The Chronicles of Andaria Project is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	The Chronicles of Andaria Project is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with The Chronicles Of Andaria.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#include <QtWidgets>

#include "Core/DataManager.h"
#include "Core/Containers/Player.h"
#include "Game/Game.h"
#include "Game/GameCycle.h"
#include "Game/CustomWidgets/MyTaskbar.h"

//TODO CFiend general cleanup

class PlayerWindow : public QObject {
	Q_OBJECT
public:
	PlayerWindow(GameCycle *gameCycle);
	QLayout *mainLayout();

public slots:
	void displayPlayer();
	void update();

private:
	GameCycle *gameCycle_;
	const Player *player;

	QVBoxLayout *mainLayout;

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

private slots:
	void showEquipment();
	void showQuests();
};

#endif
