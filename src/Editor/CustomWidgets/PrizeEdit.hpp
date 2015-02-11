/*
Copyright (C) 2014-2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
Copyright (C) 2015 by Marcin Parafiniuk <jessie [dot] inferno [at] gmail [dot] com>
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

#include "Core/Containers/Prize.hpp"
#include "Editor/CustomWidgets/EffectsListEdit.hpp"

class PrizeEdit : public QWidget {
	Q_OBJECT
	Q_PROPERTY(Prize prize_
	           READ prize
	           WRITE setPrize
	           RESET reset
	           NOTIFY prizeChanged
	           USER true)

public:
	PrizeEdit(QWidget *parent = nullptr);

	Prize prize() const;

	void reset();
	void setPrize(const Prize &prize);

private:
	void initWidgets();
	void initLayout();
	void simulateFocusLoss();

	Prize prize_;

	QSpinBox *experienceEdit_;
	QSpinBox *goldEdit_;

	EffectsListEdit *listEdit_;
//
// 	QList <Effect> effects_;
// 	QStringListModel *effectsModel_;
//
// 	QListView *listView_;
// 	QComboBox *typeEdit_;
//
// 	QPushButton *addEffectButton_;
// 	QPushButton *removeEffectButton_;

private slots:
// 	void addEffect();
// 	void removeEffect();
// 	void updateEdits(const QModelIndex &index);
//
// 	void updateType(QString text);
	void updateExperience(int x);
	void updateGold(int x);
	void updateEffects(const QList<Effect> & effects);

signals:
	void prizeChanged(Prize prize);
};
