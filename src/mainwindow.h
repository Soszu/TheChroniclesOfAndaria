#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QFrame>
#include <QGroupBox>
#include <QGraphicsView>
#include "panelakcji.h"
#include "oknogracza.h"
#include "obszarplanszy.h"
#include "mistrzgry.h"
#include "plansza.h"
#include "oknozasad.h"

namespace Ui {
class MainWindow;
}
class ObszarPlanszy;
class PanelAkcji;
class MistrzGry;

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
	void wyswietlZasady();

private:
	OknoZasad* oknoZasad;
	QWidget* widget;
	QHBoxLayout* layoutGlowny;
	QVBoxLayout* layoutBoczny;
	QGraphicsView* graphicsView;
	QFrame* ramka;
	QGroupBox* panel;

	PanelAkcji* panelAkcji;
	OknoGracza* oknoGracza;
	ObszarPlanszy* obszarPlanszy;
};

#endif // MAINWINDOW_H
