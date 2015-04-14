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
#include "Editor/CustomWidgets/PrizeEdit.hpp"

#include "Core/Enums.hpp"

PrizeEdit::PrizeEdit(QWidget *parent) :
	QWidget(parent)
{
	setFocusPolicy(Qt::FocusPolicy::ClickFocus);
	initWidgets();
	initLayout();
}

Prize PrizeEdit::prize() const
{
	return prize_;
}

void PrizeEdit::reset()
{
	emit prizeChanged(prize_);
}

void PrizeEdit::setPrize(const Prize &prize)
{
	if (prize_ == prize)
		return;

	prize_ = prize;
	experienceEdit_->setValue(prize.experience());
	goldEdit_->setValue(prize.gold());
	//TODO maria_ update list of effects
	for (int i = 0; i < repSpins_.size(); i++) {
		repSpins_[i]->setValue(prize.reputations()[KingdomsForReputation[i]]);
	}

	emit prizeChanged(prize_);
	simulateFocusLoss();
}

void PrizeEdit::initWidgets()
{
	experienceEdit_ = new QSpinBox;
	experienceEdit_->setSingleStep(100);
	experienceEdit_->setMaximum(10000);
	connect(experienceEdit_, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
	        this, &PrizeEdit::updateExperience);

	goldEdit_ = new QSpinBox;
	connect(goldEdit_, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
	        this, &PrizeEdit::updateGold);
	repLayout_ = new QFormLayout;
	for (int i = 0; i < KingdomsForReputation.size(); i++) {
		auto repSpin = new QSpinBox;
		repSpin->setMaximum(99);
		repSpin->setMinimum(-99);
		repSpins_.push_back(repSpin);
		repLayout_->addRow(KingdomLabels[KingdomsForReputation[i]], repSpins_.back());
		connect(repSpins_.back(), static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
			this, &PrizeEdit::updateKingdom);
	}
}

void PrizeEdit::initLayout()
{
	QFormLayout *mainLayout = new QFormLayout;
	mainLayout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
	setLayout(mainLayout);

	mainLayout->addRow(tr("Experience"), experienceEdit_);
	mainLayout->addRow(tr("Gold"),       goldEdit_);
	mainLayout->addRow(tr("Reputation"), repLayout_);
}

void PrizeEdit::simulateFocusLoss()
{
	setFocus(Qt::OtherFocusReason);
	clearFocus();
}

void PrizeEdit::updateExperience(int x)
{
	prize_.setExperience(x);
	emit prizeChanged(prize_);
	simulateFocusLoss();
}

void PrizeEdit::updateGold(int x)
{
	prize_.setGold(x);
	emit prizeChanged(prize_);
	simulateFocusLoss();
}

void PrizeEdit::updateKingdom(int value)
{
	for (int i = 0; i < repSpins_.size(); i++) {
		if (sender() == repSpins_[i]) {
			prize_.addReputation(KingdomsForReputation[i], value);
			break;
		}
	}
	emit prizeChanged(prize_);
	simulateFocusLoss();
}
