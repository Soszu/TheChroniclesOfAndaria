/*
Copyright (C) 2014-2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
Copyright (C) 2015 by Bartosz Szreder <szreder [at] mimuw [dot] edu [dot] pl>
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

ObjectiveEdit::ObjectiveEdit(QWidget * parent) :
	QWidget(parent),
	objective_(Objective::SimpleObjective)
{
	initLayout();
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
	emit objectiveChanged();
}

void ObjectiveEdit::reset()
{
	objective_ = Objective::SimpleObjective;
	emit objectiveChanged();
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
	emit objectiveChanged();
}

void ObjectiveEdit::updatePriority(int x)
{
	objective_.priority = x;
	emit objectiveChanged();
}

void ObjectiveEdit::updateTestType(const QVariant & typeVar)
{
	Test::Type type = typeVar.value<Test::Type>();
	objective_.testData.setType(type);
	emit objectiveChanged();
}

void ObjectiveEdit::updateTestData(const QVariant & data)
{
	objective_.testData.setData(data);
	emit objectiveChanged();
}
