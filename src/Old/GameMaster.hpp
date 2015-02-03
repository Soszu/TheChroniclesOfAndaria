/*
Copyright (C) 2013 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
Thanks to 2013 Łukasz Piesiewicz <wookesh [at] gmail [dot] com>
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

#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include "Core/GameCycle.hpp"
#include "Core/Containers/Player.hpp"
#include "Core/Containers/Enemy.hpp"
#include "Core/Containers/Prize.hpp"
#include "Core/Containers/Item.hpp"
#include "Core/Containers/Quest.hpp"
#include "Core/Board.hpp"
#include "Containers/ItemModel.hpp"

#include "Game/PlayerWindow.hpp"
#include "Game/ActionPanel.hpp"
#include "Game/Windows/FightWindow.hpp"
#include "Game/Windows/MarketWindow.hpp"
#include "Game/Windows/PrizeWindow.hpp"
#include "Game/Windows/TavernWindow.hpp"
#include "Game/Windows/HealerWindow.hpp"
#include "Game/Windows/MarketViewWindow.hpp"

class ActionPanel;
class Board;
class FightWindow;
class GameCycle;
class HealerWindow;
class MarketWindow;
class PrizeWindow;
class TavernWindow;

enum class FightResult : quint8;

enum Action : quint8 {
	EndTurn,
	EnemyEasy,
	EnemyHard,
	Market,
	Tavern,
	QuestEnemy,
	Healer
};

static const QMap <Action, QString> ActionString {
	{Action::EndTurn, QString::fromUtf8("ZakoÅcz turÄ")},
	{Action::EnemyEasy, QString::fromUtf8("Walcz ze zwyczajnym przeciwnikiem ")},
	{Action::EnemyHard, QString::fromUtf8("Walcz z wymagajÄcym przeciwnikiem")},
	{Action::Market, QString::fromUtf8("IdÅº na bazar handlowaÄ ekwipunkiem")},
	{Action::Tavern, QString::fromUtf8("IdÅº do tawerny \nposzukaÄ nowych zadaÅ")},
	{Action::QuestEnemy, QString::fromUtf8("Walcz z przeciwnikiem z zadania")},
	{Action::Healer, QString::fromUtf8("IdÅº do uzdrowiciela")}
};

class GameMaster {
public:
	GameMaster(GameCycle *gameCycle);
	~GameMaster();
	void setBoard(Board *board);
	Board * board();
	void setActionPanel(ActionPanel *actionPanel);
	void setPlayerWindow(PlayerWindow *playerWindow);
	void setPlayers(QList <Player *> *players);
	void setComputerPlayers(QMap <int, AI *> computerPlayers);

	void beginGame();
	void movePlayer(int index);
	void newWeek();
	void selectedAction(int action);
	void moveExecuted();
	void updateBoard();
	void generateQuests();
	void endFight(Enemy *enemy, FightResult result);

	static const quint8 EnemyGroupCount = 5; //grupy przeciwnikow sÄ numerowane od 1.

private:
	static const int PVPActions = 20;

	void determinePossibleActions();
	void doAction(int action); //TODO CFiend enumy
	void doQuest(int questId);
	void startFight(int enemyType); //TODO CFiend moze tu powinien byc inny enum niz Action
	Enemy * generateEnemy(int enemyGroup);
	void generateQuestsForTavern(QList <Quest *> &dest, int fraction, bool overwritePrevious); //TODO CFiend bool w API jest podejrzany
	void generateWaresForMarket(QList <const Item *> &dest);

	GameCycle *gameCycle_;
	Board *board_;
	//SIGNALS
	ActionPanel *actionPanel_;
	//SIGNALS
	PlayerWindow *playerWindow_;

	//IN ENV
	Player *currentPlayer_;
	// __MAYBE__ IN ENV (IN OTHER FORM) DUNNO
	QMap <int, AI *> computerPlayers_;
	//IN ENV (IF WILL PREVAIL)
	QList <Player *> *players_;
	//IN QUEST HANDLER
	QMap <int, QList <Quest *> > questsInCities_;
	//IN MARKET HANDLER
	QMap <int, QList <const Item *> > waresInCities_;
	//MAY STAY
	QList <QPair <int, QString> > possibleActions_;
	//ERASE OR IN QUEST HANDLER
	Quest *currentQuest_;

	//IN HANDLERS (BY SIGNALS)
	FightWindow *fightWindow_;
	PrizeWindow *prizeWindow_;
	TavernWindow *tavernWindow_;
	MarketWindow *marketWindow_;
	HealerWindow *healerWindow_;
	
	//TEMPORARY FOR TESTING
	MarketViewWindow *marketViewWindow_;
	ItemModel *itemModel_;
};

#endif
