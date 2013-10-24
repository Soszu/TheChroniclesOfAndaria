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

	menuGra = new QMenu("Gra");
	menuWidok = new QMenu("Widok");
	menuPomoc = new QMenu("Pomoc");

	menuBar()->addMenu(menuGra);
	menuBar()->addMenu(menuWidok);
	menuBar()->addMenu(menuPomoc);

	layoutGlowny->addWidget(graphicsView);
	layoutGlowny->addLayout(layoutBoczny);
	layoutBoczny->addWidget(ramka);
	layoutBoczny->addWidget(panel);

	panelAkcji = new PanelAkcji(panel);

	oknoGracza = new OknoGracza(ramka);
	obszarPlanszy = new ObszarPlanszy(this);
	graphicsView->setScene(obszarPlanszy);

	wyswietlaczDaty = new QLabel(statusBar());
	statusBar()->addPermanentWidget(wyswietlaczDaty);
	obszarPlanszy->setPasekStanu(statusBar());

	menuGra->addAction("Nowa gra");
	menuGra->addSeparator();
	menuGra->addAction(QString::fromUtf8("Wczytaj grę"));
	menuGra->addAction(QString::fromUtf8("Zapisz grę"));
	menuGra->addSeparator();
	menuGra->addAction(QString::fromUtf8("Zakończ"), this, SLOT(close()));

	menuWidok->addAction(QString::fromUtf8("Oddal"), obszarPlanszy, SLOT(powiekszRozmiarPlanszy()), Qt::CTRL + Qt::Key_Minus);
	menuWidok->addAction(QString::fromUtf8("Przybliż"), obszarPlanszy, SLOT(pomniejszRozmiarPlanszy()), Qt::CTRL + Qt::Key_Plus);
	menuWidok->addAction(QString::fromUtf8("Przywróć rozmiar"), obszarPlanszy, SLOT(przywrocRozmiarPlanszy()), Qt::CTRL + Qt::Key_Equal);

	menuPomoc->addAction("Pomoc", this, SLOT(wyswietlZasady()), Qt::Key_F1);
	menuPomoc->addAction("O Autorze");
}

MainWindow::~MainWindow()
{
	delete oknoGracza;
	delete obszarPlanszy;
	delete panelAkcji;

	delete menuGra;
	delete menuWidok;
	delete menuPomoc;
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
 * @brief MainWindow::zmienDate		Wyświetla wskazaną datę na pasku statusu
 * @param dzien
 * @param tydzien
 */
void MainWindow::zmienDate(int dzien, int tydzien)
{
	wyswietlaczDaty->setText(QString::fromUtf8("Dzień ") + QString::number(dzien) +
				 QString::fromUtf8(", Tydzień ") + QString::number(tydzien));
}

/**
 * @brief MainWindow::wyswietlZasady	Wyświetla okno zasad i blokuje pozostałe okna
 */
void MainWindow::wyswietlZasady()
{
	oknoZasad = new OknoZasad();
	oknoZasad->setWindowModality(Qt::ApplicationModal);
	oknoZasad->setAttribute(Qt::WA_DeleteOnClose);
	oknoZasad->show();
}

/**
 * @brief MainWindow::setPlansza Ustawia planszę dla elementów które jej potrzebują.
 * @param plansza
 */
void MainWindow::setPlansza(Plansza *plansza)
{
	obszarPlanszy->setPlansza(plansza);
}
