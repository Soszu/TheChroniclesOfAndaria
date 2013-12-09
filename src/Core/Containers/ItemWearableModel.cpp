#include <Core/Containers/ItemWearableModel.h>

ItemWearableModel::ItemWearableModel(QObject *parent): ItemModel(parent)
{
}

int ItemWearableModel::columnCount(const QModelIndex &) const
{
	return ItemWearableModel::ColumnCount;
}

int ItemWearableModel::rowCount(const QModelIndex &) const
{
	return items_.count();
}

QVariant ItemWearableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
		return QVariant();

	switch (section) {
		case IsComplex : return tr("Is Complex");
		default : return ItemModel::headerData(section, orientation, role);
	}

	return QVariant();
}


QVariant ItemWearableModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid() || (role != Qt::DisplayRole))
		return QVariant();
	
	const ItemWearable * item = static_cast<ItemWearable *>(items_[index.row()]);
	switch (index.column()) {
		case IsComplex : return item->isComplex(); break;
		default : return ItemModel::data(index, role); break;
	}
	
	return QVariant();
}

bool ItemWearableModel::insertRows(int row, int count, const QModelIndex &parent)
{
	beginInsertRows(QModelIndex(), row, row + count - 1);
	for (int i = 0; i < count; ++i) {
		ItemWearable * item = new ItemWearable(//serial_.next(),
									  "Default",
								     //CharacterStats(),
									  Item::Type::OneHanded,
								     //QMap <Player::Class, bool>(),
									  1,
									  Item::Quality::Good,
									  true);
		items_.insert(row, item);
	}
	endInsertRows();

	return true;
}

bool ItemWearableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    return ItemModel::removeRows(row, count, parent);
}



