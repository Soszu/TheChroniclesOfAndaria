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

#include "Core/Containers/Effect.hpp"

class EffectsListEdit : public QWidget {
	Q_OBJECT
	Q_PROPERTY(QList <Effect> effects_
	           READ effects
	           WRITE setEffects
	           RESET reset
	           NOTIFY effectsChanged
	           USER true)

public:
	EffectsListEdit(QWidget *parent = nullptr);

	QList <Effect> effects() const;

	void reset();
	void setEffects(const QList <Effect> &effects);

private:
	void initButtons();
	void initEdits();
	void initList();
	void initLayout();
	void simulateFocusLoss();

	QList <Effect> effects_;
	QStringListModel *effectsModel_;

	QListView *listView_;
	QComboBox *typeEdit_;
	QSpinBox *valueEdit_;
	QSpinBox *durationEdit_;

	QPushButton *addEffectButton_;
	QPushButton *removeEffectButton_;

private slots:
	void addEffect();
	void removeEffect();
	void updateEdits(const QModelIndex &index);

	void updateType(QString text);
	void updateValue(int x);
	void updateDuration(int x);

signals:
	void effectsChanged(QList <Effect> effects_);
};
