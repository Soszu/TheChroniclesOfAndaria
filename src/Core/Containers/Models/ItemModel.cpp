#include "Core/Containers/Models/ItemModel.h"

#include "Core/Containers/Bases/ItemBase.h"

ItemModel::ItemModel(QObject *parent) : QAbstractTableModel(parent), changed_(false)
{
	auto modelChanged = [this]{
		this->changed_ = true;
	};

	connect(this, &QAbstractTableModel::dataChanged,  modelChanged);
	connect(this, &QAbstractTableModel::rowsInserted, modelChanged);
	connect(this, &QAbstractTableModel::rowsMoved,    modelChanged);
	connect(this, &QAbstractTableModel::rowsRemoved,  modelChanged);
}

ItemModel::~ItemModel()
{
	qDeleteAll(items_);
}

int ItemModel::columnCount(const QModelIndex& index) const
{
	if (index.isValid())
		return 0;
	return ColumnCount;
}

QVariant ItemModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role == Qt::DisplayRole || role == Qt::EditRole) {
		const ItemBase *item = items_[index.row()];
		switch (index.column()) {
			case Name:                return item->name();
			case Type:                return QVariant::fromValue(item->type());
			case Price:               return item->price();
			case Quality:             return QVariant::fromValue(item->quality());
			case Effects:             return QVariant::fromValue(item->effects());
		}
	}

	return QVariant();
}

bool ItemModel::empty() const
{
	return items_.empty();
}

Qt::ItemFlags ItemModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;
	return Qt::ItemIsEnabled | Qt::ItemNeverHasChildren | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

bool ItemModel::hasItem(const QString &name) const
{
	return item(name) != nullptr;
}

const ItemBase * ItemModel::itemInRow(int row) const
{
	return items_.value(row, nullptr);
}

const ItemBase * ItemModel::item(UID uid) const
{
	return uidToItem_.value(uid, nullptr);
}

const ItemBase * ItemModel::item(const QModelIndex &index) const
{
	return items_.value(index.row(), nullptr);
}

const ItemBase * ItemModel::item(const QString &name) const
{
	for (const ItemBase * item : items_)
		if (item->name() == name)
			return item;

		return nullptr;
}

const QList <ItemBase *> & ItemModel::items() const
{
	return items_;
}

bool ItemModel::isChanged() const
{
	return changed_;
}

int ItemModel::rowCount(const QModelIndex &parent) const
{
	return items_.count();
}

QDataStream &ItemModel::toDataStream(QDataStream &out) const
{
	out << serial_ << static_cast<UID>(items_.count());
	for (const ItemBase *item : items_)
		out << *item;
	return out;
}

void ItemModel::addNewItem(){
	insertRows(items_.count(), 1);
}

QDataStream &ItemModel::fromDataStream(QDataStream &in)
{
	beginResetModel();
	qDeleteAll(items_);
	items_.clear();
	uidToItem_.clear();

	UID count;
	in >> serial_ >> count;
	for (UID i = 0; i < count; ++i) {
		ItemBase *item = new ItemBase;
		in >> *item;
		addItem(i, item);
	}
	endResetModel();

	return in;
}

bool ItemModel::insertRows(int row, int count, const QModelIndex &parent)
{
	int nameSuffix = 0;
	beginInsertRows(QModelIndex(), row, row + count - 1);
	for (int i = 0; i < count; ++i) {
		QString itemName;
		do {
			++nameSuffix;
			itemName = QString("%1 %2").arg(Labels::Item::DefaultName).arg(nameSuffix);
		} while (hasItem(itemName));

		items_.insert(row + i, new ItemBase(serial_.next(), itemName));
	}
	endInsertRows();

	return true;
}

void ItemModel::removeItem(UID uid)
{
	for (int i = 0; i < items_.count(); ++i) {
		if (items_[i]->uid() == uid) {
			beginRemoveRows(QModelIndex(), i, i);
			delete items_.takeAt(i);
			endRemoveRows();
			uidToItem_.remove(uid);
			return;
		}
	}
}

bool ItemModel::removeRows(int row, int count, const QModelIndex &parent)
{
	beginRemoveRows(QModelIndex(), row, row + count - 1);
	for (int i = 0; i < count; ++i)
		removeItemFromRow(row);
	endRemoveRows();

	return true;
}

void ItemModel::reset()
{
	beginResetModel();
	removeRows(0, rowCount());
	serial_.reset();
	endResetModel();
}

void ItemModel::setChanged(bool changed)
{
	changed_ = changed;
}

bool ItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (!index.isValid() || role != Qt::EditRole)
		return false;

	ItemBase *item = items_[index.row()];
	switch (index.column()) {
		case Name:    item->setName(value.toString()); break;
		case Type:    item->setType(value.value<ItemBase::Type>()); break;
		case Quality: item->setQuality(value.value<ItemBase::Quality>()); break;
		case Price:   item->setPrice(value.toInt()); break;
		case Effects: item->setEffects(value.value<QList <Effect> >()); break;
	}

	emit dataChanged(index, index);

	return true;
}

void ItemModel::addItemBase(ItemBase* item)
{
	beginResetModel();

	addItem(rowCount(), item);

	endResetModel();
}

void ItemModel::addItem(int row, ItemBase* item)
{
	items_.insert(row, item);
	uidToItem_[item->uid()] = item;
}

void ItemModel::removeItemFromRow(int row)
{
	uidToItem_.remove(items_[row]->uid());
	delete items_.takeAt(row);
}

QDataStream & operator<<(QDataStream &out, const ItemModel &model)
{
	return model.toDataStream(out);
}

QDataStream & operator>>(QDataStream &in, ItemModel &model)
{
	return model.fromDataStream(in);
}