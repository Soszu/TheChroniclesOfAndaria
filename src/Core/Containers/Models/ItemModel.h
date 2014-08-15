#ifndef ITEMMODEL_H
#define ITEMMODEL_H

#include "Core/Containers/Item.h"
#include <QVector>

class ItemModel : public QAbstractTableModel {
	Q_OBJECT;
public:
	explicit ItemModel(QObject *parent = nullptr);
	
	int columnCount(const QModelIndex & index = QModelIndex()) const;
	int rowCount(const QModelIndex & = QModelIndex()) const;
	
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	Qt::ItemFlags flags(const QModelIndex &index = QModelIndex()) const;

	bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
	bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

	static const int Uid = 0;
	static const int Name = 1;
	static const int Type = 2;
	static const int BonusHitPoints = 3;
	static const int BonusDefence = 4;
	static const int BonusPerception = 5;
	static const int BonusMeleeMin = 6;
	static const int BonusMeleeRng = 7;
	static const int BonusRangedMin = 8;
	static const int BonusRangedRng = 9;
	static const int BonusMagicalMin = 10;
	static const int BonusMagicalRng = 11;
	static const int BonusRegeneration = 12;
	static const int BonusMovePoints = 13;
	static const int RestrictionFighter = 14;
	static const int RestrictionRanger = 15;
	static const int RestrictionMage = 16;
	static const int RestrictionDruid = 17;
	static const int Value = 18;
	static const int ColumnCount = 19;
	
	friend QDataStream & operator<<(QDataStream &out, const ItemModel &itemModel);
	friend QDataStream & operator>>(QDataStream &in, ItemModel &itemModel);
protected:
	Serial serial_;
	QVector <Item *> items_;
};


#endif
