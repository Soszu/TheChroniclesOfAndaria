#include <Core/Containers/FightParticipant.h>

FightParticipant::FightParticipant(QString name, QString imageFile, quint16 healthCurrent)
				: name_(name), imageFile_(imageFile), healthCurrent_(healthCurrent)
{
}


QString FightParticipant::name() const
{
	return name_;
}

QString FightParticipant::imageFile() const
{
	return imageFile_;
}

quint16 FightParticipant::healthCurrent() const
{
	return healthCurrent_;
}

void FightParticipant::setHealthCurrent(quint16 healthCurrent)
{
	healthCurrent_ = healthCurrent;
}

