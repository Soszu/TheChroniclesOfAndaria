#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "panelakcji.h"
#include "oknogracza.h"
//#include "cyklgry.h"

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
//	void setCyklGry(CyklGry* cykl);

private:
	Ui::MainWindow *ui;
	PanelAkcji* panelAkcji;
	OknoGracza* oknoGracza;
//	CyklGry* cyklGry;

};

#endif // MAINWINDOW_H
