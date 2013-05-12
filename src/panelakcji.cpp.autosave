#include "panelakcji.h"
#include <QDebug>

PanelAkcji::PanelAkcji()
{
	uklad = NULL;
}

PanelAkcji& PanelAkcji::getPanelAkcji()
{
	static PanelAkcji instancja;
	return instancja;
}

void PanelAkcji::wyswietlAkcje(QList<QString> akcje)
{
	zwolnijPamiec();
	przyciski.clear();
	uklad = new QVBoxLayout;

	for(int i = 0; i < akcje.size(); ++i)
	{
		przyciski.push_front(new MyButton(akcje[i]));
		uklad->addWidget(przyciski.front());
		connect(przyciski.front(), SIGNAL(kliknietyNazwa(QString)), this, SLOT(kliknietoPrzyciskONazwie(QString)));
	}

	panelAkcji->setLayout(uklad);
}

void PanelAkcji::setGroupBox(QGroupBox* box)
{
	panelAkcji = box;
}

void PanelAkcji::kliknietoPrzyciskONazwie(QString nazwa)
{
	qDebug() << "kliknieto przycisk: " << nazwa;
}

void PanelAkcji::zwolnijPamiec()
{
	delete uklad;
	for(int i = 0; i < przyciski.size(); ++i)
		delete przyciski[i];
}
