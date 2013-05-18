#include "mainwindow.h"
#include <QtCore>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	widget = new QWidget();
	this->setCentralWidget(widget);
	layoutGlowny = new QHBoxLayout(widget);
	layoutBoczny = new QVBoxLayout();
	graphicsView = new QGraphicsView;
	ramka = new QFrame();
	panel = new QGroupBox();

	layoutGlowny->addWidget(graphicsView);
	layoutGlowny->addLayout(layoutBoczny);
	layoutBoczny->addWidget(ramka);
	layoutBoczny->addWidget(panel);

	panelAkcji = new PanelAkcji(panel);
	panelAkcji->setMistrzGry(mistrzGry);

	oknoGracza = new OknoGracza(ramka);

	obszarPlanszy = new ObszarPlanszy();
	graphicsView->setScene(obszarPlanszy);
	obszarPlanszy->setPlansza(plansza);
}

MainWindow::~MainWindow()
{
}

/**
 * @brief MainWindow::getPanelAkcji Udostępnia
 * @return
 */
PanelAkcji *MainWindow::getPanelAkcji()
{
	return panelAkcji;
}

OknoGracza *MainWindow::getOknoGracza()
{
	return oknoGracza;
}

ObszarPlanszy *MainWindow::getObszarPlanszy()
{
	return obszarPlanszy;
}

/**
 * @brief MainWindow::setMistrzGry
 * @param cykl
 */
void MainWindow::setMistrzGry(MistrzGry *mistrz)
{
	this->mistrzGry = mistrz;
}


void MainWindow::setPlansza(Plansza *plansza)
{
	this->plansza = plansza;
}
