#ifndef ITEM_PROXY_MODEL_H
#define ITEM_PROXY_MODEL_H

#include <QIdentityProxyModel>
#include "ItemModel.h"

class ItemProxyModel : public QIdentityProxyModel {
public :
	
	virtual int columnCount(const QModelIndex &parent = QModelIndex()) const
	{
		return ColumnCount; 
	}
	
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const
	{
		if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
			return QVariant();
		
		switch (section) {
			case Name : return tr("Name");
			case Value : return tr("Value");
		}
		
		return QVariant();
	}
	
	QVariant data(const QModelIndex &index, int role) const
	{
		if (role != Qt::DisplayRole || !index.isValid())
			return QIdentityProxyModel::data(index, role);
		
		switch(index.column()) {
			case Name: return sourceModel()->data(sourceModel()->index(index.row(), ItemModel::Name)); break;
			case Value: return sourceModel()->data(sourceModel()->index(index.row(), ItemModel::Value)); break;
		}
		return QVariant();
	}
	
	static const int Name = 0;
	static const int Value = 1;
	static const int ColumnCount = 2;
};



#endif