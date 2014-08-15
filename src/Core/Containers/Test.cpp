#include "Test.h"

void Test::take(Player *player) const
{
	emit result(player, Test::Result::Pass);
}
