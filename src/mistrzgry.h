#ifndef MISTRZGRY_H
#define MISTRZGRY_H

#include <QList>
#include <QString>
#include "cyklgry.h"
#include "gracz.h"
#include "plansza.h"
#include "oknogracza.h"
#include "panelakcji.h"

class PanelAkcji;
class CyklGry;
class Plansza;

class MistrzGry
{
public:
	MistrzGry();
	void ruszGracza(Gracz* gracz);
	QList<QString> mozliweAkcje(Gracz* gracz);
	void setCyklGry(CyklGry* cykl);
	void setPlansza(Plansza* plansza);
	void setPanelAkcji(PanelAkcji* panel);
	void setOknoGracza(OknoGracza* okno);
	void wybranoAkcje(QString nazwa);
private:
	CyklGry* cyklGry;
	PanelAkcji* panelAkcji;
	OknoGracza* oknoGracza;
	Plansza* plansza;
};

#endif // MISTRZGRY_H
