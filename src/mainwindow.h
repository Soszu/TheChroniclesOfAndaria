#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "panelakcji.h"
#include "oknogracza.h"
#include "obszarplanszy.h"
#include "mistrzgry.h"
#include "plansza.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	PanelAkcji* getPanelAkcji();
	OknoGracza* getOknoGracza();
	ObszarPlanszy* getObszarPlanszy();
	void setPlansza(Plansza* plansza);
	void setMistrzGry(MistrzGry* mistrz);

private:
	Ui::MainWindow *ui;

	PanelAkcji* panelAkcji;
	OknoGracza* oknoGracza;
	ObszarPlanszy* obszarPlanszy;

	MistrzGry* mistrzGry;
	Plansza* plansza;

};

#endif // MAINWINDOW_H
