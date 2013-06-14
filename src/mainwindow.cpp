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

	oknoGracza = new OknoGracza(ramka);
	obszarPlanszy = new ObszarPlanszy();
	graphicsView->setScene(obszarPlanszy);
}

MainWindow::~MainWindow()
{
	delete oknoGracza;
	delete obszarPlanszy;
//BUG:	delete panelAkcji; nie zwalnia się, jeżeli mainwindow nie było wyświetlone(i jest zakomentowane), powoduje błędy, jeśli MW jest wyświetlone (i jest odkomentowane)
}

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
 * @brief MainWindow::setMistrzGry Ustawia mistrza dla podelementów, które go potrzebują
 * @param mistrz
 */
void MainWindow::setMistrzGry(MistrzGry *mistrz)
{
	panelAkcji->setMistrzGry(mistrz);
	oknoGracza->setMistrzGry(mistrz);
}

/**
 * @brief MainWindow::setPlansza Ustawia planszę dla elementów które jej potrzebują.
 * @param plansza
 */
void MainWindow::setPlansza(Plansza *plansza)
{
	obszarPlanszy->setPlansza(plansza);
}
