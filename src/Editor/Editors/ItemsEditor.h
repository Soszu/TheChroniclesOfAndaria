#pragma once

#include <QtWidgets>

class ItemModel;
class EffectsListEdit;
class EnumEdit;

class ItemsEditor : public QWidget {
	Q_OBJECT

public:
	ItemsEditor(ItemModel *itemModel, QWidget *parent = nullptr);
	void clear();
	void loadFromStream(QDataStream& in);
	void saveToStream(QDataStream& out) const;
	bool isChanged() const;

public slots:
	void modelSaved();

private:
	static const int SpinBoxWidth = 50;

	void initEditPart();
	void initViewPart();
	void initLayout();
	void initMapper();

	QFormLayout *editLayout_;
	QVBoxLayout *viewLayout_;

	ItemModel *itemModel_;
	QDataWidgetMapper *itemMapper_;

	//--- Item name ---
	QLineEdit *nameEdit_;
	EnumEdit *typeEdit_;
	EnumEdit *qualityEdit_;
	QSpinBox *priceEdit_;
	EffectsListEdit *effectsEdit_;

	//--- Item list---
	QListView *itemsList_;
	QPushButton *addItemButton_;
	QPushButton *removeItemButton_;

private slots:
	void addItem();
	void removeItem();
};
