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
#include "Editor/CustomWidgets/ObjectiveEdit.hpp"

#include "Editor/CustomWidgets/EnumEdit.hpp"

ObjectiveEdit::ObjectiveEdit(const Objective & objective, QWidget * parent) :
	QWidget(parent),
	objective_(objective)
{
	initLayout();
	updateWidgets();
}

const Objective & ObjectiveEdit::objective() const
{
	return objective_;
}

void ObjectiveEdit::setObjective(const Objective & objective)
{
	if (objective == objective_)
		return;

	objective_ = objective;
	updateWidgets();

	emit contentChanged();
}

void ObjectiveEdit::reset()
{
	objective_ = Objective::SimpleObjective;
	emit contentChanged();
}

void ObjectiveEdit::initLayout()
{
	auto layout = new QHBoxLayout;
	setLayout(layout);

	//TODO add coordsEdit

	priorityEdit_ = new QSpinBox;
	connect(priorityEdit_, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
			this, &ObjectiveEdit::updatePriority);
	layout->addWidget(priorityEdit_);

	testTypeEdit_ = new EnumEdit;
	for (auto & type : Test::TypeLabels.leftKeys())
		testTypeEdit_->addItem(Test::TypeLabels[type], QVariant::fromValue(type));
	connect(testTypeEdit_, &EnumEdit::valueChanged, this, &ObjectiveEdit::updateTestType);
	layout->addWidget(testTypeEdit_);

	//TODO add testData Edit
}

void ObjectiveEdit::updateCoordinates(const Coordinates & coords)
{
	objective_.coords = coords;
	emit contentChanged();
}

void ObjectiveEdit::updatePriority(int x)
{
	objective_.priority = x;
	emit contentChanged();
}

void ObjectiveEdit::updateTestType(const QVariant & typeVar)
{
	Test::Type type = typeVar.value<Test::Type>();
	objective_.testData.setType(type);
	emit contentChanged();
}

void ObjectiveEdit::updateTestData(const QVariant & data)
{
	objective_.testData.setData(data);
	emit contentChanged();
}

void ObjectiveEdit::updateWidgets()
{
	priorityEdit_->setValue(objective_.priority);
	testTypeEdit_->setValue(QVariant::fromValue(objective_.testData.type()));

	//TODO update widgets when added
}
