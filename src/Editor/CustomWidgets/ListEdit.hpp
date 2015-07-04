/*
Copyright (C) 2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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
#pragma once

#include <QtWidgets>

class ListEdit : public QWidget {
	Q_OBJECT
public:
	ListEdit(QWidget * parent = nullptr);

protected:
	virtual QWidget * createEditWidget() = 0;
	virtual void rowRemoved(int index) = 0;
	//reset does not call editRemoved
	void reset();
	//setEdits does not call editRemoved nor createEditWidget
	void setEdits(const QList<QWidget *> & edits);

private:
	void initLayout();
	void addEdit(QWidget * edit);
	void removeRow(int index);
	void addRow(QWidget * btn, QWidget * widget = nullptr);

	QList<QWidget *> edits_;
	QList<QWidget *> minuses_;
	QVBoxLayout * mainLayout_;
	QSignalMapper buttonsMapper_;

private slots:
	void onEditAdded();
	void onEditRemoved(QWidget * widget);
};
