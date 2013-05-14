#include "panelakcji.h"
#include <QDebug>

PanelAkcji::PanelAkcji(QGroupBox* box)
{
	uklad = NULL;
	panelAkcji = box;
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

void PanelAkcji::kliknietoPrzyciskONazwie(QString nazwa)
{
	qDebug() << "kliknieto przycisk: " << nazwa;
	//cyklGry->wybranoAkcje(nazwa);
}

void PanelAkcji::zwolnijPamiec()
{
	delete uklad;
	for(int i = 0; i < przyciski.size(); ++i)
		delete przyciski[i];
}


//void PanelAkcji::setCyklGry(CyklGry *cykl)
//{
//	this->cyklGry = cykl;
//}
