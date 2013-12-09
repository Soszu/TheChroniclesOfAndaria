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
	return items_.count();
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
		case BonusHitPoints : return tr("Bonus Hit Points");
		case BonusDefence : return tr("Bonus Defence");
		case BonusPerception : return tr("Bonus Perception");
		case BonusMeleeMin : return tr("Bonus Melee Minimum Damage");
		case BonusMeleeRng : return tr("Bonus Melee Damage Range");
		case BonusRangedMin : return tr("Bonus Ranged Minimum Damage");
		case BonusRangedRng : return tr("Bonus Ranged Damage Range");
		case BonusMagicalMin : return tr("Bonus Magical Minimum Damage");
		case BonusMagicalRng : return tr("Bonus Magical Damage Range");
		case BonusRegeneration : return tr("Bonus Regeneration");
		case BonusMovePoints : return tr("Bonus Move Points");
		case RestrictionFighter : return tr("Restriction for Fighter");
		case RestrictionRanger : return tr("Restriction for Ranger");
		case RestrictionMage : return tr("Restriction for Mage");
		case RestrictionDruid : return tr("Restriction for Druid");
		case Value : return tr("Value");
	}

	return QVariant();
}

QVariant ItemModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid() || (role != Qt::DisplayRole))
		return QVariant();
	
	const Item * item = items_[index.row()];
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
									  Item::Type::OneHanded,
								     //QMap <Player::Class, bool>(),
									  1,
									  Item::Quality::Good);
		items_.insert(row, item);
	}
	endInsertRows();

	return true;
}

bool ItemModel::removeRows(int row, int count, const QModelIndex &)
{
	beginRemoveRows(QModelIndex(), row, row + count - 1);
	items_.remove(row, count);
	endRemoveRows();

	return true;
}

QDataStream & operator<<(QDataStream &out, const ItemModel &itemModel)
{
	out << itemModel.serial_ << itemModel.items_.count();
	for (const Item * item : itemModel.items_)
		out << item;
	
	return out;
}

QDataStream & operator>>(QDataStream &in, ItemModel &itemModel)
{
	int count;
	in >> itemModel.serial_ >> count;
	for (int i = 0; i < count; ++i) {
		//UID id;
		QString name;
		//CharacterStats statsModifiers;
		Item::Type type;
		//QMap <Player::Class, bool> restrictions;
		int value;
		Item::Quality quality;
		in /*>> id*/ >> name/* >> statsModifiers*/ >> toUnderlyingRef(type) 
			/*>> restrictions*/ >> value >> toUnderlyingRef(quality);
		itemModel.items_.push_back(new Item{/*id,*/ name,/*statsModifiers,*/ type, /*restrictions,*/ value, quality});
		
	}
	
	return in;
}


