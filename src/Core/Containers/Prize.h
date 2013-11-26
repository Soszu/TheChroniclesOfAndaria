#ifndef PRIZE_H
#define PRIZE_H

#include <QtCore>

class Prize {

public:
	Prize(int *reputation, quint16 gold, quint16 experience, QStringList groupNames, QList <int> *items);
	~Prize();

	int * reputation();
	quint16 gold();
	quint16 experience();
	QStringList groupNames();
	QList <int> * items();

private:
	int *reputation_; //TODO CFiend to na pewno ma byc pointer, a nie np. kopia albo const pointer const?
	quint16 gold_;
	quint16 experience_;
	QStringList groupNames_;
	QList <int> *items_;
};

#endif
