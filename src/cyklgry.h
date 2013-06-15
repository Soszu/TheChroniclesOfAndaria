#ifndef CYKLGRY_H
#define CYKLGRY_H

#include "gracz.h"
#include <QList>
#include <QString>
#include <QMainWindow>
#include "mistrzgry.h"
#include "plansza.h"

class MistrzGry;
class Plansza;

class CyklGry
{
public:
	CyklGry(int *wynikParsowania);
	~CyklGry();

	void setMistrzGry(MistrzGry* mistrz);
	void setPlansza(Plansza* plansza);
	void setGracze(QList<Gracz*> gracze);
	void setMainWindow(QMainWindow* okno);
	QMainWindow* getMainWindow();
	void wystapilBlad(QString komunikat, int blad);

	QList<Gracz*> getGracze();

	void wykreslGracza(Gracz* gracz);
	void rozpocznij();
	void zakonczTure();
private:
	void graczWygral(Gracz* gracz);
	bool czySpelnionyWarunekZwyciestwa(Gracz* gracz);
	void ruszGracza(int indeks);
	QList<Gracz*> gracze;
	int indeksAktualnego;

	int* wynikParsowania;
	QDialog* komunikatOBledzie;
	QMainWindow* mainWindow;
	Plansza* plansza;
	MistrzGry* mistrzGry;
};
#endif // CYKLGRY_H

