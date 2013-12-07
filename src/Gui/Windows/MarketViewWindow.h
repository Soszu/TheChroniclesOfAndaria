#ifndef MARKETVIEWWINDOW_H
#define MARKETVIEWWINDOW_H

#include <QtWidgets>
#include <Core/Containers/ItemModel.h>

class MarketViewWindow : public QDialog {
	Q_OBJECT;
public:
	MarketViewWindow(ItemModel * model);

private:
	void createOtherModel();
	
	ItemModel *itemModel_;
	ItemModel *someOtherModel_;
	QColumnView *columnview_;
	QTableView *tableView_;
	QTableView *tableView2_;
	QListView *listView_;
	QTreeView *treeView_;
	
private slots:
	void changeModel();
};

#endif
