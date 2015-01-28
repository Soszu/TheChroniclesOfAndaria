#include "Editor/Editors/ItemsEditor.h"

#include "Core/Containers/Bases/ItemBase.h"
#include "Core/Containers/Models/ItemModel.h"
#include "Editor/CustomWidgets/EffectsListEdit.h"
#include "Editor/CustomWidgets/EnumEdit.h"
#include "Editor/Shortcuts.h"
#include "Editor/Strings.h"

ItemsEditor::ItemsEditor(ItemModel *itemModel, QWidget *parent)
: QWidget(parent),
  itemModel_(itemModel),
  itemMapper_(new QDataWidgetMapper(this))
{
	initEditPart();
	initViewPart();
	initLayout();
	initMapper();
}

void ItemsEditor::clear()
{
	itemModel_->reset();
}

void ItemsEditor::loadFromStream(QDataStream& in)
{
	in >> *itemModel_;
}

void ItemsEditor::saveToStream(QDataStream& out) const
{
	out << *itemModel_;
}

bool ItemsEditor::isChanged() const
{
	return (itemModel_->isChanged());
}

void ItemsEditor::modelSaved()
{
	itemModel_->setChanged(false);
}

void ItemsEditor::initEditPart()
{
	nameEdit_ = new QLineEdit;

	typeEdit_ = new EnumEdit;
	for (auto &type : ItemBase::TypeLabels.leftKeys())
		typeEdit_->addItem(ItemBase::TypeLabels[type], QVariant::fromValue(type));

	qualityEdit_ = new EnumEdit;
	for (auto &quality : ItemBase::QualityLabels.leftKeys())
		qualityEdit_->addItem(ItemBase::QualityLabels[quality], QVariant::fromValue(quality));

	priceEdit_ = new QSpinBox;
	priceEdit_->setFixedWidth(SpinBoxWidth);

	effectsEdit_ = new EffectsListEdit;

	editLayout_ = new QFormLayout;
	editLayout_->addRow(Labels::Item::Name,      nameEdit_);
	editLayout_->addRow(Labels::Item::Type,      typeEdit_);
	editLayout_->addRow(Labels::Item::Quality,   qualityEdit_);
	editLayout_->addRow(Labels::Item::Price,     priceEdit_);
	editLayout_->addRow(Labels::Item::Effects,   effectsEdit_);

	editLayout_->setRowWrapPolicy(QFormLayout::DontWrapRows);
// 	editLayout_->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
// 	editLayout_>setFormAlignment(Qt::AlignHCenter | Qt::AlignTop);
	editLayout_->setLabelAlignment(Qt::AlignLeft);
}

void ItemsEditor::initLayout()
{
	QHBoxLayout *mainLayout = new QHBoxLayout;

	mainLayout->addLayout(viewLayout_);
	mainLayout->addLayout(editLayout_);

	setLayout(mainLayout);
}

void ItemsEditor::initMapper()
{
	itemMapper_->setModel(itemModel_);
	itemMapper_->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

	itemMapper_->addMapping(nameEdit_,    ItemModel::Name);
	itemMapper_->addMapping(typeEdit_,    ItemModel::Type);
	itemMapper_->addMapping(qualityEdit_, ItemModel::Quality);
	itemMapper_->addMapping(priceEdit_,   ItemModel::Price);
	itemMapper_->addMapping(effectsEdit_, ItemModel::Effects);

	connect(itemsList_->selectionModel(), &QItemSelectionModel::currentRowChanged, itemMapper_, &QDataWidgetMapper::setCurrentModelIndex);
}

void ItemsEditor::initViewPart()
{
	addItemButton_ = new QPushButton(Editor::Labels::Add);
	addItemButton_->setShortcut(Editor::Shortcuts::Add);
	connect(addItemButton_, &QPushButton::clicked, this, &ItemsEditor::addItem);

	removeItemButton_ = new QPushButton(Editor::Labels::Remove);
	removeItemButton_->setShortcut(Editor::Shortcuts::Remove);
	connect(removeItemButton_, &QPushButton::clicked, this, &ItemsEditor::removeItem);

	QHBoxLayout *buttonsLayout = new QHBoxLayout;
	buttonsLayout->addWidget(addItemButton_);
	buttonsLayout->addWidget(removeItemButton_);
	buttonsLayout->addStretch();

	itemsList_ = new QListView;
	itemsList_->setModel(itemModel_);
	itemsList_->setModelColumn(ItemModel::Name);
	itemsList_->setSelectionMode(QAbstractItemView::SingleSelection);

	viewLayout_ = new QVBoxLayout;
	viewLayout_->addLayout(buttonsLayout);
	viewLayout_->addWidget(itemsList_);
}

void ItemsEditor::addItem()
{
	itemModel_->insertRows(itemModel_->rowCount(), 1);
}

void ItemsEditor::removeItem()
{
	QModelIndex selected = itemsList_->selectionModel()->currentIndex();
	if (!selected.isValid())
		return;

	itemModel_->removeRows(selected.row(), 1);
}
