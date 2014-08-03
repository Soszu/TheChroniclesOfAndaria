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

#pragma once

#include <QtWidgets>

#include "Core/Parsers/BoardParser.h"
#include "Core/Parsers/EnemyParser.h"
#include "Core/Parsers/ItemParser.h"
#include "Core/Parsers/PrizeParser.h"
#include "Core/Parsers/QuestParser.h"
#include "Core/Containers/Enemy.h"

class BoardParser;
class EnemyParser;
class ItemParser;
class PrizeParser;
class QuestParser;

class DataKeeper
{
	friend class EnemyParser;
	friend class ItemParser;
	friend class PrizeParser;
	friend class QuestParser;
	friend class BoardParser;

public:
	static DataKeeper &instance();
	int initError();
	~DataKeeper();

	//READ ONLY
	//CONST! CONST! CONST! CONST! CONST! 
	const QMap <int, const QList <int> *> enemyGroups() const;
	const QMap <int, const Enemy *> enemies() const;
	const QMap <QString, const QList <int> *> itemGroups() const;
	const QMap <int, const Item *> items() const;
	const QMap <int, const Prize *> prizes() const;
	const QMap <int, const Quest *> quests() const;
	
	const QList <int> & cities() const;
	const QList <const Field *> & fields() const;
	const quint8 boardHeight() const;
	const quint8 boardWidth() const;
	//CONST! CONST! CONST! CONST! CONST! 

private:
	explicit DataKeeper();
	DataKeeper(const DataKeeper &) = delete;
	DataKeeper(DataKeeper &&) = delete;
	void operator=(const DataKeeper &) = delete;
	void operator=(DataKeeper &&) = delete;
	
	void displayErrorMessage(const QString &message) const;
	
	int initError_;
	QDialog *errorMessageBox_; //NOTE ??
	
	QMap <int, const QList <int> *> enemyGroups_; //dla kaÅ¼dej grupy reprezentowanej przez poziom trzymane sÄ identyfikatory przeciwnikoe do niej naleÅ¼Äcych
	QMap <int, const Enemy *> enemies_; //jako klucz jest zapisywany identyfikator w postaci liczby caÅkowitej
	QMap <QString, const QList <int> *> itemGroups_; //dla kaÅ¼dej grupy trzymane sÄ identyfikatory przedmiotÃ³w do niej naleÅ¼Äcych
	QMap <int, const Item *> items_; //dla kaÅ¼dego identyfikatora trzymany jest opis przedmiotu.
	QMap <int, const Prize *> prizes_; //dla kaÅ¼dego identyfikatora trzymany jest opis nagrody.
	QMap <int, const Quest *> quests_; //dla kaÅ¼dego identyfikatora trzymany jest opis zadania.

	QList <int> cities_;
	QList <const Field *> fields_;
	quint8 boardHeight_;
	quint8 boardWidth_;
};
