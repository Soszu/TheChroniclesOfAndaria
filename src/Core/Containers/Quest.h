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
