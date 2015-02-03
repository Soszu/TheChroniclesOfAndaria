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

#ifndef MYTASKBAR_H
#define MYTASKBAR_H

#include <QtWidgets>

//TODO CFiend zmianic nazwe klasy?
//TODO CFiend ta klasa chyba probuje robic zbyt wiele jednoczesnie
class MyTaskbar : public QWidget {

public:
	MyTaskbar(qreal d, QColor c);
	MyTaskbar(qreal d1, qreal d2, QColor c1, QColor c2);
	MyTaskbar(int n, int p, QColor c);
	void fill(qreal newD);
	void fillFirst(qreal newD);
	void fillSecond(qreal newD);
	void setMarkerCount(int markerCnt);
	QSize sizeHint();
	QSize minimumSizeHint();

protected:
	void paintEvent(QPaintEvent *e);

private:
	static const int MinLength = 66;
	static const int Width = 20;

	int height_;
	int width_;
	bool markersVisible_;
	bool isTwoParted_;
	qreal firstLength_;
	qreal secondLength_;
	QColor firstColor_;
	QColor secondColor_;
	int markerCount_;
	int markerLimit_;

};

#endif
