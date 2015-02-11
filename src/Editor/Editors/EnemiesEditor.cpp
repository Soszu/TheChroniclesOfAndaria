/*
Copyright (C) 2014-2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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
#include "Editor/Editors/EnemiesEditor.hpp"

#include "Core/Containers/Models/EnemyModel.hpp"
#include "Core/Enums.hpp"
#include "Editor/CustomWidgets/EffectsListEdit.hpp"
#include "Editor/CustomWidgets/EnumEdit.hpp"
#include "Editor/CustomWidgets/PrizeEdit.hpp"
#include "Editor/Strings.hpp"
#include "Editor/Shortcuts.hpp"


EnemiesEditor::EnemiesEditor(EnemyModel *enemyModel, QWidget *parent) :
	QWidget(parent),
	enemyModel_(enemyModel),
	enemyMapper_(new QDataWidgetMapper(this))
{
	initEditPart();
	initViewPart();
	initLayout();
	initMapper();
}

void EnemiesEditor::clear()
{
	enemyModel_->reset();
}

void EnemiesEditor::loadFromStream(QDataStream& in)
{
	in >> *enemyModel_;
}

void EnemiesEditor::saveToStream(QDataStream& out) const
{
	out << *enemyModel_;
}

bool EnemiesEditor::isChanged() const
{
	return (enemyModel_->isChanged());
}

void EnemiesEditor::modelSaved()
{
	enemyModel_->setChanged(false);
}

void EnemiesEditor::initEditPart()
{
	nameEdit_ = new QLineEdit;

	imageNameEdit_ = new QLineEdit;

	levelEdit_ = new QSpinBox;

	defaultAttackEdit_ = new EnumEdit;
	for (auto &attack : AttackLabels.leftKeys())
		defaultAttackEdit_->addItem(AttackLabels[attack], QVariant::fromValue(attack));

	baseStatsEdit_ = new EffectsListEdit;

	prizeEdit_ = new PrizeEdit;

	editLayout_ = new QFormLayout;
	editLayout_->addRow(Labels::Enemy::Name,          nameEdit_);
	editLayout_->addRow(Labels::Enemy::ImageName,     imageNameEdit_);
	editLayout_->addRow(Labels::Enemy::Level,         levelEdit_);
	editLayout_->addRow(Labels::Enemy::DefaultAttack, defaultAttackEdit_);
	editLayout_->addRow(Labels::Enemy::BaseStats,     baseStatsEdit_);
	editLayout_->addRow(Labels::Enemy::WinningPrize,  prizeEdit_);

	editLayout_->setRowWrapPolicy(QFormLayout::DontWrapRows);
	editLayout_->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
// 	editLayout_->setFormAlignment(Qt::AlignHCenter | Qt::AlignTop);
	editLayout_->setLabelAlignment(Qt::AlignLeft);
}

void EnemiesEditor::initLayout()
{
	QHBoxLayout *mainLayout = new QHBoxLayout;

	mainLayout->addLayout(viewLayout_);
	mainLayout->addLayout(editLayout_);

	setLayout(mainLayout);
}

void EnemiesEditor::initMapper()
{
	enemyMapper_->setModel(proxyModel_);
	enemyMapper_->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

	enemyMapper_->addMapping(nameEdit_,          EnemyModel::Name);
	enemyMapper_->addMapping(imageNameEdit_,     EnemyModel::ImageName);
	enemyMapper_->addMapping(levelEdit_,         EnemyModel::Level);
	enemyMapper_->addMapping(defaultAttackEdit_, EnemyModel::DefaultAttack);
	enemyMapper_->addMapping(baseStatsEdit_,     EnemyModel::BaseStats);
	enemyMapper_->addMapping(prizeEdit_,         EnemyModel::WinningPrize);

	connect(enemiesList_->selectionModel(), &QItemSelectionModel::currentRowChanged, enemyMapper_, &QDataWidgetMapper::setCurrentModelIndex);
}

void EnemiesEditor::characterTyped(const QString & text)
{
	proxyModel_->setFilterRegExp(QRegExp(text, Qt::CaseInsensitive, QRegExp::FixedString));
}

void EnemiesEditor::initViewPart()
{
	addEnemyButton_ = new QPushButton(Editor::Labels::Add);
	addEnemyButton_->setShortcut(Editor::Shortcuts::Add);
	connect(addEnemyButton_, &QPushButton::clicked, this, &EnemiesEditor::addEnemy);

	removeEnemyButton_ = new QPushButton(Editor::Labels::Remove);
	removeEnemyButton_->setShortcut(Editor::Shortcuts::Remove);
	connect(removeEnemyButton_, &QPushButton::clicked, this, &EnemiesEditor::removeEnemy);

	searchLine_ = new QLineEdit(this);
	connect(searchLine_, &QLineEdit::textChanged, this, &EnemiesEditor::characterTyped);

	QHBoxLayout *buttonsLayout = new QHBoxLayout;
	buttonsLayout->addWidget(new QLabel(Editor::Titles::Enemies));
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(searchLine_);
	buttonsLayout->addWidget(addEnemyButton_);
	buttonsLayout->addWidget(removeEnemyButton_);

	proxyModel_ = new QSortFilterProxyModel(this);
	proxyModel_->setSourceModel(enemyModel_);

	enemiesList_ = new QListView;
	enemiesList_->setModel(proxyModel_);
	enemiesList_->setModelColumn(EnemyModel::Name);
	enemiesList_->setSelectionMode(QAbstractItemView::SingleSelection);

	viewLayout_ = new QVBoxLayout;
	viewLayout_->addLayout(buttonsLayout);
	viewLayout_->addWidget(enemiesList_);
}

void EnemiesEditor::addEnemy()
{
	enemyModel_->insertRows(enemyModel_->rowCount(), 1);
}

void EnemiesEditor::removeEnemy()
{
	QModelIndex selected = enemiesList_->selectionModel()->currentIndex();
	if (!selected.isValid())
		return;

	enemyModel_->removeRows(selected.row(), 1);
}
