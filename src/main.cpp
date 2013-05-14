#include <QApplication>
#include "mainwindow.h"
#include "cyklgry.h"
#include "newgamedialog.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	MainWindow w;
	w.show();

	CyklGry cykl;
//	w.setCyklGry(&cykl);

	cykl.setPanelAkcji(w.getPanelAkcji());
	cykl.setOknoGracza(w.getOknoGracza());

	NewGameDialog okno;
	okno.show();
	okno.setCyklGry(&cykl);

	return a.exec();
}

