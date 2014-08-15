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

#include "Quest.h"

Quest::Quest(const QuestBase *base, Coordinates source) : base_(base), source_(source)
{}

void Quest::execute(Player *player)
{
//find currPos, find Test to do connect to result & take it
}

void Quest::testEnded(Player *player, Test::Result result)
{
	//if result unsettled -> nothing
	//if resule pass, check done, give prize, check if need return and add to map, tell to remove / addToDone (be careful to memory), add followUp
	//if not pass, remove (ew. penalty for failure)
}
