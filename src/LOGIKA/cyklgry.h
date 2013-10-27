#ifndef CYKLGRY_H
#define CYKLGRY_H

#include "gracz.h"
#include <QList>
#include <QString>
#include <QMainWindow>
#include "mistrzgry.h"
#include "sztucznainteligencja.h"
#include "plansza.h"

class MistrzGry;
class Plansza;
class MainWindow;

class CyklGry
{
public:
	CyklGry(int *wynikParsowania);
	~CyklGry();

	void setMistrzGry(MistrzGry* mistrz);
	void setPlansza(Plansza* plansza);
	void setGracze(QList<Gracz*> gracze);
	void setMainWindow(MainWindow *okno);
	MainWindow* getMainWindow();
	void wystapilBlad(QString komunikat, int blad);

	QList<Gracz*> getGracze();

	void wykreslAktualnego();
	void rozpocznij();
	void zakonczTure();
private:
	void zrestartujZmienne();
	void graczWygral(Gracz* gracz);
	bool czySpelnionyWarunekZwyciestwa(Gracz* gracz);
	void ruszGracza(int indeks);
	void wyznaczKolejnego();
	void nowyDzien();

	int liczbaAktywnych;
	int indeksAktualnego;
	int tydzien;
	int dzien;

	QList<Gracz*> gracze;
	QMap<int, SztucznaInteligencja*> boty;

	int* wynikParsowania;
	QDialog* komunikatOBledzie;
	MainWindow* mainWindow;
	Plansza* plansza;
	MistrzGry* mistrzGry;
};
#endif // CYKLGRY_H

