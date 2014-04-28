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

#ifndef MARKETVIEWWINDOW_H
#define MARKETVIEWWINDOW_H

#include <QtWidgets>
#include <QIdentityProxyModel>
#include "Core/Containers/ItemModel.h"
#include "Core/Containers/ItemWearableModel.h"

class ItemProxyModel : public QIdentityProxyModel {
public :
	
	virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	QVariant data(const QModelIndex &index, int role) const;
	
	static const int Name = 0;
	static const int Value = 1;
	static const int ColumnCount = 2;
};

class MarketViewWindow : public QDialog {
	Q_OBJECT;
public:
	MarketViewWindow(ItemModel * model);

private:
	void createOtherModel();
	
	ItemModel *itemModel_;
	ItemModel *someOtherModel_;
	ItemWearableModel *wearableModel_;
	QColumnView *columnview_;
	QTableView *tableView_;
	QTableView *tableView2_;
	QListView *listView_;
	QTreeView *treeView_;
	
private slots:
	void changeModel();
};

#endif
