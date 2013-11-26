#include "Core/Containers/Prize.h"

Prize::Prize(int *reputation, quint16 gold, quint16 experience, QStringList groupNames, QList <int> *items)
	: reputation_(reputation), gold_(gold), experience_(experience), groupNames_(groupNames), items_(items)
{
}

Prize::~Prize()
{
	delete [] reputation_; //TODO CFiend skad wiadomo, ze to nalezy do nas? Moze lepiej trzymac stala tablice, zamiast alokowac na stercie?
	delete items_; //TODO CFiend j.w. skad to sie bierze?
}

int * Prize::reputation()
{
	return reputation_;
}

quint16 Prize::gold()
{
	return gold_;
}

quint16 Prize::experience()
{
	return experience_;
}

QStringList Prize::groupNames()
{
	return groupNames_;
}

QList <int> * Prize::items()
{
	return items_;
}
