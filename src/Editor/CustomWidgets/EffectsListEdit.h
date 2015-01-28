#pragma once

#include <QtWidgets>

#include "Core/Containers/Effect.h"

class EffectsListEdit : public QWidget {
	Q_OBJECT
	Q_PROPERTY(QList <Effect> effects_
	           READ effects
	           WRITE setEffects
	           RESET reset
	           NOTIFY effectsChanged
	           USER true)

public:
	EffectsListEdit(QWidget *parent = nullptr);

	QList <Effect> effects() const;

	void reset();
	void setEffects(const QList <Effect> &effects);

private:
	void initButtons();
	void initEdits();
	void initList();
	void initLayout();
	void simulateFocusLoss();

	QList <Effect> effects_;
	QStringListModel *effectsModel_;

	QListView *listView_;
	QComboBox *typeEdit_;
	QSpinBox *valueEdit_;
	QSpinBox *durationEdit_;

	QPushButton *addEffectButton_;
	QPushButton *removeEffectButton_;

private slots:
	void addEffect();
	void removeEffect();
	void updateEdits(const QModelIndex &index);

	void updateType(QString text);
	void updateValue(int x);
	void updateDuration(int x);

signals:
	void effectsChanged(QList <Effect> effects_);
};
