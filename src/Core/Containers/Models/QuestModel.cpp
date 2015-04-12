/*
Copyright (C) 2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
This file is part of The Chronicles Of Andaria Project.

	The Chronicles of Andaria Project is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	The Chronicles of Andaria Project is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with The Chronicles Of Andaria.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "Core/Containers/Models/QuestModel.hpp"

#include "Core/Containers/Bases/QuestBase.hpp"
#include "Core/Strings.hpp"
#include "Core/Enums.hpp"

QuestModel::QuestModel(QObject *parent) :
	QAbstractTableModel(parent),
	changed_(false)
{
	auto modelChanged = [this]{
		this->changed_ = true;
	};

	connect(this, &QAbstractTableModel::dataChanged,  modelChanged);
	connect(this, &QAbstractTableModel::rowsInserted, modelChanged);
	connect(this, &QAbstractTableModel::rowsMoved,    modelChanged);
	connect(this, &QAbstractTableModel::rowsRemoved,  modelChanged);
}

QuestModel::~QuestModel()
{
	qDeleteAll(quests_);
}

int QuestModel::columnCount(const QModelIndex& index) const
{
	if (index.isValid())
		return 0;
	return ColumnCount;
}

QVariant QuestModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role == Qt::DisplayRole || role == Qt::EditRole) {
		const QuestBase *quest = quests_[index.row()];
		switch (index.column()) {
			case Title:            return quest->title();
			case Description:      return quest->description();
			case Fraction:         return QVariant::fromValue(quest->fraction());
			case Level:            return QVariant::fromValue(quest->level());
			case QuestDifficulty:  return QVariant::fromValue(quest->difficulty());
			case IsReturnRequired: return quest->isReturnRequired();
			case CanBeDrawn:       return quest->canBeDrawn();
			case FollowUp:         return QVariant::fromValue(quest->followUp());
			case Objectives:       return QVariant::fromValue(quest->objectives());
			case Reward:           return QVariant::fromValue(quest->reward());
		}
	}

	return QVariant();
}

bool QuestModel::empty() const
{
	return quests_.empty();
}

Qt::ItemFlags QuestModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;
	return Qt::ItemIsEnabled | Qt::ItemNeverHasChildren | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

bool QuestModel::hasQuest(const QString &title) const
{
	return quest(title) != nullptr;
}

const QuestBase * QuestModel::questInRow(int row) const
{
	return quests_.value(row, nullptr);
}

const QuestBase * QuestModel::quest(UID uid) const
{
	return uidToQuest_.value(uid, nullptr);
}

const QuestBase * QuestModel::quest(const QModelIndex &index) const
{
	return quests_.value(index.row(), nullptr);
}

const QuestBase * QuestModel::quest(const QString &title) const
{
	for (const QuestBase * quest : quests_)
		if (quest->title() == title)
			return quest;

		return nullptr;
}

const QList <QuestBase *> & QuestModel::quests() const
{
	return quests_;
}

bool QuestModel::isChanged() const
{
	return changed_;
}

int QuestModel::rowCount(const QModelIndex &parent) const
{
	return quests_.count();
}

QDataStream &QuestModel::toDataStream(QDataStream &out) const
{
	out << serial_ << static_cast<UID>(quests_.count());
	for (const QuestBase *quest : quests_)
		out << *quest;
	return out;
}

void QuestModel::addNewQuest(){
	insertRows(quests_.count(), 1);
}

QDataStream &QuestModel::fromDataStream(QDataStream &in)
{
	beginResetModel();
	qDeleteAll(quests_);
	quests_.clear();
	uidToQuest_.clear();

	UID count;
	in >> serial_ >> count;
	for (UID i = 0; i < count; ++i) {
		QuestBase *quest = new QuestBase;
		in >> *quest;
		addQuest(i, quest);
	}
	endResetModel();

	return in;
}

bool QuestModel::insertRows(int row, int count, const QModelIndex &parent)
{
	int nameSuffix = 0;
	beginInsertRows(QModelIndex(), row, row + count - 1);
	for (int i = 0; i < count; ++i) {
		QString questName;
		do {
			++nameSuffix;
			questName = QString("%1 %2").arg(Labels::Quest::DefaultName).arg(nameSuffix);
		} while (hasQuest(questName));

		quests_.insert(row + i, new QuestBase(serial_.next(), questName));
	}
	endInsertRows();

	return true;
}

void QuestModel::removeQuest(UID uid)
{
	for (int i = 0; i < quests_.count(); ++i) {
		if (quests_[i]->uid() == uid) {
			beginRemoveRows(QModelIndex(), i, i);
			delete quests_.takeAt(i);
			endRemoveRows();
			uidToQuest_.remove(uid);
			return;
		}
	}
}

bool QuestModel::removeRows(int row, int count, const QModelIndex &parent)
{
	beginRemoveRows(QModelIndex(), row, row + count - 1);
	for (int i = 0; i < count; ++i)
		removeQuestFromRow(row);
	endRemoveRows();

	return true;
}

void QuestModel::reset()
{
	beginResetModel();
	removeRows(0, rowCount());
	serial_.reset();
	endResetModel();
}

void QuestModel::setChanged(bool changed)
{
	changed_ = changed;
}

bool QuestModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (!index.isValid() || role != Qt::EditRole)
		return false;

	QuestBase *quest = quests_[index.row()];
	switch (index.column()) {
		case Title:            quest->setTitle(value.toString()); break;
		case Description:      quest->setDescription(value.toString()); break;
		case Fraction:         quest->setFraction(value.value<Kingdom>()); break;
		case Level:            quest->setLevel(value.toInt()); break;
		case QuestDifficulty:  quest->setDifficulty(value.value<Difficulty>()); break;
		case IsReturnRequired: quest->setIsReturnRequired(value.toBool()); break;
		case CanBeDrawn:       quest->setCanBeDrawn(value.toBool()); break;
		case FollowUp:         quest->setFollowUp(value.value<UID>()); break;
		case Objectives:       quest->setObjectives(value.value<QList<Objective>>()); break;
		case Reward:           quest->setReward(value.value<Prize>()); break;
	}

	emit dataChanged(index, index);

	return true;
}

void QuestModel::addQuestBase(QuestBase* quest)
{
	beginResetModel();

	addQuest(rowCount(), quest);

	endResetModel();
}

void QuestModel::addQuest(int row, QuestBase* quest)
{
	quests_.insert(row, quest);
	uidToQuest_[quest->uid()] = quest;
}

void QuestModel::removeQuestFromRow(int row)
{
	uidToQuest_.remove(quests_[row]->uid());
	delete quests_.takeAt(row);
}

QDataStream & operator<<(QDataStream &out, const QuestModel &model)
{
	return model.toDataStream(out);
}

QDataStream & operator>>(QDataStream &in, QuestModel &model)
{
	return model.fromDataStream(in);
}
