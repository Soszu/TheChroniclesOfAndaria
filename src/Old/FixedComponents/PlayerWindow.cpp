/*
Copyright (C) 2013-2014 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
Thanks to 2013 Łukasz Piesiewicz <wookesh [at] gmail [dot] com>
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

#include "Game/FixedComponents/PlayerWindow.hpp"

PlayerWindow::PlayerWindow(GameCycle *gameCycle)
{
	this->gameCycle_ = gameCycle;
	mainLayout = new QVBoxLayout();
//------------------------------
	pierwszaLinijka = new QLabel();
//------------------------------
	opisPrzedZdrowiem = new QLabel("Zdrowie:");
	wskaznikZdrowia = new MyTaskbar(0, 0, Qt::red, Qt::green);

	linijkaZdrowia = new QHBoxLayout();
	linijkaZdrowia->addWidget(opisPrzedZdrowiem);
	linijkaZdrowia->addWidget(wskaznikZdrowia);
//------------------------------
	opisPrzedDoswiadczeniem = new QLabel("Poziom: _");
	wskaznikDoswiadczenia = new MyTaskbar(0, Qt::blue);
	linijkaDoswiadczenia = new QHBoxLayout();
	linijkaDoswiadczenia->addWidget(opisPrzedDoswiadczeniem);
	linijkaDoswiadczenia->addWidget(wskaznikDoswiadczenia);
//------------------------------
	reputacja = new QHBoxLayout();
	for(int i = 0; i < KingdomCount; ++i)
	{
		slupkiLayouts[i] = new QVBoxLayout();
		slupki[i] = new MyTaskbar(MaximumReputation, 0, Qt::yellow);
		slupki[i]->setToolTip(QString::fromUtf8("WskaÅºnik reputacji dla frakcji: ") + KingdomString[i]);
		podpisy[i] = new QLabel(KingdomString[i]);
		slupkiLayouts[i]->addWidget(slupki[i]);
		slupkiLayouts[i]->addWidget(podpisy[i]);

		reputacja->addLayout(slupkiLayouts[i]);
	}
//------------------------------
	obronaIkona = new QLabel();
	obronaIkona->setPixmap(DataManager::pixmap(Paths::IconDefence));
	obronaIkona->setToolTip(QString::fromUtf8("WartoÅÄ wspÃ³Åczynnika obrony."));
	obrona = new QLabel();
	obrona->setToolTip(QString::fromUtf8("WartoÅÄ wspÃ³Åczynnika obrony."));
	percepcjaIkona = new QLabel();
	percepcjaIkona->setPixmap(DataManager::pixmap(Paths::IconPerception));
	percepcjaIkona->setToolTip(QString::fromUtf8("WartoÅÄ wspÃ³Åczynnika percepcji."));
	percepcja = new QLabel();
	percepcja->setToolTip(QString::fromUtf8("WartoÅÄ wspÃ³Åczynnika percepcji."));
	ruchIkona = new QLabel();
	ruchIkona->setPixmap(DataManager::pixmap(Paths::IconMovement));
	ruchIkona->setToolTip(QString::fromUtf8("IloÅÄ punktÃ³w ruchu."));
	ruch = new QLabel();
	ruch->setToolTip(QString::fromUtf8("IloÅÄ punktÃ³w ruchu."));

	linijkaObrony = new QHBoxLayout();
	linijkaObrony->addWidget(obronaIkona);
	linijkaObrony->addWidget(obrona);
	linijkaObrony->addWidget(percepcjaIkona);
	linijkaObrony->addWidget(percepcja);
	linijkaObrony->addWidget(ruchIkona);
	linijkaObrony->addWidget(ruch);
//------------------------------
	wreczIkona = new QLabel();
	wreczIkona->setPixmap(DataManager::pixmap(Paths::IconMelee));
	wreczIkona->setToolTip(QString::fromUtf8("WartoÅÄ ataku wrÄcz."));
	wrecz = new QLabel();
	wrecz->setToolTip(QString::fromUtf8("WartoÅÄ ataku wrÄcz."));
	dystansIkona = new QLabel();
	dystansIkona->setPixmap(DataManager::pixmap(Paths::IconRanged));
	dystansIkona->setToolTip(QString::fromUtf8("WartoÅÄ ataku dystansowego."));
	dystans = new QLabel();
	dystans->setToolTip(QString::fromUtf8("WartoÅÄ ataku dystansowego."));
	magiaIkona = new QLabel();
	magiaIkona->setPixmap(DataManager::pixmap(Paths::IconMagic));
	magiaIkona->setToolTip(QString::fromUtf8("WartoÅÄ ataku magicznego."));
	magia = new QLabel();
	magia->setToolTip(QString::fromUtf8("WartoÅÄ ataku magicznego."));

	linijkaAtakow = new QHBoxLayout();
	linijkaAtakow->addWidget(wreczIkona);
	linijkaAtakow->addWidget(wrecz);
	linijkaAtakow->addWidget(dystansIkona);
	linijkaAtakow->addWidget(dystans);
	linijkaAtakow->addWidget(magiaIkona);
	linijkaAtakow->addWidget(magia);
//------------------------------
	zlotoIkona = new QLabel();
	zlotoIkona->setPixmap(DataManager::pixmap(Paths::IconGold));
	zlotoIkona->setToolTip(QString::fromUtf8("IloÅÄ posiadanego zÅota."));
	zloto = new QLabel();
	zloto->setToolTip(QString::fromUtf8("IloÅÄ posiadanego zÅota."));

	linijkaZlota = new QHBoxLayout();
	linijkaZlota->addWidget(zlotoIkona);
	linijkaZlota->addWidget(zloto);
//	linijkaZlota->addStretch();
//------------------------------
	linijkaPrzyciskow = new QHBoxLayout();
	zadania = new QPushButton(QString::fromUtf8("Przejrzyj zadania"));
	zadania->setToolTip(QString::fromUtf8("WyÅwietla opis wykonywanych zadaÅ."));
	ekwipunek = new QPushButton(QString::fromUtf8("Przejrzyj ekwipunek"));
	ekwipunek->setToolTip(QString::fromUtf8("WyÅwietla opis posiadanego ekwipunku."));
	linijkaPrzyciskow->addWidget(ekwipunek);
	linijkaPrzyciskow->addWidget(zadania);

	connect(ekwipunek, SIGNAL(clicked()), this, SLOT(showEquipment()));
	connect(zadania, SIGNAL(clicked()), this, SLOT(showQuests()));

//------------------------------
	mainLayout->addWidget(pierwszaLinijka);
	mainLayout->addLayout(linijkaZdrowia);
	mainLayout->addLayout(linijkaDoswiadczenia);
	mainLayout->addLayout(reputacja);
	mainLayout->addLayout(linijkaObrony);
	mainLayout->addLayout(linijkaAtakow);
	mainLayout->addLayout(linijkaZlota);
	mainLayout->addLayout(linijkaPrzyciskow);
}

QLayout *PlayerWindow::mainLayout()
{
	return mainLayout;
}

void PlayerWindow::displayPlayer()
{
	player = gameCycle_->currentPlayer();
	pierwszaLinijka->setText(player->name() + ", " + Player::raceString()[player->playerRace()] + " " + Player::classString()[player->playerClass()]);
//------------------------------
	QString odmianaPunkty;
	switch(player->regeneration()){
	case 1:
		odmianaPunkty = "punkt";
		break;
	case 2: case 3: case 4:
		odmianaPunkty = "punkty";
		break;
	default:
		odmianaPunkty = QString::fromUtf8("punktÃ³w");
		break;
	}

	wskaznikZdrowia->fillFirst((qreal)player->currentHealth() / player->maxHealth());
	wskaznikZdrowia->fillSecond((qreal)player->regeneration() / player->maxHealth());
	wskaznikZdrowia->setToolTip(QString("Punkty zdrowia: ") + QString::number(player->currentHealth()) + QString("/") + QString::number(player ->maxHealth())+
				    QString::fromUtf8("\nRegeneracja: ") + QString::number(player->regeneration()) + QString(" ") + odmianaPunkty + QString::fromUtf8("/turÄ") );
//------------------------------
	opisPrzedDoswiadczeniem->setText(QString("Poziom: ") + QString::number(player->level()));
	int ileDoswNaAktualnyPoziom = GRANICE_POZIOMOW[player->level()] - GRANICE_POZIOMOW[player->level() - 1];
	int ileDoswZebranoNaAktPoziomie = player->experience() - GRANICE_POZIOMOW[player->level() - 1];
	wskaznikDoswiadczenia->fill((qreal)ileDoswZebranoNaAktPoziomie / ileDoswNaAktualnyPoziom );
	if(player->level() < MaximumLevel)
		wskaznikDoswiadczenia->setToolTip(QString::fromUtf8("Punkty doÅwiadczenia: ") + QString::number(ileDoswZebranoNaAktPoziomie) + QString("/") + QString::number(ileDoswNaAktualnyPoziom));
	else
		wskaznikDoswiadczenia->setToolTip(QString::fromUtf8("OsiÄgnÄÅeÅ maksymalny poziom"));
//------------------------------
	for(int i = 0; i < KingdomCount; ++i)
		slupki[i]->setMarkerCount(player->reputation()[i]);
//------------------------------
	obrona->setText(QString::number(player->defence()));
	percepcja->setText(QString::number(player->perception()));
	ruch->setText(QString::number(player->movePoints()));
//------------------------------
	wrecz->setText(QString::number(player->attackMelee()));
	dystans->setText(QString::number(player->attackRanged()));
	magia->setText(QString::number(player->attackMagical()));
//------------------------------
	zloto->setText(QString::number(player->gold()));// + odmiana(player->gold()));
//------------------------------

	if(player->isAI())
	{
		zadania->setEnabled(false);
		ekwipunek->setEnabled(false);
	}
	else
	{
		zadania->setEnabled(true);
		ekwipunek->setEnabled(true);
	}

	qDebug() << "Okno Gracza wyswietlilo dane: " << player->name();
}

void PlayerWindow::update()
{
	displayPlayer();
}

void PlayerWindow::showEquipment()
{
	gameCycle_->showEquipment();
}

void PlayerWindow::showQuests()
{
	gameCycle_->showQuests();
}
