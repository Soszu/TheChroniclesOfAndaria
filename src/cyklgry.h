#ifndef CYKLGRY_H
#define CYKLGRY_H

#include "gracz.h"
#include <QList>
#include <QString>
#include "mistrzgry.h"
#include "plansza.h"

class MistrzGry;
class Plansza;

class CyklGry
{
public:
	CyklGry();

	void setMistrzGry(MistrzGry* mistrz);
	void setPlansza(Plansza* plansza);
	void setGracze(QList<Gracz*> gracze);

	QList<Gracz*> getGracze();

	void rozpocznij();
	void zakonczGre();
	void zakonczTure();
private:
	void ruszGracza(int indeks);
	QList<Gracz*> gracze;
	int indeksAktualnego;


	Plansza* plansza;
	MistrzGry* mistrzGry;
};
#endif // CYKLGRY_H

