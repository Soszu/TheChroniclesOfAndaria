/*
Copyright (C) 2013 Łukasz Piesiewicz <wookesh [at] gmail [dot] com>
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

#ifndef ITEMWEARABLEMODEL_H
#define ITEMWEARABLEMODEL_H
#include <Core/Containers/ItemModel.h>
#include <Core/Containers/ItemWearable.h>

class ItemWearableModel : public ItemModel {
	Q_OBJECT;
public :
	explicit ItemWearableModel(QObject *parent = nullptr);
	
	int columnCount(const QModelIndex & = QModelIndex()) const;
	int rowCount(const QModelIndex & = QModelIndex()) const;
	
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
	bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
	
	
	static constexpr int IsComplex = ItemModel::ColumnCount;
	static constexpr int ColumnCount = ItemModel::ColumnCount + 1;
	
	friend QDataStream &operator>>(QDataStream &in, ItemWearableModel &itemWearableModel);
	friend QDataStream &operator<<(QDataStream &out, const ItemWearableModel &itemWearableModel);
};


#endif