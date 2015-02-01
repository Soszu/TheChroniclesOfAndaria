#include "Editor/Editors/EnemiesEditor.h"

#include "Core/Containers/Models/EnemyModel.h"
#include "Core/Enums.hpp"
#include "Editor/CustomWidgets/EffectsListEdit.h"
#include "Editor/CustomWidgets/EnumEdit.h"
#include "Editor/CustomWidgets/PrizeEdit.hpp"
#include "Editor/Strings.h"
#include "Editor/Shortcuts.h"


EnemiesEditor::EnemiesEditor(EnemyModel *enemyModel, QWidget *parent)
: QWidget(parent),
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
	enemyMapper_->setModel(enemyModel_);
	enemyMapper_->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

	enemyMapper_->addMapping(nameEdit_,          EnemyModel::Name);
	enemyMapper_->addMapping(imageNameEdit_,     EnemyModel::ImageName);
	enemyMapper_->addMapping(levelEdit_,         EnemyModel::Level);
	enemyMapper_->addMapping(defaultAttackEdit_, EnemyModel::DefaultAttack);
	enemyMapper_->addMapping(baseStatsEdit_,     EnemyModel::BaseStats);
	enemyMapper_->addMapping(prizeEdit_,         EnemyModel::WinningPrize);

	connect(enemiesList_->selectionModel(), &QItemSelectionModel::currentRowChanged, enemyMapper_, &QDataWidgetMapper::setCurrentModelIndex);
}

void EnemiesEditor::initViewPart()
{
	addEnemyButton_ = new QPushButton(Editor::Labels::Add);
	addEnemyButton_->setShortcut(Editor::Shortcuts::Add);
	connect(addEnemyButton_, &QPushButton::clicked, this, &EnemiesEditor::addEnemy);

	removeEnemyButton_ = new QPushButton(Editor::Labels::Remove);
	removeEnemyButton_->setShortcut(Editor::Shortcuts::Remove);
	connect(removeEnemyButton_, &QPushButton::clicked, this, &EnemiesEditor::removeEnemy);

	QHBoxLayout *buttonsLayout = new QHBoxLayout;
	buttonsLayout->addWidget(new QLabel(Editor::Titles::Enemies));
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(addEnemyButton_);
	buttonsLayout->addWidget(removeEnemyButton_);

	enemiesList_ = new QListView;
	enemiesList_->setModel(enemyModel_);
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
