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

#include <QtWidgets>

class EnumEdit;
class PrizeEdit;
class EffectsListEdit;
class EnemyModel;

class EnemiesEditor : public QWidget {
	Q_OBJECT

public:
	EnemiesEditor(EnemyModel *enemyModel, QWidget *parent = nullptr);
	void clear();
	void loadFromStream(QDataStream& in);
	void saveToStream(QDataStream& out) const;
	bool isChanged() const;

public slots:
	void modelSaved();

private:
	void initEditPart();
	void initViewPart();
	void initLayout();
	void initMapper();

	QFormLayout *editLayout_;
	QVBoxLayout *viewLayout_;

	EnemyModel *enemyModel_;
	QDataWidgetMapper *enemyMapper_;

	//--- Edits ---
	QLineEdit *nameEdit_;
	QLineEdit *imageNameEdit_;
	EnumEdit *defaultAttackEdit_;
	QSpinBox *levelEdit_;
	EffectsListEdit *baseStatsEdit_;
	PrizeEdit *prizeEdit_;

	//--- List---
	QListView *enemiesList_;
	QPushButton *addEnemyButton_;
	QPushButton *removeEnemyButton_;

private slots:
	void addEnemy();
	void removeEnemy();
};
