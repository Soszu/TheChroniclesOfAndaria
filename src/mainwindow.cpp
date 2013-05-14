#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	panelAkcji = new PanelAkcji(ui->groupBox);
//	panelAkcji->setCyklGry(cyklGry);
	oknoGracza = new OknoGracza();
}

MainWindow::~MainWindow()
{
	delete ui;
}

PanelAkcji *MainWindow::getPanelAkcji()
{
	return panelAkcji;
}

OknoGracza *MainWindow::getOknoGracza()
{
	return oknoGracza;
}

//MainWindow::setCyklGry(CyklGry *cykl)
//{
//	this->cyklGry = cykl;
//}
