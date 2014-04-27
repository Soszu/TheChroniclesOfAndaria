/*
Copyright (C) 2013 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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

#include "Game/PlayerWindow.h"

PlayerWindow::PlayerWindow(QFrame *frame)
{
	QVBoxLayout *mainLayout = new QVBoxLayout();
	frame->setLayout(mainLayout);
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
		slupki[i]->setToolTip(QString::fromUtf8("Wskaźnik reputacji dla frakcji: ") + KingdomString[i]);
		podpisy[i] = new QLabel(KingdomString[i]);
		slupkiLayouts[i]->addWidget(slupki[i]);
		slupkiLayouts[i]->addWidget(podpisy[i]);

		reputacja->addLayout(slupkiLayouts[i]);
	}
//------------------------------
	obronaIkona = new QLabel();
	obronaIkona->setPixmap(IKONKA_OBRONA);
	obronaIkona->setToolTip(QString::fromUtf8("Wartość współczynnika obrony."));
	obrona = new QLabel();
	obrona->setToolTip(QString::fromUtf8("Wartość współczynnika obrony."));
	percepcjaIkona = new QLabel();
	percepcjaIkona->setPixmap(IKONKA_PERCEPCJA);
	percepcjaIkona->setToolTip(QString::fromUtf8("Wartość współczynnika percepcji."));
	percepcja = new QLabel();
	percepcja->setToolTip(QString::fromUtf8("Wartość współczynnika percepcji."));
	ruchIkona = new QLabel();
	ruchIkona->setPixmap(IKONKA_RUCH);
	ruchIkona->setToolTip(QString::fromUtf8("Ilość punktów ruchu."));
	ruch = new QLabel();
	ruch->setToolTip(QString::fromUtf8("Ilość punktów ruchu."));

	linijkaObrony = new QHBoxLayout();
	linijkaObrony->addWidget(obronaIkona);
	linijkaObrony->addWidget(obrona);
	linijkaObrony->addWidget(percepcjaIkona);
	linijkaObrony->addWidget(percepcja);
	linijkaObrony->addWidget(ruchIkona);
	linijkaObrony->addWidget(ruch);
//------------------------------
	wreczIkona = new QLabel();
	wreczIkona->setPixmap(IKONKA_WRECZ);
	wreczIkona->setToolTip(QString::fromUtf8("Wartość ataku wręcz."));
	wrecz = new QLabel();
	wrecz->setToolTip(QString::fromUtf8("Wartość ataku wręcz."));
	dystansIkona = new QLabel();
	dystansIkona->setPixmap(IKONKA_DYSTANSOWY);
	dystansIkona->setToolTip(QString::fromUtf8("Wartość ataku dystansowego."));
	dystans = new QLabel();
	dystans->setToolTip(QString::fromUtf8("Wartość ataku dystansowego."));
	magiaIkona = new QLabel();
	magiaIkona->setPixmap(IKONKA_MAGICZNY);
	magiaIkona->setToolTip(QString::fromUtf8("Wartość ataku magicznego."));
	magia = new QLabel();
	magia->setToolTip(QString::fromUtf8("Wartość ataku magicznego."));

	linijkaAtakow = new QHBoxLayout();
	linijkaAtakow->addWidget(wreczIkona);
	linijkaAtakow->addWidget(wrecz);
	linijkaAtakow->addWidget(dystansIkona);
	linijkaAtakow->addWidget(dystans);
	linijkaAtakow->addWidget(magiaIkona);
	linijkaAtakow->addWidget(magia);
//------------------------------
	zlotoIkona = new QLabel();
	zlotoIkona->setPixmap(IKONKA_ZLOTO);
	zlotoIkona->setToolTip(QString::fromUtf8("Ilość posiadanego złota."));
	zloto = new QLabel();
	zloto->setToolTip(QString::fromUtf8("Ilość posiadanego złota."));

	linijkaZlota = new QHBoxLayout();
	linijkaZlota->addWidget(zlotoIkona);
	linijkaZlota->addWidget(zloto);
//	linijkaZlota->addStretch();
//------------------------------
	linijkaPrzyciskow = new QHBoxLayout();
	zadania = new QPushButton(QString::fromUtf8("Przejrzyj zadania"));
	zadania->setToolTip(QString::fromUtf8("Wyświetla opis wykonywanych zadań."));
	ekwipunek = new QPushButton(QString::fromUtf8("Przejrzyj ekwipunek"));
	ekwipunek->setToolTip(QString::fromUtf8("Wyświetla opis posiadanego ekwipunku."));
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

/**
 * @brief OknoGracza::wyswietlGracz	Wyświetla dane podanego gracza.
 * @param gracz
 */
void PlayerWindow::displayPlayer(Player *player)
{
	currentPlayer = player;
	pierwszaLinijka->setText(player->name() + ", " + PlayerRaceString[player->playerRace()] + " " + PlayerClassString[player->playerClass()]);
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
		odmianaPunkty = QString::fromUtf8("punktów");
		break;
	}

	wskaznikZdrowia->fillFirst((qreal)player->healthCurrent() / player->healthMax());
	wskaznikZdrowia->fillSecond((qreal)player->regeneration() / player->healthMax());
	wskaznikZdrowia->setToolTip(QString("Punkty zdrowia: ") + QString::number(player->healthCurrent()) + QString("/") + QString::number(player ->healthMax())+
				    QString::fromUtf8("\nRegeneracja: ") + QString::number(player->regeneration()) + QString(" ") + odmianaPunkty + QString::fromUtf8("/turę") );
//------------------------------
	opisPrzedDoswiadczeniem->setText(QString("Poziom: ") + QString::number(player->level()));
	int ileDoswNaAktualnyPoziom = GRANICE_POZIOMOW[player->level()] - GRANICE_POZIOMOW[player->level() - 1];
	int ileDoswZebranoNaAktPoziomie = player->experience() - GRANICE_POZIOMOW[player->level() - 1];
	wskaznikDoswiadczenia->fill((qreal)ileDoswZebranoNaAktPoziomie / ileDoswNaAktualnyPoziom );
	if(player->level() < MaximumLevel)
		wskaznikDoswiadczenia->setToolTip(QString::fromUtf8("Punkty doświadczenia: ") + QString::number(ileDoswZebranoNaAktPoziomie) + QString("/") + QString::number(ileDoswNaAktualnyPoziom));
	else
		wskaznikDoswiadczenia->setToolTip(QString::fromUtf8("Osiągnąłeś maksymalny poziom"));
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

/**
 * @brief OknoGracza::uaktualnijInformacje	Odświeża dane i powiadamia o zmianie
 */
void PlayerWindow::update()
{
	gameMaster_->updateBoard();
	displayPlayer(currentPlayer);
}

void PlayerWindow::setGameMaster(GameMaster *gameMaster)
{
	this->gameMaster_ = gameMaster;
}

/**
 * @brief OknoGracza::odmiana Odmienia słowo "sztuka" zależnie od liczby sztuk złota
 * @param n ile sztuk
 * @return
 */
QString PlayerWindow::odmiana(int n)
{
	if (n == 1)
		return QString(" sztuka");
	if (n > 1 && n < 5)
		return QString(" sztuki");
	return QString(" sztuk");
}

/**
 * @brief OknoGracza::pokazEkwipunek Wywołuje Okno Ekwipunek
 */
void PlayerWindow::showEquipment()
{
	equipmentWindow_ = new EquipmentWindow(currentPlayer, this);
	equipmentWindow_->setWindowModality(Qt::ApplicationModal);
	equipmentWindow_->setAttribute(Qt::WA_DeleteOnClose);
	equipmentWindow_->show();
}

/**
 * @brief OknoGracza::pokazZadania	Wywołuje Okno Zadania
 */
void PlayerWindow::showQuests()
{
	questWindow_ = new QuestWindow(currentPlayer, gameMaster_->board());
	questWindow_->setWindowModality(Qt::ApplicationModal);
	questWindow_->setAttribute(Qt::WA_DeleteOnClose);
	questWindow_->show();
}
