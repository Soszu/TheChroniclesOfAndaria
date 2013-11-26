#include "Core/Containers/Field.h"

Field::Field (FieldId fieldId, QString name, int coefficient, bool hasEnemy, bool hasCity, QString imageFile, int fraction)
	: fieldId_(fieldId), name_(name), moveCost_(coefficient), hasEnemy_(hasEnemy), imageFile_(imageFile), fraction_(fraction)
{
}

FieldId Field::fieldId() const
{
	return fieldId_;
}

QString Field::name() const
{
	return name_;
}

int Field::moveCost() const
{
	return moveCost_;
}

bool Field::hasEnemy() const
{
	return hasEnemy_;
}

bool Field::hasCity() const
{
	return hasCity_;
}

QString Field::imageFile() const
{
	return imageFile_;
}

int Field::fraction() const
{
	return fraction_;
}
