#include "Test.h"

QDataStream & operator<<(QDataStream &out, const Test &effectType)
{
	return out;
}

QDataStream & operator>>(QDataStream &in, Test &effectType)
{
	return in;
}