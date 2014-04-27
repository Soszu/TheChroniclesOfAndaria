/*
Copyright (C) 2013 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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

#include "Core/GameCycle.h"
#include "Core/AI/AI.h"
#include "Core/Containers/Player.h"
#include "Core/Containers/Enemy.h"
#include "Core/Containers/Prize.h"
#include "Core/Containers/Item.h"
#include "Core/Containers/Quest.h"
#include "Core/Board.h"
#include "Core/Parsers/EnemyParser.h"
#include "Core/Parsers/ItemParser.h"
#include "Core/Parsers/PrizeParser.h"
#include "Core/Parsers/QuestParser.h"
#include "Game/PlayerWindow.h"
#include "Game/ActionPanel.h"
#include "Core/Game.h"
#include "Game/Windows/FightWindow.h"
#include "Game/Windows/MarketWindow.h"
#include "Game/Windows/PrizeWindow.h"
#include "Game/Windows/TavernWindow.h"
#include "Game/Windows/HealerWindow.h"

class ActionPanel;
class AI;
class Board;
class EnemyParser;
class FightWindow;
class GameCycle;
class HealerWindow;
class ItemParser;
class MarketWindow;
class PrizeParser;
class PrizeWindow;
class QuestParser;
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
	{Action::EndTurn, QString::fromUtf8("Zakończ turę")},
	{Action::EnemyEasy, QString::fromUtf8("Walcz ze zwyczajnym przeciwnikiem ")},
	{Action::EnemyHard, QString::fromUtf8("Walcz z wymagającym przeciwnikiem")},
	{Action::Market, QString::fromUtf8("Idź na bazar handlować ekwipunkiem")},
	{Action::Tavern, QString::fromUtf8("Idź do tawerny \nposzukać nowych zadań")},
	{Action::QuestEnemy, QString::fromUtf8("Walcz z przeciwnikiem z zadania")},
	{Action::Healer, QString::fromUtf8("Idź do uzdrowiciela")}
};

class GameMaster {
	friend class EnemyParser;
	friend class ItemParser;
	friend class PrizeParser;
	friend class QuestParser;
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
	void grantPrize(Player *player, Prize *prize, bool isEndOfTurn); //TODO CFiend bool w API jest podejrzany

	static const quint8 EnemyGroupCount = 5; //grupy przeciwnikow są numerowane od 1.

private:
	static const int PVPActions = 20;

	void determinePossibleActions();
	void doAction(int action); //TODO CFiend enumy
	void doQuest(int questId);
	void startFight(int enemyType); //TODO CFiend moze tu powinien byc inny enum niz Action
	Prize * mergePrizes(Prize *first, Prize *second);
	Enemy * generateEnemy(int enemyGroup);
	void generateQuestsForTavern(QList <Quest *> &dest, int fraction, bool overwritePrevious); //TODO CFiend bool w API jest podejrzany
	void generateWaresForMarket(QList <const Item *> &dest);

	GameCycle *gameCycle_;
	Board *board_;
	ActionPanel *actionPanel_;
	PlayerWindow *playerWindow_;

	QMap <int, QList <int> *> enemyGroups_; //dla każdej grupy reprezentowanej przez poziom trzymane są identyfikatory przeciwnikoe do niej należących
	QMap <int, Enemy *> enemies_; //jako klucz jest zapisywany identyfikator w postaci liczby całkowitej
	QMap <QString, QList <int> *> itemGroups_; //dla każdej grupy trzymane są identyfikatory przedmiotów do niej należących
	QMap <int, const Item *> items_; //dla każdego identyfikatora trzymany jest opis przedmiotu.
	QMap <int, Prize *> prizes_; //dla każdego identyfikatora trzymany jest opis nagrody.
	QMap <int, Quest *> quests_; //dla każdego identyfikatora trzymany jest opis zadania.

	Player *currentPlayer_;
	QMap <int, AI *> computerPlayers_;
	QList <Player *> *players_;
	QMap <int, QList <Quest *> > questsInCities_;
	QMap <int, QList <const Item *> > waresInCities_;
	QList <QPair <int, QString> > possibleActions_;
	Quest *currentQuest_;

	FightWindow *fightWindow_;
	PrizeWindow *prizeWindow_;
	TavernWindow *tavernWindow_;
	MarketWindow *marketWindow_;
	HealerWindow *healerWindow_;
};

#endif
