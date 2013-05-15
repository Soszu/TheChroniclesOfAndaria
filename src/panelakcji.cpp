#include "panelakcji.h"
#include <QDebug>

PanelAkcji::PanelAkcji(QGroupBox* box)
{
	uklad = NULL;
	panelAkcji = box;
}

/**
 * @brief PanelAkcji::wyswietlAkcje Wyświetla przyciski akcji wymienione w zadanej liście.
 * @param akcje Lista nazw akcji do wyświetlenia
 */
void PanelAkcji::wyswietlAkcje(QList<QString> akcje)
{
	/*
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
	*/
}

/**
 * @brief PanelAkcji::kliknietoPrzyciskONazwie Powiadamia mistrza gry o kliknięciu na przcisk.
 * @param nazwa Nazwa klikniętego przycisku
 */
void PanelAkcji::kliknietoPrzyciskONazwie(QString nazwa)
{
	qDebug() << "kliknieto przycisk: " << nazwa;
	mistrzGry->wybranoAkcje(nazwa);
}

/**
 * @brief PanelAkcji::zwolnijPamiec Zwalnia pamięć, którą zajmowały poprzednie przyciski
 */
void PanelAkcji::zwolnijPamiec()
{
	delete uklad;
	for(int i = 0; i < przyciski.size(); ++i)
		delete przyciski[i];
}

/**
 * @brief PanelAkcji::setMistrzGry Ustawia mistrza gry, którego panel powiadomi o kliknięciu
 * @param mistrz
 */
void PanelAkcji::setMistrzGry(MistrzGry *mistrz)
{
	this->mistrzGry = mistrz;
}
