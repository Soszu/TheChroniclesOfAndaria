#include "Core/Containers/Quest.h"

Quest::Quest(int id,
	     QuestType type,
	     QuestLevel level,
	     int fraction,
	     QString title,
	     QString description,
	     bool isReturnRequired,
	     FieldId targetField,
	     Prize *prize,
	     QList <Enemy *> *enemies)
	: id_(id),
	  type_(type),
	  level_(level),
	  fraction_(fraction),
	  title_(title),
	  description_(description),
	  isReturnRequired_(isReturnRequired),
	  targetField_(targetField),
	  prize_(prize),
	  enemies_(enemies) //TODO CFiend skad to sie bierze?
{
	FieldId empty = {-1, -1};
	this->employerField_ = empty;
	isPartiallyCompleted_ = !isReturnRequired;
	if (type == pokonaj)
		isPartiallyCompleted_ = false;
}

//TODO CFiend kill it with fire
Quest::Quest(Quest *quest)
{
	this->id_ = quest->id_;
	this->type_ = quest->type_;
	this->level_ = quest->level_;
	this->fraction_ = quest->fraction_;
	this->title_ = quest->title_;
	this->description_ = quest->description_;
	this->isReturnRequired_ = quest->isReturnRequired_;
	this->targetField_ = quest->targetField_;
	this->prize_ = quest->prize_;

	enemies_ = new QList <Enemy *>;
	for(int i = 0; i < quest->enemies_->size(); ++i)
		enemies_->push_back(quest->enemies_->at(i));

	employerField_ = quest->employerField_;

	isPartiallyCompleted_ = isReturnRequired_ ? false : true;
	if(type_ == pokonaj)
		isPartiallyCompleted_ = false;
}

Quest::~Quest()
{
	delete enemies_;
}

int Quest::id() const
{
	return id_;
}

QuestType Quest::type() const
{
	return type_;
}

QuestLevel Quest::level() const
{
	return level_;
}

int Quest::fraction() const
{
	return fraction_;
}

QString Quest::title() const
{
	return title_;
}

QString Quest::description() const
{
	return description_;
}

bool Quest::isReturnRequired() const
{
	return isReturnRequired_;
}

FieldId Quest::targetField() const
{
	return targetField_;
}

void Quest::setTargetField(FieldId field)
{
	this->targetField_ = field;
}

Prize * Quest::prize() const
{
	return prize_;
}

QList <Enemy *> * Quest::enemies() const
{
	return enemies_;
}

void Quest::setEmployerField(FieldId field)
{
	employerField_ = field;
}

FieldId Quest::employerField() const
{
	return employerField_;
}

void Quest::setIsPartiallyCompleted(bool value)
{
	isPartiallyCompleted_ = value;
}

bool Quest::isPartiallyCompleted() const
{
	return isPartiallyCompleted_;
}
