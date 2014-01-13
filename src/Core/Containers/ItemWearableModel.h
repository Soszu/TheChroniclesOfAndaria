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