#pragma once
#include "Core/Containers/Quest.h"

class Journal {
public:
	Journal ();
	static const quint8 QuestsTakenLimit = 5;
	static const quint8 QuestDeclineCost = 2;

	//void removeQuest(int questId);
//	void generateDescription(Quest *quest, QTextBrowser *target); //NOTE QTextBrowser seems odd here...
private:
	QList <Quest> quests_;

};