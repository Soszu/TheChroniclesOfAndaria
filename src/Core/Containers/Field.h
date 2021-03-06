/*
Copyright (C) 2013 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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

#ifndef FIELD_H
#define FIELD_H

#include <QtCore>

typedef QPoint FieldId;

class Field {

public:
	Field(FieldId fieldId, QString name, int coefficient, bool hasEnemy, bool hasCity, QString imageFile, int fraction);
	FieldId fieldId() const;
	QString name() const;
	int moveCost() const;
	bool hasEnemy() const;
	bool hasCity() const;
	QString imageFile() const;
	int fraction() const;

private:
	FieldId fieldId_;
	QString name_;
	int moveCost_;
	bool hasEnemy_;
	bool hasCity_;
	QString imageFile_;
	int fraction_;
};

#endif
