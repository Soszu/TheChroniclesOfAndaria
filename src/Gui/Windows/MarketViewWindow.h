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
