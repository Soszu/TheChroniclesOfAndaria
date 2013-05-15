#ifndef OBSZARPLANSZY_H
#define OBSZARPLANSZY_H

#include <QGraphicsScene>
#include"plansza.h"

class Plansza;

class ObszarPlanszy : public QGraphicsScene
{
	Q_OBJECT
public:
	explicit ObszarPlanszy();
	void setPlansza(Plansza* plansza);

private:
	Plansza *plansza;

signals:

public slots:

};

#endif // OBSZARPLANSZY_H
