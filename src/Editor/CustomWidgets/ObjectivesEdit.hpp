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

#include <QtCore>

#include "Editor/CustomWidgets/ListEdit.hpp"
#include "Editor/CustomWidgets/ObjectiveEdit.hpp"
#include "Core/Containers/Bases/QuestBase.hpp"

class ObjectivesEdit : public ListEdit {
	Q_OBJECT
	Q_PROPERTY(QList<Objective> objectives
	           READ objectives
	           WRITE setObjectives
	           RESET reset
	           NOTIFY contentChanged
	           USER true)

public:
	ObjectivesEdit(QWidget * parent = nullptr);

	QList<Objective> objectives() const;
	void setObjectives(const QList<Objective> & objectives);

	void reset();

private:
	QWidget * createEditWidget();
	void rowRemoved(int index) override;

	QList<ObjectiveEdit *> objectiveEdits_;

signals:
	void contentChanged();
};
