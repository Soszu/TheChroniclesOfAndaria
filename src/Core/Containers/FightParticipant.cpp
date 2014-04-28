/*
Copyright (C) 2013 Łukasz Piesiewicz <wookesh [at] gmail [dot] com>
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

