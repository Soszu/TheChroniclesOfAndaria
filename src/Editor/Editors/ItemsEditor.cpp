/*
Copyright (C) 2014-2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
Copyright (C) 2015 by Bartosz Szreder <szreder [at] mimuw [dot] edu [dot] pl>
Copyright (C) 2015 by Marcin Parafiniuk <jessie [dot] inferno [at] gmail [dot] com>
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
#include "Editor/Editors/ItemsEditor.hpp"

#include "Core/Containers/Bases/ItemBase.hpp"
#include "Core/Containers/Models/ItemModel.hpp"
#include "Editor/CustomWidgets/EffectsListEdit.hpp"
#include "Editor/CustomWidgets/EnumEdit.hpp"
#include "Editor/Shortcuts.hpp"
#include "Editor/Strings.hpp"

ItemsEditor::ItemsEditor(ItemModel *itemModel, QWidget *parent) :
	QWidget(parent),
	itemModel_(itemModel),
	itemMapper_(new QDataWidgetMapper(this))
{
	initLayout();
	initMapper();
	setEditWidgetsEnabled(false);
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
	return itemModel_->isChanged();
}

void ItemsEditor::modelSaved()
{
	itemModel_->setChanged(false);
}

QLayout * ItemsEditor::createEditPart()
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

	canBeDrawnEdit_ = new QCheckBox;

	effectsEdit_ = new EffectsListEdit;
	connect(itemModel_, &QAbstractItemModel::modelReset, effectsEdit_, &EffectsListEdit::reset);

	QFormLayout *editLayout = new QFormLayout;
	editLayout->addRow(Labels::Item::Name,       nameEdit_);
	editLayout->addRow(Labels::Item::Type,       typeEdit_);
	editLayout->addRow(Labels::Item::Quality,    qualityEdit_);
	editLayout->addRow(Labels::Item::Price,      priceEdit_);
	editLayout->addRow(Labels::Item::CanBeDrawn, canBeDrawnEdit_);
	editLayout->addRow(Labels::Item::Effects,    effectsEdit_);

	editLayout->setRowWrapPolicy(QFormLayout::DontWrapRows);
// 	editLayout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
// 	editLayout->setFormAlignment(Qt::AlignHCenter | Qt::AlignTop);
	editLayout->setLabelAlignment(Qt::AlignLeft);

	return editLayout;
}

QLayout * ItemsEditor::createViewPart()
{
	addItemButton_ = new QPushButton(Editor::Labels::Add);
	addItemButton_->setShortcut(Editor::Shortcuts::Add);
	connect(addItemButton_, &QPushButton::clicked, this, &ItemsEditor::addItem);

	removeItemButton_ = new QPushButton(Editor::Labels::Remove);
	removeItemButton_->setShortcut(Editor::Shortcuts::Remove);
	connect(removeItemButton_, &QPushButton::clicked, this, &ItemsEditor::removeItem);

	searchLine_ = new QLineEdit(this);
	connect(searchLine_, &QLineEdit::textChanged, this, &ItemsEditor::characterTyped);

	QHBoxLayout *buttonsLayout = new QHBoxLayout;
	buttonsLayout->addWidget(new QLabel(Editor::Titles::Items));
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(searchLine_);
	buttonsLayout->addWidget(addItemButton_);
	buttonsLayout->addWidget(removeItemButton_);

	itemsList_ = new QListView;
	itemsList_->setModel(itemModel_);
	itemsList_->setModelColumn(ItemModel::Name);
	itemsList_->setSelectionMode(QAbstractItemView::SingleSelection);

	proxyModel_ = new QSortFilterProxyModel(this);
	proxyModel_->setSourceModel(itemModel_);

	QVBoxLayout *viewLayout = new QVBoxLayout;
	viewLayout->addLayout(buttonsLayout);
	viewLayout->addWidget(itemsList_);

	return viewLayout;
}

void ItemsEditor::initLayout()
{
	QHBoxLayout *mainLayout = new QHBoxLayout;

	mainLayout->addLayout(createViewPart());
	mainLayout->addLayout(createEditPart());

	setLayout(mainLayout);
}

void ItemsEditor::initMapper()
{
	itemMapper_->setModel(proxyModel_);
	itemMapper_->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

	itemMapper_->addMapping(nameEdit_,       ItemModel::Name);
	itemMapper_->addMapping(typeEdit_,       ItemModel::Type);
	itemMapper_->addMapping(qualityEdit_,    ItemModel::Quality);
	itemMapper_->addMapping(priceEdit_,      ItemModel::Price);
	itemMapper_->addMapping(canBeDrawnEdit_, ItemModel::CanBeDrawn);
	itemMapper_->addMapping(effectsEdit_,    ItemModel::Effects);

	connect(effectsEdit_, &EffectsListEdit::effectsChanged,
	        itemMapper_, &QDataWidgetMapper::submit);
	connect(itemsList_->selectionModel(), &QItemSelectionModel::currentRowChanged,
	        this, &ItemsEditor::rowChanged);
}

void ItemsEditor::setEditWidgetsEnabled(bool enabled)
{
	for (QWidget *widget : std::initializer_list<QWidget *>{nameEdit_, typeEdit_, qualityEdit_,
	                       priceEdit_, canBeDrawnEdit_, effectsEdit_})
		widget->setEnabled(enabled);
}

void ItemsEditor::characterTyped(const QString & text)
{
	proxyModel_->setFilterRegExp(QRegExp(text, Qt::CaseInsensitive, QRegExp::FixedString));
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

void ItemsEditor::rowChanged()
{
	const QItemSelectionModel *selection = itemsList_->selectionModel();
	setEditWidgetsEnabled(selection->hasSelection());
	if (selection->hasSelection())
		itemMapper_->setCurrentModelIndex(selection->currentIndex());
}
