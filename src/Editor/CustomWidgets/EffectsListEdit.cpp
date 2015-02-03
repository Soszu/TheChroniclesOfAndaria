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
#include "Editor/CustomWidgets/EffectsListEdit.hpp"
#include "Editor/Strings.hpp"
#include "Editor/Shortcuts.hpp"

EffectsListEdit::EffectsListEdit(QWidget *parent) :
	QWidget(parent)
{
	setFocusPolicy(Qt::FocusPolicy::ClickFocus);
	initButtons();
	initEdits();
	initList();
	initLayout();
}

QList <Effect> EffectsListEdit::effects() const
{
	return effects_;
}

void EffectsListEdit::reset()
{
	effectsModel_->removeRows(0, effects_.count());
	emit effectsChanged(effects_);
}

void EffectsListEdit::setEffects(const QList <Effect> &effects)
{
	if (effects_ == effects)
		return;

	QStringList effectsNames;
	for (auto effect : effects)
		effectsNames.append(Effect::description(effect));
	effectsModel_->setStringList(effectsNames);
	effects_ = effects;
	emit effectsChanged(effects_);
	simulateFocusLoss();
}

void EffectsListEdit::addEffect()
{
	effectsModel_->insertRow(effects_.count());
	effects_.push_back(Effect());
	effectsModel_->setData(effectsModel_->index(effects_.count() - 1), Effect::description(effects_.back()));
	emit effectsChanged(effects_);
	simulateFocusLoss();
}

void EffectsListEdit::removeEffect()
{
	QModelIndex selected = listView_->selectionModel()->currentIndex();
	if (!selected.isValid())
		return;

	effectsModel_->removeRow(selected.row());
	effects_.removeAt(selected.row());
	emit effectsChanged(effects_);
	simulateFocusLoss();
}

void EffectsListEdit::updateEdits(const QModelIndex& index)
{
	if (!index.isValid())
		return;

	Effect &effect = effects_[index.row()];
	typeEdit_->setCurrentIndex(typeEdit_->findText(Effect::TypeLabels[effect.type()]));
	valueEdit_->setValue(effect.value());
	durationEdit_->setValue(effect.duration());
}

void EffectsListEdit::updateType(QString text)
{
	QModelIndex selected = listView_->selectionModel()->currentIndex();
	if (!selected.isValid())
		return;

	effects_[selected.row()].setType(Effect::TypeLabels[text]);
	effectsModel_->setData(selected, Effect::description(effects_[selected.row()]));
	emit effectsChanged(effects_);
	simulateFocusLoss();
}

void EffectsListEdit::updateValue(int x)
{
	QModelIndex selected = listView_->selectionModel()->currentIndex();
	if (!selected.isValid())
		return;

	effects_[selected.row()].setValue(x);
	effectsModel_->setData(selected, Effect::description(effects_[selected.row()]));
	emit effectsChanged(effects_);
	simulateFocusLoss();
}

void EffectsListEdit::updateDuration(int x)
{
	QModelIndex selected = listView_->selectionModel()->currentIndex();
	if (!selected.isValid())
		return;

	effects_[selected.row()].setDuration(x);
	effectsModel_->setData(selected, Effect::description(effects_[selected.row()]));
	emit effectsChanged(effects_);
	simulateFocusLoss();
}

void EffectsListEdit::initButtons()
{
	addEffectButton_ = new QPushButton(Editor::Labels::Effects::Add);
	addEffectButton_->setShortcut(Editor::Shortcuts::SecondaryAdd);
	connect(addEffectButton_, &QPushButton::clicked, this, &EffectsListEdit::addEffect);

	removeEffectButton_ = new QPushButton(Editor::Labels::Effects::Remove);
	removeEffectButton_->setShortcut(Editor::Shortcuts::SecondaryRemove);
	connect(removeEffectButton_, &QPushButton::clicked, this, &EffectsListEdit::removeEffect);
}

void EffectsListEdit::initEdits()
{
	typeEdit_ = new QComboBox;
	for (auto type : Effect::TypeLabels.leftKeys())
		typeEdit_->addItem(Effect::TypeLabels[type], QVariant::fromValue(type));
	connect(typeEdit_, static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
	        this, &EffectsListEdit::updateType);

	valueEdit_ = new QSpinBox;
	durationEdit_ = new QSpinBox;

	connect(valueEdit_, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
	        this, &EffectsListEdit::updateValue);
	connect(durationEdit_, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
	        this, &EffectsListEdit::updateDuration);
}

void EffectsListEdit::initList()
{
	effectsModel_ = new QStringListModel(this);

	listView_ = new QListView;
	listView_->setModel(effectsModel_);

	connect(listView_, &QListView::clicked, this, &EffectsListEdit::updateEdits);
}

void EffectsListEdit::initLayout()
{
	QHBoxLayout *itemEffectsLayout = new QHBoxLayout(this);
	QLabel *listLabel = new QLabel(Editor::Labels::Effects::List);
	QGroupBox *effectDetails = new QGroupBox(Editor::Labels::Effects::Details);
	QFormLayout *effectDetailsLayout = new QFormLayout(effectDetails);
	QVBoxLayout *effectsListLayout = new QVBoxLayout;
	QHBoxLayout *buttonsLayout = new QHBoxLayout;

	itemEffectsLayout->addWidget(effectDetails);
	itemEffectsLayout->addLayout(effectsListLayout);

	effectDetailsLayout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
	effectDetailsLayout->addRow(Labels::Effect::Type,     typeEdit_);
	effectDetailsLayout->addRow(Labels::Effect::Value,    valueEdit_);
	effectDetailsLayout->addRow(Labels::Effect::Duration, durationEdit_);

	effectsListLayout->addWidget(listLabel);
	effectsListLayout->addWidget(listView_);
	effectsListLayout->addLayout(buttonsLayout);

	buttonsLayout->addWidget(addEffectButton_);
	buttonsLayout->addWidget(removeEffectButton_);
	buttonsLayout->addStretch();
}

void EffectsListEdit::simulateFocusLoss()
{
	setFocus(Qt::OtherFocusReason);
	clearFocus();
}