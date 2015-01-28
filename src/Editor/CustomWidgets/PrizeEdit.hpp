#pragma once

#include <QtWidgets>

#include "Core/Containers/Prize.h"

class PrizeEdit : public QWidget {
	Q_OBJECT
	Q_PROPERTY(Prize prize_
	           READ prize
	           WRITE setPrize
	           RESET reset
	           NOTIFY prizeChanged
	           USER true)

public:
	PrizeEdit(QWidget *parent = nullptr);

	Prize prize() const;

	void reset();
	void setPrize(const Prize &prize);

private:
	void initWidgets();
	void initLayout();
	void simulateFocusLoss();

	Prize prize_;

	QSpinBox *experienceEdit_;
	QSpinBox *goldEdit_;
//
// 	QList <Effect> effects_;
// 	QStringListModel *effectsModel_;
//
// 	QListView *listView_;
// 	QComboBox *typeEdit_;
//
// 	QPushButton *addEffectButton_;
// 	QPushButton *removeEffectButton_;

private slots:
// 	void addEffect();
// 	void removeEffect();
// 	void updateEdits(const QModelIndex &index);
//
// 	void updateType(QString text);
	void updateExperience(int x);
	void updateGold(int x);

signals:
	void prizeChanged(Prize prize);
};
