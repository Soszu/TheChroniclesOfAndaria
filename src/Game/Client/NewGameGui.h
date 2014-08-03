#pragma once

#include <QtWidgets>
#include "Game/Client/NewGameClt.h"
#include "Game/Client/Strings.h"
#include "Core/DataManager.h"

#include "Core/Containers/Player.h"

class NewGameGui : public QDialog {
	Q_OBJECT
public:
	NewGameGui(NewGameClt *newGameClt);

private:
	void initWindow();
	void initStripes();
	void initButtons();
	void fillOthersStripes();
	void clearOthersStripes();
	QHBoxLayout * draftToStripe(const PlayerDraft &draft);

	NewGameClt  *newGameClt_;
	QVBoxLayout *mainLayout_;
	QVBoxLayout *othersStripes_;
	QPushButton *readyButton_;

	QLineEdit *nameEdit_;
	QComboBox *playerRaceCombo_;
	QComboBox *playerClassCombo_;
	QPushButton *colorButton_;
	QColorDialog *colorDialog_;

private slots:
	void showColorDialog();
	void refreshOthersDrafts();
	void playerRaceChanged(const QString &playerRace);
	void playerClassChanged(const QString &playerClass);
	void playerReady();
};
