#pragma once

#include <QtCore>
#include "Core/Strings.h"
#include "Core/Utils/Serial.hpp"
#include "Core/Containers/Bases/ItemBase.h"

class ItemBase;

class ItemModel : public QAbstractTableModel {
public:
	static const int Name              = 0;
	static const int Type              = 1;
	static const int Price             = 2;
	static const int Quality           = 3;
	static const int Effects           = 4;
	static const int ColumnCount       = 5;

	explicit ItemModel(QObject *parent = nullptr);
	ItemModel(const ItemModel &) = delete;
	ItemModel(ItemModel &&) = delete;
	void operator=(const ItemModel &) = delete;
	void operator=(ItemModel &&) = delete;
	~ItemModel();

	int columnCount(const QModelIndex &index = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;
	bool empty() const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	bool hasItem(const QString &name) const;
	const ItemBase * itemInRow(int row) const;
	const ItemBase * item(UID uid) const;
	const ItemBase * item(const QModelIndex &index) const;
	const ItemBase * item(const QString &name) const;
	const QList <ItemBase *> & items() const;
	bool isChanged() const;
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QDataStream & toDataStream(QDataStream &out) const;

	void addNewItem();
	QDataStream & fromDataStream(QDataStream &in);
	bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
	void removeItem(UID uid);
	bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
	void reset();
	void setChanged(bool changed);
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

private:
	void addItem(int row, ItemBase *item);
	void removeItemFromRow(int row);

	bool changed_;
	QList <ItemBase *> items_;
	Serial serial_;
	QHash <UID, ItemBase *> uidToItem_;
};
QDataStream & operator<<(QDataStream &out, const ItemModel &model);
QDataStream & operator>>(QDataStream &in, ItemModel &model);