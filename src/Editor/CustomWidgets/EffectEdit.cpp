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
#include "Editor/CustomWidgets/EffectEdit.hpp"

#include "Editor/CustomWidgets/EnumEdit.hpp"

EffectEdit::EffectEdit(const Effect & effect, QWidget * parent) :
	QWidget(parent),
	effect_(effect)
{
	initLayout();
	updateWidgets();
}

const Effect & EffectEdit::effect() const
{
	return effect_;
}

void EffectEdit::setEffect(const Effect & effect)
{
	if (effect == effect_)
		return;

	effect_ = effect;
	updateWidgets();

	emit contentChanged();
}

void EffectEdit::reset()
{
	effect_ = Effect();
	emit contentChanged();
}

void EffectEdit::initLayout()
{
	auto layout = new QHBoxLayout;
	setLayout(layout);

	typeEdit_ = new EnumEdit;
	for (auto type : Effect::TypeLabels.leftKeys())
		typeEdit_->addItem(Effect::TypeLabels[type], QVariant::fromValue(type));
	connect(typeEdit_, &EnumEdit::valueChanged,
			this, &EffectEdit::updateType);
	layout->addWidget(typeEdit_);

	durationEdit_ = new QSpinBox;
	connect(durationEdit_, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
			this, &EffectEdit::updateDuration);
	layout->addWidget(durationEdit_);

	valueEdit_ = new QSpinBox;
	connect(valueEdit_, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
			this, &EffectEdit::updateValue);
	layout->addWidget(valueEdit_);
}

void EffectEdit::updateType(const QVariant & typeVar)
{
	Effect::Type type = typeVar.value<Effect::Type>();
	effect_.setType(type);
	emit contentChanged();
}

void EffectEdit::updateDuration(int x)
{
	effect_.setDuration(x);
	emit contentChanged();
}

void EffectEdit::updateValue(int x)
{
	effect_.setValue(x);
	emit contentChanged();
}

void EffectEdit::updateWidgets()
{
	typeEdit_->setValue(QVariant::fromValue(effect_.type()));
	durationEdit_->setValue(effect_.duration());
	valueEdit_->setValue(effect_.value());
}
