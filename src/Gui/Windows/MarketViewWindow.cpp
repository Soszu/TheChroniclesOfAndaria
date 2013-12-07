#include <Gui/Windows/MarketViewWindow.h>
#include <Core/Containers/ItemProxyModel.h>

MarketViewWindow::MarketViewWindow(ItemModel *model): QDialog()
{
	resize(800, 600);
	
	QPushButton *changeModelButton = new QPushButton("Sell/Buy", this);
	
	this->itemModel_ = model;
	createOtherModel();
	
		
	ItemProxyModel *proxy = new ItemProxyModel();
	proxy->setSourceModel(itemModel_);
	
	tableView_ = new QTableView(this);
	tableView_->setModel(proxy);
	tableView_->setSelectionBehavior(QAbstractItemView::SelectRows);
	tableView_->setSelectionMode(QAbstractItemView::SingleSelection);
	
	connect(changeModelButton, &QPushButton::clicked, this, &MarketViewWindow::changeModel);
	
	tableView2_ = new QTableView(this);
	tableView2_->setModel(itemModel_);

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(changeModelButton, 0, 0, 1, 1);
	layout->addWidget(tableView_, 1, 0, 1, 1);
	layout->addWidget(tableView2_, 0, 1, 2, 1);
	setLayout(layout);
}


void MarketViewWindow::createOtherModel()
{
	someOtherModel_ = new ItemModel(nullptr);
	someOtherModel_->insertRows(0, 5);
}

void MarketViewWindow::changeModel()
{
	static bool changed = false;
	tableView_->setModel(changed ? itemModel_ : someOtherModel_);
	//treeView_->setModel(changed ? itemModel_ : someOtherModel_);
	changed = !changed;
}

