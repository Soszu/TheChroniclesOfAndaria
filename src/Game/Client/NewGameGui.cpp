#include "NewGameGui.h"

NewGameGui::NewGameGui(NewGameClt *newGameClt)
          : newGameClt_(newGameClt)
{
	initWindow();
	initStripes();
	initButtons();
}

void NewGameGui::initWindow()
{
	this->setWindowTitle(Client::Strings::NewGameWindowTitle);
	this->setSizeGripEnabled(false);

	mainLayout_ = new QVBoxLayout(this);
	mainLayout_->setSizeConstraint(QLayout::SetFixedSize);

	connect(newGameClt_, &NewGameClt::newSettings, this, &NewGameGui::refreshOthersDrafts);
}

void NewGameGui::initStripes()
{
	QLabel *myStripesTitle = new QLabel(Client::Strings::MyStripesTitle);

	nameEdit_ = new QLineEdit(newGameClt_->myDraft().name());
	nameEdit_->setMaxLength(MaxNameLength);
	connect(nameEdit_, &QLineEdit::textChanged, newGameClt_, &NewGameClt::setMyName);

	playerRaceCombo_ = new QComboBox();
	for (auto race : Race::labels())
		playerRaceCombo_->addItem(raceLabels[race]);
	connect(playerRaceCombo_, static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
	        this, &NewGameGui::playerRaceChanged);

	playerClassCombo_ = new QComboBox();
	for (auto _class : Class::labels())
		playerClassCombo_->addItem(classLabels[_class]);
	connect(playerClassCombo_, static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
	        this, &NewGameGui::playerClassChanged);

	QIcon colorIcon = QIcon(DataManager::pixmap(Paths::IconColor));
	colorButton_ = new QPushButton(colorIcon, Client::Strings::PickColor);
	colorDialog_ = new QColorDialog(newGameClt_->myDraft().color(), this);
	connect(colorButton_, &QPushButton::clicked, this, &NewGameGui::showColorDialog);

	QHBoxLayout *myStripe = new QHBoxLayout();
	myStripe->addWidget(nameEdit_);
	myStripe->addWidget(playerRaceCombo_);
	myStripe->addWidget(playerClassCombo_);
	myStripe->addWidget(colorButton_);

	QLabel *othersStripesTitle = new QLabel(Client::Strings::OthersStripesTitle);

	othersStripes_ = new QVBoxLayout;
	fillOthersStripes();

	QVBoxLayout *stripesLayout = new QVBoxLayout();
	mainLayout_->addLayout(stripesLayout);

	stripesLayout->addWidget(myStripesTitle);
	stripesLayout->addLayout(myStripe);
	stripesLayout->addWidget(othersStripesTitle);
	stripesLayout->addLayout(othersStripes_);
}


void NewGameGui::initButtons()
{
	QPushButton *cancelButton = new QPushButton(Client::Strings::CancelButton, this);
	connect(cancelButton, &QPushButton::clicked, this, &NewGameGui::close);

	readyButton_ = new QPushButton(Client::Strings::ReadyButton, this);
	connect(readyButton_, &QPushButton::clicked, this, &NewGameGui::playerReady);

	QHBoxLayout *buttonLayout = new QHBoxLayout();
	mainLayout_->addLayout(buttonLayout);

	buttonLayout->addWidget(cancelButton);
	buttonLayout->addWidget(readyButton_);
}

void NewGameGui::fillOthersStripes()
{
	for (auto &draft : newGameClt_->otherPlayersDrafts())
		othersStripes_->addLayout(draftToStripe(draft));
}

void NewGameGui::clearOthersStripes()
{
	while (othersStripes_->count()) {
		auto item = othersStripes_->takeAt(0);
		othersStripes_->removeItem(item);
		delete item;
	}
}

QHBoxLayout * NewGameGui::draftToStripe(const PlayerDraft &draft)
{
	QHBoxLayout *stripe = new QHBoxLayout();
	QLabel *name = new QLabel(draft.name());
	QLabel *color = new QLabel(draft.color().name());
	QLabel *playerRace = new QLabel(raceLabels[draft.playerRace()]);
	QLabel *playerClass = new QLabel(classLabels[draft.playerClass()]);

	stripe->addWidget(name);
	stripe->addWidget(color);
	stripe->addWidget(playerRace);
	stripe->addWidget(playerClass);

	return stripe;
}

void NewGameGui::showColorDialog()
{
	colorDialog_->open(newGameClt_, SLOT(setMyColor(const QColor &)));
}

void NewGameGui::refreshOthersDrafts()
{
	clearOthersStripes();
	fillOthersStripes();
}

void NewGameGui::playerRaceChanged(const QString &playerRace)
{
	newGameClt_->setMyRace(raceLabels.value(playerRace, Race::Human));
}

void NewGameGui::playerClassChanged(const QString &playerClass)
{
	newGameClt_->setMyClass(classLabels.value(playerClass, Class::Fighter));
}

void NewGameGui::playerReady()
{
	newGameClt_->switchPlayerIsReady();
	if (newGameClt_->playerIsReady())
		readyButton_->setText(Client::Strings::NotReadyButton);
	else
		readyButton_->setText(Client::Strings::ReadyButton);
}
