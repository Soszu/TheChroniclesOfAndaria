#include "Core/Containers/ItemModel.h"


ItemModel::ItemModel(QObject *parent): QAbstractTableModel(parent)
{
}

int ItemModel::columnCount(const QModelIndex &) const
{
	return ColumnCount;
}

int ItemModel::rowCount(const QModelIndex &) const
{
	return items.count();
}

Qt::ItemFlags ItemModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;
	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}


QVariant ItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
		return QVariant();

	switch (section) {
		case Uid : return tr("ID");
		case Name : return tr("Name");
		case Type : return tr("Type");;
		case BonusHitPoints : return tr("BonusHitPoints");
		case BonusDefence : return tr("BonusDefence");
		case BonusPerception : return tr("BonusPerception");;
		case BonusMeleeMin : return tr("BonusMeleeMin");
		case BonusMeleeRng : return tr("BonusMeleeRng");
		case BonusRangedMin : return tr("BonusRangedMin");
		case BonusRangedRng : return tr("BonusRangedRng");
		case BonusMagicalMin : return tr("BonusMagicalMin");
		case BonusMagicalRng : return tr("BonusMagicalRng");
		case BonusRegeneration : return tr("BonusRegeneration");
		case BonusMovePoints : return tr("BonusMovePoints");
		case RestrictionFighter : return tr("RestrictionFighter");
		case RestrictionRanger : return tr("RestrictionRanger");;
		case RestrictionMage : return tr("RestrictionMage");
		case RestrictionDruid : return tr("RestrictionDruid");
		case Value : return tr("Value");
	}

	return QVariant();
}

QVariant ItemModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid() || (role != Qt::DisplayRole))
		return QVariant();
	
	const Item * item = items[index.row()];
	switch (index.column()) {
		//case Uid : return item->ID(); break;
		case Name : return item->name(); break;
		case Type : return toUnderlying(item->type()); break;
// 		case BonusHitPoints : return item->statsModifiers().battleStats_.healthMax_; break;
// 		case BonusDefence : return item->statsModifiers().battleStats_.defence_; break;
// 		case BonusPerception : return item->statsModifiers().battleStats_.perception_; break;
// 		case BonusMeleeMin : return item->statsModifiers().battleStats_.attacks_[AttackType::meele].first; break;
// 		case BonusMeleeRng : return item->statsModifiers().battleStats_.attacks_[AttackType::meele].second; break;
// 		case BonusRangedMin : return item->statsModifiers().battleStats_.attacks_[AttackType::range].first; break;
// 		case BonusRangedRng : return item->statsModifiers().battleStats_.attacks_[AttackType::range].second; break;
// 		case BonusMagicalMin : return item->statsModifiers().battleStats_.attacks_[AttackType::magical].first; break;
// 		case BonusMagicalRng : return item->statsModifiers().battleStats_.attacks_[AttackType::magical].second; break;
// 		case BonusRegeneration : return item->statsModifiers().regeneration_; break;
// 		case BonusMovePoints : return item->statsModifiers().movePoints_; break;
// 		case RestrictionFighter : return item->restrictions()[PlayerClass::fighter]; break;
// 		case RestrictionRanger : return item->restrictions()[PlayerClass::ranger]; break;
// 		case RestrictionMage : return item->restrictions()[PlayerClass::mage]; break;
// 		case RestrictionDruid : return item->restrictions()[PlayerClass::druid]; break;
		case Value : return item->value(); break;
	}
	
	return QVariant();
}

bool ItemModel::insertRows(int row, int count, const QModelIndex &)
{
	beginInsertRows(QModelIndex(), row, row + count - 1);
	for (int i = 0; i < count; ++i) {
		Item * item = new Item(//serial_.next(),
									  "Default",
								     //CharacterStats(),
									  Item::Type::OneHeanded,
								     //QMap <Player::Class, bool>(),
									  i,
									  Item::Quality::Good);
		items.insert(row, item);
	}
	endInsertRows();

	return true;
}

bool ItemModel::removeRows(int row, int count, const QModelIndex &)
{
	beginRemoveRows(QModelIndex(), row, row + count - 1);
	items.remove(row, count);
	endRemoveRows();

	return true;
}
