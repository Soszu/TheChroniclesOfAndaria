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

#include <Game/Windows/MarketViewWindow.h>

int ItemProxyModel::columnCount(const QModelIndex &parent) const
{
	return ColumnCount; 
}

QVariant ItemProxyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
		return QVariant();
	
	switch (section) {
		case Name : return tr("Name");
		case Value : return tr("Value");
	}
	
	return QVariant();
}

QVariant ItemProxyModel::data(const QModelIndex &index, int role) const
{
	if (role != Qt::DisplayRole || !index.isValid())
		return QIdentityProxyModel::data(index, role);
	
	switch(index.column()) {
		case Name: return sourceModel()->data(sourceModel()->index(index.row(), ItemModel::Name)); break;
		case Value: return sourceModel()->data(sourceModel()->index(index.row(), ItemModel::Value)); break;
	}
	return QVariant();
}

MarketViewWindow::MarketViewWindow(ItemModel *model): QDialog()
{
	resize(800, 600);
	
	QPushButton *changeModelButton = new QPushButton("Sell/Buy", this);
	
	itemModel_ = model;
	createOtherModel();
	
	ItemProxyModel *proxy = new ItemProxyModel();
	proxy->setSourceModel(itemModel_);
	
	tableView_ = new QTableView(this);
	tableView_->setModel(wearableModel_);
	tableView_->setSelectionBehavior(QAbstractItemView::SelectRows);
	tableView_->setSelectionMode(QAbstractItemView::SingleSelection);
	
	connect(changeModelButton, &QPushButton::clicked, this, &MarketViewWindow::changeModel);
	
	tableView2_ = new QTableView(this);
	tableView2_->setModel(itemModel_);
	for (int i = 0; i < itemModel_->rowCount(); ++i)
		tableView2_->hideRow(i);

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(changeModelButton, 0, 0, 1, 1);
	layout->addWidget(tableView_, 1, 0, 1, 1);
	layout->addWidget(tableView2_, 0, 1, 2, 1);
	setLayout(layout);
}


void MarketViewWindow::createOtherModel()
{
	someOtherModel_ = new ItemModel();
	someOtherModel_->insertRows(0, 2);
	wearableModel_ = new ItemWearableModel();
	wearableModel_->insertRows(0, 4);
}

void MarketViewWindow::changeModel()
{
	static bool changed = false;
	tableView_->setModel(changed ? wearableModel_ : someOtherModel_);
	//tableView2_->setModel(changed ? itemModel_ : wearableModel_);
	changed = !changed;
}
