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

#include "Core/Containers/Bases/QuestBase.hpp"

class EnumEdit;
class CoordsEdit;

class ObjectiveEdit : public QWidget {
	Q_OBJECT
	Q_PROPERTY(Objective objective
	           READ objective
	           WRITE setObjective
	           RESET reset
	           NOTIFY contentChanged
	           USER true)

public:
	ObjectiveEdit(const Objective & objective = Objective::SimpleObjective,
	              QWidget * parent = nullptr);

	const Objective & objective() const;

	void setObjective(const Objective & objective);

public slots:
	void reset();

private:
	void initLayout();

	Objective objective_;

	CoordsEdit * coordsEdit_;
	QSpinBox * priorityEdit_;
	EnumEdit * testTypeEdit_;
	QWidget * testDataEdit_;

private slots:
	void updateCoordinates(const Coordinates & coords);
	void updatePriority(int x);
	void updateTestType(const QVariant & typeVar);
	void updateTestData(const QVariant & data);
	void updateWidgets();

signals:
	void contentChanged();
};
