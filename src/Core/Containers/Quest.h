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

#pragma once

#include "Core/Containers/Bases/QuestBase.h"
#include "Core/Actions/Action.h"
#include "Core/Containers/Test.h"

class Player;

class Quest : public Action {
public:
	Quest(const QuestBase *base, Coordinates source);

	bool canBeDrawn() const;
	QString description() const;
	const Quest *followUp() const;
	Kingdom fraction() const;
	bool isReturnRequired() const;
	QuestBase::Level level() const;
	QHash <Coordinates, TestBase> objectives() const;
	const Prize *prize() const;
	Coordinates source() const;
	QString title() const;
	const QSet <Coordinates> & toDo() const;
	UID uid() const;

	void execute(Player *player);

private:
	const QuestBase *base_;
	const Coordinates source_;
	QSet <Coordinates> toDo_;

private slots:
	void testEnded(Player *player, Test::Result result);
};
