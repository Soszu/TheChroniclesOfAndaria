/*
 C o*pyright (C) 2013 Łukasz Piesiewicz <wookesh [at] gmail [dot] com>
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

#ifndef FIGHTPARTICIPANT_H
#define FIGHTPARTICIPANT_H

#include <QtCore>

class FightParticipant {
public:
	
	FightParticipant(QString name, QString imageFile = "", quint16 healthCurrent = 0);
	
	enum class AttackType : quint8 {
		Melee,
		Ranged,
		Magical
	};
	
	struct BattleStats {
		qint8 healthMax_;
		qint8 defence_;
		qint8 perception_;
		QMap <AttackType, QPair <qint8, qint8> > attacks_; //or QHash | AttackType -> min value, range
	};
	
	QString name() const;
	QString imageFile() const;
	quint16 healthCurrent() const;

	void setHealthCurrent(quint16 healthCurrent);
	
protected:
	QString name_;
	QString imageFile_;
	//const FightStratedy fightStrategy_; //not yet implemented (will be introduced with PVP)
	qint16 healthCurrent_;
};



#endif