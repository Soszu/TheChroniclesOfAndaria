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

#include "DataKeeper.h"

DataKeeper & DataKeeper::instance()
{
	static DataKeeper *instance = new DataKeeper;
	return *instance;
}

int DataKeeper::initError()
{
	return initError_;
}

DataKeeper::~DataKeeper(){
	delete errorMessageBox_;
	
	qDeleteAll(items_);
	qDeleteAll(enemies_);
	qDeleteAll(prizes_);
	qDeleteAll(itemGroups_);
	qDeleteAll(enemyGroups_);
	qDeleteAll(quests_);

	qDeleteAll(fields_);
}

const QMap <int, const QList <int> *> DataKeeper::enemyGroups() const
{
	return enemyGroups();
}

const QMap<int, const Enemy *> DataKeeper::enemies() const
{
	return enemies_;
}

const QMap <QString, const QList <int> *> DataKeeper::itemGroups() const
{
	return itemGroups_;
}

const QMap<int, const Item *> DataKeeper::items() const
{
	return items_;
}

const QMap <int, const Prize *> DataKeeper::prizes() const
{
	return prizes_;
}

const QMap<int, const Quest *> DataKeeper::quests() const
{
	return quests_;
}

const QList <int> & DataKeeper::cities() const
{
	return cities_;
}

const QList<const Field *> &DataKeeper::fields() const
{
	return fields_;
}

const quint8 DataKeeper::boardHeight() const
{
	return boardHeight_;
}

const quint8 DataKeeper::boardWidth() const
{
	return boardWidth_;
}

DataKeeper::DataKeeper() : initError_(0), errorMessageBox_(new QDialog)
{
	//TODO Parsers should be replaced with models
	
	BoardParser boardParser(this);
	if (boardParser.bladWczytywania()) {
		initError_ = blad_parsera_ustawienia_planszy;
		displayErrorMessage(QString::fromUtf8("Wystąpił błąd przy wczytywaniu ustawienia planszy\n\n") + boardParser.trescBledu);
		return;
	}
	qDebug() << QString::fromUtf8("Ustawienie planszy wczytano poprawnie");
	
	ItemParser itemParser(this);
	if (itemParser.bladWczytywania()) {
		initError_ = blad_parsera_przedmiotow;
		displayErrorMessage(QString::fromUtf8("WystÄpiÅ bÅÄd przy wczytywaniu danych przedmiotow\n\n") + itemParser.trescBledu);
		return;
	}
	qDebug() << QString::fromUtf8("Informacje o przedmiotach wczytano poprawnie");

	PrizeParser prizeParser(this);
	if (prizeParser.bladWczytywania()) {
		initError_ = blad_parsera_nagrod;
		displayErrorMessage(QString::fromUtf8("WystÄpiÅ bÅÄd przy wczytywaniu danych nagrÃ³d\n\n") + prizeParser.trescBledu);
		return;
	}
	qDebug() << QString::fromUtf8("Informacje o prizech wczytano poprawnie");

	EnemyParser enemyParser(this);
	if (enemyParser.bladWczytywania()) {
		initError_ = blad_parsera_przeciwnikow;
		displayErrorMessage(QString::fromUtf8("WystÄpiÅ bÅÄd przy wczytywaniu danych przeciwnikÃ³w\n\n") + enemyParser.trescBledu);
		return;
	} else if (enemyGroups_.size() != Enemy::NUMBER_OF_ENEMIES_GROUPS) {
		initError_ = blad_liczby_grup_przeciwnikow;
		displayErrorMessage(QString::fromUtf8("Wczytano za maÅo albo za duÅ¼o grup przedmiotÃ³w.\n\n"));
		return;
	}
	qDebug() << QString::fromUtf8("Informacje o przeciwnikach wczytano poprawnie");

	QuestParser questParser(this);
	if (questParser.bladWczytywania()) {
		initError_ = blad_parsera_zadan;
		displayErrorMessage(QString::fromUtf8("WystÄpiÅ bÅÄd przy wczytywaniu danych zadaÅ\n\n") + questParser.trescBledu);
		return;
	} else if (quests_.size() < QuestsInTavernCount) {
		initError_ = blad_liczby_zadan;
		displayErrorMessage(QString::fromUtf8("Wczytano za maÅo zadaÅ.\n\n"));
		return;
	}
	qDebug() << QString::fromUtf8("Informacje o zadaniach wczytano poprawnie");
}

void DataKeeper::displayErrorMessage(const QString &message) const
{
	qDebug() << message;

	QMessageBox::critical(
		errorMessageBox_,
		QString::fromUtf8("Napotkano błąd"),
		message + QString::fromUtf8("\n\nNastąpi zamknięcie programu.")
	);
}
