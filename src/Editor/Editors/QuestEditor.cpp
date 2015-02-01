#include "Editor/Editors/QuestEditor.h"

#include "Core/Containers/Models/QuestModel.h"
#include "Core/Containers/Bases/QuestBase.h"
#include "Core/Enums.hpp"
#include "Editor/CustomWidgets/EffectsListEdit.h"
#include "Editor/CustomWidgets/EnumEdit.h"
#include "Editor/CustomWidgets/PrizeEdit.hpp"
#include "Editor/Strings.h"
#include "Editor/Shortcuts.h"

QuestEditor::QuestEditor(QuestModel *questModel, QWidget *parent)
: QWidget(parent),
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

void QuestEditor::loadFromStream(QDataStream& in)
{
	in >> *questModel_;
}

void QuestEditor::saveToStream(QDataStream& out) const
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
	for (auto &kingdom : KingdomLabels.leftKeys())
		fractionEdit_->addItem(KingdomLabels[kingdom], QVariant::fromValue(kingdom));

	levelEdit_ = new EnumEdit;
	levelEdit_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	for (auto &level : QuestBase::LevelLabels.leftKeys())
		levelEdit_->addItem(QuestBase::LevelLabels[level], QVariant::fromValue(level));

	isReturnRequiredEdit_ = new QCheckBox;
	canBeDrawnEdit_ = new QCheckBox;

	followUpEdit_ = new EnumEdit;
	followUpEdit_->setEditable(true);

	rewardEdit_ = new PrizeEdit;

	editLayout_ = new QFormLayout;
	editLayout_->addRow(Labels::Quest::Title,            titleEdit_);
	editLayout_->addRow(Labels::Quest::Description,      descriptionEdit_);
	editLayout_->addRow(Labels::Quest::Fraction,         fractionEdit_);
	editLayout_->addRow(Labels::Quest::Level,            levelEdit_);
	editLayout_->addRow(Labels::Quest::IsReturnRequired, isReturnRequiredEdit_);
	editLayout_->addRow(Labels::Quest::CanBeDrawn,       canBeDrawnEdit_);
	editLayout_->addRow(Labels::Quest::FollowUp,         followUpEdit_);
	editLayout_->addRow(Labels::Quest::Reward,           rewardEdit_);

	editLayout_->setRowWrapPolicy(QFormLayout::DontWrapRows);
	editLayout_->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
// 	editLayout_->setFormAlignment(Qt::AlignHCenter | Qt::AlignTop);
	editLayout_->setLabelAlignment(Qt::AlignLeft);
}

void QuestEditor::initLayout()
{
	QHBoxLayout *mainLayout = new QHBoxLayout;

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
	questMapper_->addMapping(levelEdit_,            QuestModel::Level);
	questMapper_->addMapping(isReturnRequiredEdit_, QuestModel::IsReturnRequired, "checked");
	questMapper_->addMapping(canBeDrawnEdit_,       QuestModel::CanBeDrawn,       "checked");
	questMapper_->addMapping(followUpEdit_,         QuestModel::FollowUp);
	questMapper_->addMapping(rewardEdit_,           QuestModel::Reward);

	connect(questsList_->selectionModel(), &QItemSelectionModel::currentRowChanged, questMapper_, &QDataWidgetMapper::setCurrentModelIndex);
}

void QuestEditor::initViewPart()
{
	QPushButton *addQuestButton = new QPushButton(Editor::Labels::Add);
	addQuestButton->setShortcut(Editor::Shortcuts::Add);
	connect(addQuestButton, &QPushButton::clicked, this, &QuestEditor::addQuest);

	QPushButton *removeQuestButton = new QPushButton(Editor::Labels::Remove);
	removeQuestButton->setShortcut(Editor::Shortcuts::Remove);
	connect(removeQuestButton, &QPushButton::clicked, this, &QuestEditor::removeQuest);

	QHBoxLayout *buttonsLayout = new QHBoxLayout;
	buttonsLayout->addWidget(new QLabel(Editor::Titles::Quests));
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
	for (auto &quest : questModel_->quests())
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
