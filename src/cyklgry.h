#ifndef CYKLGRY_H
#define CYKLGRY_H

#include "gracz.h"
#include <QList>
#include <QString>
#include "panelakcji.h"
#include "oknogracza.h"
#include "mistrzgry.h"
//#include "plansza.h"

class CyklGry
{
public:
	CyklGry();

	void setGracze(QList<Gracz*> gracze);
	void setPanelAkcji(PanelAkcji* panel);
	void setOknoGracza(OknoGracza* okno);
	void wybranoAkcje(QString nazwa);
	QList<Gracz*> getGracze();

	void rozpocznij();
	void zakonczGre();
	void zakonczTure();
private:
	void ruszGracza(int indeks);
	QList<Gracz*> gracze;
	Gracz* aktualnyGracz;
	int indeksAktualnego;

	PanelAkcji* panelAkcji;
	OknoGracza* oknoGracza;
};
#endif // CYKLGRY_H
