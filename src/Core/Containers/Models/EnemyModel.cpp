#include "Core/Containers/Models/EnemyModel.h"

#include "Core/Containers/Enemy.h"
#include "Core/Containers/Bases/EnemyBase.h"
#include "Core/Containers/Prize.h"

EnemyModel::EnemyModel(QObject *parent) : QAbstractTableModel(parent), changed_(false)
{
	auto modelChanged = [this]{
		this->changed_ = true;
	};

	connect(this, &QAbstractTableModel::dataChanged,  modelChanged);
	connect(this, &QAbstractTableModel::rowsInserted, modelChanged);
	connect(this, &QAbstractTableModel::rowsMoved,    modelChanged);
	connect(this, &QAbstractTableModel::rowsRemoved,  modelChanged);
}

EnemyModel::~EnemyModel()
{
	qDeleteAll(enemies_);
}

int EnemyModel::columnCount(const QModelIndex& index) const
{
	if (index.isValid())
		return 0;
	return ColumnCount;
}

QVariant EnemyModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role == Qt::DisplayRole || role == Qt::EditRole) {
		const EnemyBase *enemy = enemies_[index.row()];
		switch (index.column()) {
			case Name:                return enemy->name();
			case ImageName:           return enemy->imageName();
			case Level:               return enemy->level();
			case DefaultAttack:       return QVariant::fromValue(enemy->defaultAttack());
			case BaseStats:           return QVariant::fromValue(enemy->baseStats());
			case WinningPrize:               return QVariant::fromValue(enemy->prize());
		}
	}
	return QVariant();
}

bool EnemyModel::empty() const
{
	return enemies_.empty();
}

Qt::ItemFlags EnemyModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;
	return Qt::ItemIsEnabled | Qt::ItemNeverHasChildren | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

bool EnemyModel::hasEnemy(const QString &name) const
{
	return enemy(name) != nullptr;
}

const EnemyBase * EnemyModel::enemyInRow(int row) const
{
	return enemies_.value(row, nullptr);
}

const EnemyBase * EnemyModel::enemy(UID uid) const
{
	return uidToEnemy_.value(uid, nullptr);
}

const EnemyBase * EnemyModel::enemy(const QModelIndex &index) const
{
	return enemies_.value(index.row(), nullptr);
}

const EnemyBase * EnemyModel::enemy(const QString &name) const
{
	for (const EnemyBase * enemy : enemies_)
		if (enemy->name() == name)
			return enemy;

		return nullptr;
}

const QList <EnemyBase *> & EnemyModel::enemies() const
{
	return enemies_;
}

bool EnemyModel::isChanged() const
{
	return changed_;
}

int EnemyModel::rowCount(const QModelIndex &parent) const
{
	return enemies_.count();
}

QDataStream &EnemyModel::toDataStream(QDataStream &out) const
{
	out << serial_ << static_cast<UID>(enemies_.count());
	for (const EnemyBase *enemy : enemies_)
		out << *enemy;
	return out;
}

void EnemyModel::addNewEnemy(){
	insertRows(enemies_.count(), 1);
}

QDataStream &EnemyModel::fromDataStream(QDataStream &in)
{
	beginResetModel();
	qDeleteAll(enemies_);
	enemies_.clear();
	uidToEnemy_.clear();

	UID count;
	in >> serial_ >> count;
	for (UID i = 0; i < count; ++i) {
		EnemyBase *enemy = new EnemyBase;
		in >> *enemy;
		addEnemy(i, enemy);
	}
	endResetModel();

	return in;
}

bool EnemyModel::insertRows(int row, int count, const QModelIndex &parent)
{
	int nameSuffix = 0;
	beginInsertRows(QModelIndex(), row, row + count - 1);
	for (int i = 0; i < count; ++i) {
		QString enemyName;
		do {
			++nameSuffix;
			enemyName = QString("%1 %2").arg(Labels::Enemy::DefaultName).arg(nameSuffix);
		} while (hasEnemy(enemyName));

		enemies_.insert(row + i, new EnemyBase(serial_.next(), enemyName));
	}
	endInsertRows();

	return true;
}

void EnemyModel::removeEnemy(UID uid)
{
	for (int i = 0; i < enemies_.count(); ++i) {
		if (enemies_[i]->uid() == uid) {
			beginRemoveRows(QModelIndex(), i, i);
			delete enemies_.takeAt(i);
			endRemoveRows();
			uidToEnemy_.remove(uid);
			return;
		}
	}
}

bool EnemyModel::removeRows(int row, int count, const QModelIndex &parent)
{
	beginRemoveRows(QModelIndex(), row, row + count - 1);
	for (int i = 0; i < count; ++i)
		removeEnemyFromRow(row);
	endRemoveRows();

	return true;
}

void EnemyModel::reset()
{
	beginResetModel();
	removeRows(0, rowCount());
	serial_.reset();
	endResetModel();
}

void EnemyModel::setChanged(bool changed)
{
	changed_ = changed;
}

bool EnemyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (!index.isValid() || role != Qt::EditRole)
		return false;

	EnemyBase *enemy = enemies_[index.row()];
	switch (index.column()) {
		case Name:                enemy->setName(value.toString()); break;
		case ImageName:           enemy->setImageName(value.toString()); break;
		case Level:               enemy->setLevel(value.toInt()); break;
		case DefaultAttack:       enemy->setDefaultAttack(value.value<Attack>()); break;
		case BaseStats:           enemy->setBaseStats(value.value<QList <Effect> >()); break;
		case WinningPrize:               enemy->setPrize(value.value<Prize>()); break;
	}

	emit dataChanged(index, index);

	return true;
}

void EnemyModel::addEnemy(int row, EnemyBase* enemy)
{
	enemies_.insert(row, enemy);
	uidToEnemy_[enemy->uid()] = enemy;
}

void EnemyModel::removeEnemyFromRow(int row)
{
	uidToEnemy_.remove(enemies_[row]->uid());
	delete enemies_.takeAt(row);
}

QDataStream & operator<<(QDataStream &out, const EnemyModel &model)
{
	return model.toDataStream(out);
}

QDataStream & operator>>(QDataStream &in, EnemyModel &model)
{
	return model.fromDataStream(in);
}
