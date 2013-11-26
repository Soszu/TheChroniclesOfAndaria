#include "Core/AI/AI.h"

AI::AI(Player *player)
	: player_(player)
{
}

void AI::setActions(QList <Action> actions)
{
}

void AI::setQuests(QList <Quest *> quests)
{
}

int AI::decide()
{
	return EndTurn;
}
