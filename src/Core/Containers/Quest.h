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

#ifndef QUEST_H
#define QUEST_H

#include "Core/Containers/Enemy.h"
#include "Core/Containers/Field.h"
#include "Core/Containers/Prize.h"

//TODO CFiend class Quest { public: enum class Type ... }
enum QuestType {
	pokonaj = 1,
	przynies = 2, //realizuje też "dotrzyj na miejsce" jeśli czyPowrótWymagany == false
	odnajdz = 3
};

enum QuestLevel {
	easy,
	medium,
	hard
};

class Quest {

public:
	Quest(int id,
	      QuestType type,
	      QuestLevel level,
	      int fraction,
	      QString title,
	      QString description,
	      bool isReturnRequired,
	      FieldId targetField,
	      Prize *prize,
	      QList <Enemy *> *enemies);
	Quest(Quest *quest); //TODO CFiend major WTF, to chyba mialo byc Quest(const Quest &)
	~Quest();

	int id() const;
	QuestType type() const;
	QuestLevel level() const;
	int fraction() const;
	QString title() const;
	QString description() const;
	bool isReturnRequired() const;
	FieldId targetField() const;
	void setTargetField(FieldId field);
	Prize * prize() const;
	QList <Enemy *> * enemies() const;
	void setEmployerField(FieldId field);
	FieldId employerField() const;
	void setIsPartiallyCompleted(bool value);
	bool isPartiallyCompleted() const;

private:
	int id_;
	QuestType type_;
	QuestLevel level_;
	int fraction_;
	QString title_;
	QString description_;
	bool isReturnRequired_;
	FieldId targetField_;
	Prize *prize_;
	QList <Enemy *> *enemies_;
	FieldId employerField_;
	bool isPartiallyCompleted_;
};

#endif
