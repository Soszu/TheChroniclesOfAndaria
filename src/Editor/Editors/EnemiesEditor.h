#pragma once

#include <QtWidgets>

class EnumEdit;
class PrizeEdit;
class EffectsListEdit;
class EnemyModel;

class EnemiesEditor : public QWidget {
	Q_OBJECT

public:
	EnemiesEditor(EnemyModel *enemyModel, QWidget *parent = nullptr);
	void clear();
	void loadFromStream(QDataStream& in);
	void saveToStream(QDataStream& out) const;
	bool isChanged() const;

public slots:
	void modelSaved();

private:
	void initEditPart();
	void initViewPart();
	void initLayout();
	void initMapper();

	QFormLayout *editLayout_;
	QVBoxLayout *viewLayout_;

	EnemyModel *enemyModel_;
	QDataWidgetMapper *enemyMapper_;

	//--- Edits ---
	QLineEdit *nameEdit_;
	QLineEdit *imageNameEdit_;
	EnumEdit *defaultAttackEdit_;
	QSpinBox *levelEdit_;
	EffectsListEdit *baseStatsEdit_;
	PrizeEdit *prizeEdit_;

	//--- List---
	QListView *enemiesList_;
	QPushButton *addEnemyButton_;
	QPushButton *removeEnemyButton_;

private slots:
	void addEnemy();
	void removeEnemy();
};
