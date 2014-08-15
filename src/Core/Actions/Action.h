#pragma once

#include "Game/Common/Authority.h"

class Player;

class Action : public Authority {
public:
	virtual QString title() const = 0;
	virtual void execute(Player *player) = 0;
};