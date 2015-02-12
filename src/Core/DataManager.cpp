/*
Copyright (C) 2013-2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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
#include "DataManager.hpp"
#include "Paths.hpp"

QHash <QString, QPixmap *> DataManager::pixmapsMap;

const QPixmap & DataManager::pixmap(const QString& pathName)
{
	const QString path = resolvePath(pathName);
	if (!pixmapsMap.contains(path)) {
		QPixmap *image = new QPixmap();
		if (!image->load(path)) {
			qCritical() << "Error while loading file " << path;
			exit(EXIT_FAILURE);
		}
		pixmapsMap[path] = image;
	}
	return *pixmapsMap[path];
}
