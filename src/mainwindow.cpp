#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	panelAkcji = new PanelAkcji(ui->groupBox);
	panelAkcji->setMistrzGry(mistrzGry);

	oknoGracza = new OknoGracza();

	obszarPlanszy = new ObszarPlanszy();
	ui->graphicsView->setScene(obszarPlanszy);
	obszarPlanszy->setPlansza(plansza);
}

MainWindow::~MainWindow()
{
	delete ui;
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
