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
#include "Editor/CustomWidgets/ObjectivesEdit.hpp"

#include "Editor/CustomWidgets/ObjectiveEdit.hpp"

ObjectivesEdit::ObjectivesEdit(QWidget * parent) : ListEdit(parent)
{}

QList<Objective> ObjectivesEdit::objectives() const
{
	QList<Objective> objectives;
	for (auto obj : objectiveEdits_)
		objectives.append(obj->objective());

	return objectives;
}

void ObjectivesEdit::setObjectives(const QList<Objective> & objectives)
{
	if (this->objectives() == objectives)
		return;

	objectiveEdits_.clear();
	QList<QWidget *> edits;
	for (auto & obj : objectives) {
		auto oe = new ObjectiveEdit(obj);
		objectiveEdits_.append(oe);
		connect(oe, &ObjectiveEdit::contentChanged, this, &ObjectivesEdit::contentChanged);
		edits.append(oe);
	}

	ListEdit::setEdits(edits);
}

void ObjectivesEdit::reset()
{
	objectiveEdits_.clear();

	emit contentChanged();

	ListEdit::reset();
}

QWidget * ObjectivesEdit::createEditWidget()
{
	auto oe = new ObjectiveEdit;
	objectiveEdits_.append(oe);
	connect(oe, &ObjectiveEdit::contentChanged, this, &ObjectivesEdit::contentChanged);

	emit contentChanged();

	return oe;
}

void ObjectivesEdit::rowRemoved(int index)
{
	if (index < 0 || index > objectiveEdits_.count())
		return;

	objectiveEdits_.removeAt(index);
	emit contentChanged();
}
