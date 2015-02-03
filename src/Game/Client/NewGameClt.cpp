/*
Copyright (C) 2014-2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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
#include "NewGameClt.hpp"

NewGameClt::NewGameClt(ConnectionAdapterClt *connectionAdapter) :
	connectionAdapter_(connectionAdapter),
	playerIsReady_(false)
{
// 	connect(connectionAdapter_, &ConnectionAdapterClt::newMessage, this, &NewGameClt::onNewMessage);
	connect(connectionAdapter_, &ConnectionAdapterClt::connected, this, &NewGameClt::showGui);
}


void NewGameClt::start()
{
	connectionAdapter_->connectToSrv();
}

const QVector <PlayerDraft> & NewGameClt::otherPlayersDrafts() const
{
	return otherPlayersDrafts_;
}

const PlayerDraft & NewGameClt::myDraft() const
{
	return myDraft_;
}

bool NewGameClt::playerIsReady() const
{
	return playerIsReady_;
}

void NewGameClt::setMyName(const QString &name)
{
	myDraft_.setName(name);
	notifyAboutChanges();
}

void NewGameClt::setMyRace(Race playerRace)
{
	myDraft_.setPlayerRace(playerRace);
	notifyAboutChanges();
}

void NewGameClt::setMyClass(Class playerClass)
{
	myDraft_.setPlayerClass(playerClass);
	notifyAboutChanges();
}

void NewGameClt::setMyColor(const QColor &color)
{
	myDraft_.setColor(color);
	notifyAboutChanges();
}

void NewGameClt::switchPlayerIsReady()
{
	playerIsReady_ = !playerIsReady_;
	notifyAboutChanges();
}

void NewGameClt::notifyAboutChanges()
{
	//TODO
	qDebug() << "myDraft changed";
}

void NewGameClt::onNewMessage(Message &msg)
{
	//TODO
	//if player drafts newSettings

	// if everyoneReady
	emit gameSet();
}


//void NewGameWindow::validate()
//{
//	for (int i = 0; i < playerCount_; ++i) {
//		if (playerRows[i].nameEdit->text().size() == 0) {
//			messageBox->setText(QString::fromUtf8("Nazwa co najmniej jednego z graczy nie została wpisana poprawnie."));
//			messageBox->show();
//			return;
//		}

//		if (playerRows[i].nameEdit->text().size() > MAKSYMALNA_DLUGOSC_NAZWY) {//TODO CFiend to raczej trzeba ustawic na poziome QLineEdit
//			messageBox->setText(QString::fromUtf8("Nazwa co najmniej jednego z graczy jest za długa. Limit to ") + QString::number(MAKSYMALNA_DLUGOSC_NAZWY)+ QString::fromUtf8("znaków."));
//			messageBox->show();
//			return;
//		}

//		for (int j = i + 1; j < playerCount_; ++j)
//			if (playerRows[i].colorCombo->currentText() == playerRows[j].colorCombo->currentText()) {
//				messageBox->setText(QString::fromUtf8("Co najmniej jeden kolor się powtarza."));
//				messageBox->show();
//				return;
//			}
//	}

//	QList <Player *> playerList;
//	for (int i = 0; i < playerCount_; ++i ){
//		playerList.push_back(new Player(playerRows[i].nameEdit->text(),
//					Player::raceString()[playerRows[i].playerRaceCombo->currentText()],
//					Player::classString()[playerRows[i].playerClassCombo->currentText()],
//					KOLORY[playerRows[i].colorCombo->currentIndex()],
//					playerRows[i].isAiCheckBox->checkState()));
//	}
//	//korzystam tutaj z faktu, że pola w przyciskach są w takiej kolejności jak w tablicy,
//	//a tam, są w takiej kolejności jak w enumach
//	//TODO CFiend powyzszy komentarz do wywalenia po przerzuceniu enum na enum class

//	gameCycle_->beginGame(playerList);
//	this->close();
//}
