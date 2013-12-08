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
	connect(tableView_, &QTableView::clicked, this, &MarketViewWindow::setRowInSecondView);
	
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
	someOtherModel_->insertRows(0, 5);
}

void MarketViewWindow::changeModel()
{
	static bool changed = false;
	tableView_->setModel(changed ? itemModel_ : someOtherModel_);
	tableView2_->setModel(changed ? itemModel_ : someOtherModel_);
	changed = !changed;
}

void MarketViewWindow::setRowInSecondView(const QModelIndex & index)
{
	static int previousRow = 0;
	tableView2_->hideRow(previousRow);
	tableView2_->showRow(index.row());
	previousRow = index.row();
}

