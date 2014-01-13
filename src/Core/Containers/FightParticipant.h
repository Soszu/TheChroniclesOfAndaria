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