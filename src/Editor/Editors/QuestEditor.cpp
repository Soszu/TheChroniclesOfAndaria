/*
Copyright (C) 2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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
#include "Editor/Editors/QuestEditor.hpp"

#include "Core/Containers/Models/QuestModel.hpp"
#include "Core/Containers/Bases/QuestBase.hpp"
#include "Core/Enums.hpp"
#include "Core/Strings.hpp"
#include "Editor/CustomWidgets/ObjectivesEdit.hpp"
#include "Editor/CustomWidgets/EffectsListEdit.hpp"
#include "Editor/CustomWidgets/EnumEdit.hpp"
#include "Editor/CustomWidgets/PrizeEdit.hpp"
#include "Editor/Shortcuts.hpp"

QuestEditor::QuestEditor(QuestModel * questModel, QWidget * parent) :
	QWidget(parent),
	questModel_(questModel),
	questMapper_(new QDataWidgetMapper(this))
{
	initEditPart();
	initViewPart();
	initLayout();
	initMapper();
}

void QuestEditor::clear()
{
	questModel_->reset();
}

void QuestEditor::loadFromStream(QDataStream & in)
{
	in >> *questModel_;
}

void QuestEditor::saveToStream(QDataStream & out) const
{
	out << *questModel_;
}

bool QuestEditor::isChanged() const
{
	return (questModel_->isChanged());
}

void QuestEditor::modelSaved()
{
	questModel_->setChanged(false);
}

void QuestEditor::initEditPart()
{
	titleEdit_ = new QLineEdit;

	descriptionEdit_ = new QPlainTextEdit;

	fractionEdit_ = new EnumEdit;
	fractionEdit_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	for (auto & kingdom : KingdomLabels.leftKeys())
		fractionEdit_->addItem(KingdomLabels[kingdom], QVariant::fromValue(kingdom));

	levelEdit_ = new QSpinBox;
	levelEdit_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	difficultyEdit_ = new EnumEdit;
	difficultyEdit_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	for (auto & level : DifficultyLabels.leftKeys())
		difficultyEdit_->addItem(DifficultyLabels[level], QVariant::fromValue(level));

	isReturnRequiredEdit_ = new QCheckBox;
	canBeDrawnEdit_ = new QCheckBox;

	objectivesEdit_ = new ObjectivesEdit;

	followUpEdit_ = new EnumEdit;
	followUpEdit_->setEditable(true);

	rewardEdit_ = new PrizeEdit;

	editLayout_ = new QFormLayout;
	editLayout_->addRow(Labels::Quest::Title,            titleEdit_);
	editLayout_->addRow(Labels::Quest::Description,      descriptionEdit_);
	editLayout_->addRow(Labels::Quest::Fraction,         fractionEdit_);
	editLayout_->addRow(Labels::Quest::Level,            levelEdit_);
	editLayout_->addRow(Labels::Quest::Difficulty,       difficultyEdit_);
	editLayout_->addRow(Labels::Quest::IsReturnRequired, isReturnRequiredEdit_);
	editLayout_->addRow(Labels::Quest::CanBeDrawn,       canBeDrawnEdit_);
	editLayout_->addRow(Labels::Quest::Objectives,       objectivesEdit_);
	editLayout_->addRow(Labels::Quest::FollowUp,         followUpEdit_);
	editLayout_->addRow(Labels::Quest::Reward,           rewardEdit_);

	editLayout_->setRowWrapPolicy(QFormLayout::DontWrapRows);
// 	editLayout_->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
// 	editLayout_->setFormAlignment(Qt::AlignHCenter | Qt::AlignTop);
	editLayout_->setLabelAlignment(Qt::AlignLeft);
}

void QuestEditor::initLayout()
{
	QHBoxLayout * mainLayout = new QHBoxLayout;

	mainLayout->addLayout(viewLayout_);
	mainLayout->addLayout(editLayout_);

	setLayout(mainLayout);
}

void QuestEditor::initMapper()
{
	questMapper_->setModel(questModel_);
	questMapper_->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

	questMapper_->addMapping(titleEdit_,            QuestModel::Title);
	questMapper_->addMapping(descriptionEdit_,      QuestModel::Description);
	questMapper_->addMapping(fractionEdit_,         QuestModel::Fraction);
	questMapper_->addMapping(difficultyEdit_,       QuestModel::QuestDifficulty);
	questMapper_->addMapping(levelEdit_,            QuestModel::Level);
	questMapper_->addMapping(isReturnRequiredEdit_, QuestModel::IsReturnRequired, "checked");
	questMapper_->addMapping(canBeDrawnEdit_,       QuestModel::CanBeDrawn,       "checked");
	questMapper_->addMapping(objectivesEdit_,       QuestModel::Objectives);
	questMapper_->addMapping(followUpEdit_,         QuestModel::FollowUp);
	questMapper_->addMapping(rewardEdit_,           QuestModel::Reward);

	connect(objectivesEdit_, &ObjectivesEdit::contentChanged,
	        questMapper_, &QDataWidgetMapper::submit);

	connect(questsList_->selectionModel(), &QItemSelectionModel::currentRowChanged,
	        questMapper_, &QDataWidgetMapper::setCurrentModelIndex);
}

void QuestEditor::initViewPart()
{
	QPushButton * addQuestButton = new QPushButton(tr("Add"));
	addQuestButton->setShortcut(Editor::Shortcuts::Add);
	connect(addQuestButton, & QPushButton::clicked, this, &QuestEditor::addQuest);

	QPushButton *removeQuestButton = new QPushButton(tr("Remove"));
	removeQuestButton->setShortcut(Editor::Shortcuts::Remove);
	connect(removeQuestButton, &QPushButton::clicked, this, &QuestEditor::removeQuest);

	QHBoxLayout * buttonsLayout = new QHBoxLayout;
	buttonsLayout->addWidget(new QLabel(tr("Quests")));
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(addQuestButton);
	buttonsLayout->addWidget(removeQuestButton);

	questsList_ = new QListView;
	questsList_->setModel(questModel_);
	questsList_->setModelColumn(QuestModel::Title);
	questsList_->setSelectionMode(QAbstractItemView::SingleSelection);

	viewLayout_ = new QVBoxLayout;
	viewLayout_->addLayout(buttonsLayout);
	viewLayout_->addWidget(questsList_);
}

void QuestEditor::updateFollowUps()
{
	//TODO if removed check for invalid uids

	followUpEdit_->clear();
	for (auto & quest : questModel_->quests())
		followUpEdit_->addItem(quest->title(), quest->uid());
}

void QuestEditor::addQuest()
{
	questModel_->insertRows(questModel_->rowCount(), 1);
	updateFollowUps();
}

void QuestEditor::removeQuest()
{
	QModelIndex selected = questsList_->selectionModel()->currentIndex();
	if (!selected.isValid())
		return;

	questModel_->removeRows(selected.row(), 1);
	updateFollowUps();
}
