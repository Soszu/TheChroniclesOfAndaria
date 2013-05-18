#include <QApplication>
#include "mainwindow.h"
#include "cyklgry.h"
#include "mistrzgry.h"
#include "plansza.h"
#include "oknonowejgry.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	MainWindow okno;
	OknoNowejGry nowaGra;
	CyklGry cykl;
	MistrzGry mistrz;
	Plansza plansza;

	okno.setMistrzGry(&mistrz); //potem mainwindow pokazuje swoim komponentom komu mają zgłaszać zmiany/ informace
	okno.setPlansza(&plansza);

	//ustalanie kogo mistrz gry ma prosić o wyświetlanie informacji
	//zamiast tego można to zrobić pośrednio przez mainwindow
	mistrz.setPanelAkcji(okno.getPanelAkcji());
	mistrz.setOknoGracza(okno.getOknoGracza());
	plansza.setObszarPlanszy(okno.getObszarPlanszy());

	cykl.setMistrzGry(&mistrz);
	cykl.setPlansza(&plansza);
	mistrz.setCyklGry(&cykl);
	mistrz.setPlansza(&plansza);
	plansza.setMistrzGry(&mistrz);
	nowaGra.setCyklGry(&cykl);
	nowaGra.setMainWindow(&okno);
	nowaGra.show();


	return a.exec();
}

