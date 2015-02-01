#pragma once

#include <QtWidgets>

class EnumEdit;
class PrizeEdit;
class QuestModel;

class QuestEditor : public QWidget {
	Q_OBJECT

public:
	QuestEditor(QuestModel *questModel, QWidget *parent = nullptr);
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
    void updateFollowUps();

	QFormLayout *editLayout_;
	QVBoxLayout *viewLayout_;

	QuestModel *questModel_;
	QDataWidgetMapper *questMapper_;

	//--- Edits ---
	QLineEdit *titleEdit_;
	QPlainTextEdit *descriptionEdit_;
	EnumEdit *fractionEdit_;
	EnumEdit *levelEdit_;
	QCheckBox *isReturnRequiredEdit_;
	QCheckBox *canBeDrawnEdit_;
	EnumEdit *followUpEdit_;
	PrizeEdit *rewardEdit_;

	//--- List---
	QListView *questsList_;

private slots:
	void addQuest();
	void removeQuest();
};
