#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtGui>
#include "panelakcji.h"
#include "newgamedialog.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	NewGameDialog* d = new NewGameDialog(this);
	d->show();


}

MainWindow::~MainWindow()
{
	delete ui;
}
