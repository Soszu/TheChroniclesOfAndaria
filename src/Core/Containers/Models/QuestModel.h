#pragma once

#include <QtCore>
#include "Core/Utils/Serial.hpp"

class QuestBase;

class QuestModel : public QAbstractTableModel {
public:
	static const int Title            = 0;
	static const int Description      = 1;
	static const int Fraction         = 2;
	static const int Level            = 3;
	static const int IsReturnRequired = 4;
	static const int CanBeDrawn       = 5;
	static const int FollowUp         = 6;
	static const int Objectives       = 7;
	static const int Reward           = 8;
	static const int ColumnCount      = 9;

	explicit QuestModel(QObject *parent = nullptr);
	QuestModel(const QuestModel &) = delete;
	QuestModel(QuestModel &&) = delete;
	void operator=(const QuestModel &) = delete;
	void operator=(QuestModel &&) = delete;
	~QuestModel();

	int columnCount(const QModelIndex &index = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;
	bool empty() const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	bool hasQuest(const QString &name) const;
	const QuestBase * questInRow(int row) const;
	const QuestBase * quest(UID uid) const;
	const QuestBase * quest(const QModelIndex &index) const;
	const QuestBase * quest(const QString &name) const;
	const QList <QuestBase *> & quests() const;
	bool isChanged() const;
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QDataStream & toDataStream(QDataStream &out) const;

	void addNewQuest();
	QDataStream & fromDataStream(QDataStream &in);
	bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
	void removeQuest(UID uid);
	bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
	void reset();
	void setChanged(bool changed);
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

	//TMP for migration from parsers
	void addQuestBase(QuestBase *quest);
private:
	void addQuest(int row, QuestBase *quest);
	void removeQuestFromRow(int row);

	bool changed_;
	QList <QuestBase *> quests_;
	Serial serial_;
	QHash <UID, QuestBase *> uidToQuest_;
};
QDataStream & operator<<(QDataStream &out, const QuestModel &model);
QDataStream & operator>>(QDataStream &in, QuestModel &model);