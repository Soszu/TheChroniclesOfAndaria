#ifndef AI_H
#define AI_H

#include "Core/Containers/Player.h"
#include "Core/Containers/Quest.h"
#include "Core/GameMaster.h"

enum Action : quint8;

class AI {

public:
	AI(Player *player);
	void setActions(QList <Action> actions);
	void setQuests(QList <Quest *> quests);
	int decide();

private:
	Player *player_;
};

#endif
