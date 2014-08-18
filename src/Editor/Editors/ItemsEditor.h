#pragma once

#include <QtWidgets>
#include "Core/Containers/Models/ItemModel.h"
#include "Editor/Editors/ContentEditor.h"
#include "Editor/CustomWidgets/EffectsListEdit.h"
#include "Editor/CustomWidgets/EnumEdit.h"

class ItemsEditor : public ContentEditor {
	Q_OBJECT
public:
	ItemsEditor(QObject *parent = nullptr);
	void clear();
	void loadFromStream(QDataStream& in);
	void saveToStream(QDataStream& out) const;
	bool isChanged() const;

public slots:
	void modelSaved();

private:
	static const int SpinBoxWidth = 50;

	void initModels();
	void initEditPart();
	void initViewPart();
	void initLayout();
	void initMapper();

	QVBoxLayout *editLayout_;
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
