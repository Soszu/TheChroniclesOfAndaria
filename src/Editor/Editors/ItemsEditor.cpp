#include "Editor/Editors/ItemsEditor.h"
#include "Editor/Strings.h"
#include "Editor/Shortcuts.h"
#include "Core/Containers/Bases/ItemBase.h"

ItemsEditor::ItemsEditor(QObject *parent) : ContentEditor(Title::Items, parent)
{
	initModel();
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

void ItemsEditor::initModel()
{
	itemModel_ = new ItemModel(this);
	itemMapper_ = new QDataWidgetMapper(this);
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

	QFormLayout *baseInfoLayout = new QFormLayout;
	baseInfoLayout->addRow(Label::Item::Name, nameEdit_);
	baseInfoLayout->addRow(Label::Item::Type, typeEdit_);
	baseInfoLayout->addRow(Label::Item::Quality, qualityEdit_);
	baseInfoLayout->addRow(Label::Item::Price, priceEdit_);

	effectsEdit_ = new EffectsListEdit(Label::Item::Effects);

	editLayout_ = new QVBoxLayout;
	editLayout_->addLayout(baseInfoLayout);
	editLayout_->addWidget(effectsEdit_);

	baseInfoLayout->setRowWrapPolicy(QFormLayout::DontWrapRows);
// 	baseInfoLayout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
// 	baseInfoLayout->setFormAlignment(Qt::AlignHCenter | Qt::AlignTop);
	baseInfoLayout->setLabelAlignment(Qt::AlignLeft);
}

void ItemsEditor::initLayout()
{
	QWidget *placeholder = new QWidget;
	QHBoxLayout *mainLayout = new QHBoxLayout(placeholder);

	mainLayout->addLayout(editLayout_);
	mainLayout->addLayout(viewLayout_);

	setPlaceholder(placeholder);
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
	itemsList_ = new QListView;
	itemsList_->setModel(itemModel_);
	itemsList_->setModelColumn(ItemModel::Name);
	itemsList_->setSelectionMode(QAbstractItemView::SingleSelection);

	addItemButton_ = new QPushButton(Label::Editor::Add);
	addItemButton_->setShortcut(Shortcut::Editor::Add);
	connect(addItemButton_, &QPushButton::clicked, this, &ItemsEditor::addItem);

	removeItemButton_ = new QPushButton(Label::Editor::Remove);
	removeItemButton_->setShortcut(Shortcut::Editor::Remove);
	connect(removeItemButton_, &QPushButton::clicked, this, &ItemsEditor::removeItem);

	QHBoxLayout *buttonsLayout = new QHBoxLayout;
	buttonsLayout->addWidget(addItemButton_);
	buttonsLayout->addWidget(removeItemButton_);
	buttonsLayout->addStretch();

	viewLayout_ = new QVBoxLayout;
	viewLayout_->addWidget(itemsList_);
	viewLayout_->addLayout(buttonsLayout);
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
