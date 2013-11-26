#ifndef NEWGAMEWINDOW_H
#define NEWGAMEWINDOW_H

#include <QtWidgets>

#include "Core/Containers/Player.h"
#include "Core/Game.h"
#include "Core/GameCycle.h"

class NewGameWindow : public QDialog {
	Q_OBJECT;
public:
	explicit NewGameWindow(QWidget *parent = nullptr);
	~NewGameWindow();
	void setGameCycle(GameCycle *gameCycle);
	void setMainWindow(QMainWindow *mainWindow);

private:
	GameCycle *gameCycle_;
	QMainWindow *mainWindow_;
	quint8 playerCount_;

	//TODO CFiend kill it or enhance it?
	struct PlayerSelectionRow {
		QLineEdit *nameEdit;
		QComboBox *playerRaceCombo;
		QComboBox *playerClassCombo;
		QComboBox *colorCombo;
		QCheckBox *isAiCheckBox;
	};

	QList <PlayerSelectionRow> playerRows;

	QHBoxLayout *playerSelectionRowLayouts[MaxPlayers];

	QMessageBox *messageBox;

	void fillPlayerSelectionRow(PlayerSelectionRow *row, int playerNumber);

private slots:
	void addPlayerSelectionRow();
	void removePlayerSelectionRow();
	void validate();
};

#endif
