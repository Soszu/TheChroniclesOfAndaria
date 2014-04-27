/*
Copyright (C) 2014 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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

#ifndef CONTENTEDITOR_H
#define CONTENTEDITOR_H

#include <QtWidgets>

class ContentEditor : public QObject
{
Q_OBJECT

public:
	ContentEditor(const QString &name);

	QString name() const;
	QWidget * widget() const;

	virtual void clear(){}
	virtual bool isChanged() const = 0;
	virtual void saveToStream(QDataStream &out) const = 0 ;
	virtual void loadFromStream(QDataStream &in) = 0;

public slots:
	virtual void modelSaved() = 0;

protected:
	QWidget *widget_;
	QString name_;
};

#endif // CONTENTEDITOR_H
