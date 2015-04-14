/*
Copyright (C) 2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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
class QuestModel;
class ObjectivesEdit;

class QuestEditor : public QWidget {
	Q_OBJECT

public:
	QuestEditor(QuestModel * questModel, QWidget * parent = nullptr);
	void clear();
	void loadFromStream(QDataStream & in);
	void saveToStream(QDataStream & out) const;
	bool isChanged() const;

public slots:
	void modelSaved();

private:
	void initEditPart();
	void initViewPart();
	void initLayout();
	void initMapper();
    void updateFollowUps();

	QFormLayout * editLayout_;
	QVBoxLayout * viewLayout_;

	QuestModel * questModel_;
	QDataWidgetMapper questMapper_;

	//--- Edits ---
	QLineEdit * titleEdit_;
	QPlainTextEdit * descriptionEdit_;
	EnumEdit * fractionEdit_;
	QSpinBox * levelEdit_;
	EnumEdit * difficultyEdit_;
	QCheckBox * isReturnRequiredEdit_;
	QCheckBox * canBeDrawnEdit_;
	ObjectivesEdit * objectivesEdit_;
	EnumEdit * followUpEdit_;
	PrizeEdit * rewardEdit_;

	//--- List---
	QListView * questsList_;

private slots:
	void addQuest();
	void removeQuest();
};
