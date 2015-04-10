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
#pragma once

#include <QtCore>
#include "Core/Strings.hpp"
#include "Core/Utils/Serial.hpp"

class EnemyBase;

class EnemyModel : public QAbstractTableModel {
public:
	static const int Name          = 0;
	static const int ImageName     = 1;
	static const int Level         = 2;
	static const int Type          = 3;
	static const int DefaultAttack = 4;
	static const int BaseStats     = 5;
	static const int WinningPrize  = 6;
	static const int ColumnCount   = 7;

	explicit EnemyModel(QObject * parent = nullptr);
	EnemyModel(const EnemyModel &) = delete;
	EnemyModel(EnemyModel &&) = delete;
	void operator=(const EnemyModel &) = delete;
	void operator=(EnemyModel &&) = delete;
	~EnemyModel();

	int columnCount(const QModelIndex & index = QModelIndex()) const;
	QVariant data(const QModelIndex & index, int role) const;
	bool empty() const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	bool hasEnemy(const QString & name) const;
	const EnemyBase * enemyInRow(int row) const;
	const EnemyBase * enemy(UID uid) const;
	const EnemyBase * enemy(const QModelIndex & index) const;
	const EnemyBase * enemy(const QString & name) const;
	const QList <EnemyBase *> & enemies() const;
	bool isChanged() const;
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QDataStream & toDataStream(QDataStream &out) const;

	void addNewEnemy();
	QDataStream & fromDataStream(QDataStream & in);
	bool insertRows(int row, int count, const QModelIndex & parent = QModelIndex());
	void removeEnemy(UID uid);
	bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());
	void reset();
	void setChanged(bool changed);
	bool setData(const QModelIndex &index, const QVariant & value, int role = Qt::EditRole);

	//TMP for migration from parser
	void addEnemyBase(EnemyBase * eb);

private:
	void addEnemy(int row, EnemyBase * enemy);
	void removeEnemyFromRow(int row);

	bool changed_;
	QList <EnemyBase *> enemies_;
	Serial serial_;
	QHash <UID, EnemyBase *> uidToEnemy_;
};
QDataStream & operator<<(QDataStream & out, const EnemyModel & model);
QDataStream & operator>>(QDataStream & in, EnemyModel & model);
