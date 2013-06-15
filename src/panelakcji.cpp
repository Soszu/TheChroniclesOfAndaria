#include "panelakcji.h"
#include <QDebug>

PanelAkcji::PanelAkcji(QGroupBox* box)
{
	uklad = NULL;
	panel = box;
}

void PanelAkcji::ustawAkcje(QList<Akcja> akcje)
{
	this->akcje = akcje;
}

void PanelAkcji::wyswietl()
{
	wyczyscPanel();
	uklad = new QVBoxLayout(panel);

	foreach(Zadanie* i, zadania)
	{
		przyciski.push_back(new MojPrzycisk(-1 * (i->getId()) ));
		przyciski.back()->setText( QString("Wykonaj zadanie:\n") + i->getTytul());
		uklad->addWidget(przyciski.back());
		connect(przyciski.back(), SIGNAL(kliknietyID(int)), this, SLOT(kliknietoPrzycisk(int)));
	}

	foreach(int i, akcje)
	{
		przyciski.push_back(new MojPrzycisk(i));
		przyciski.back()->setText(AKCJE[i]);
		uklad->addWidget(przyciski.back());
		connect(przyciski.back(), SIGNAL(kliknietyID(int)), this, SLOT(kliknietoPrzycisk(int)));
	}

	qDebug() << "Panel Akcji wyswietlil zadane akcje";
}

/**
 * @brief PanelAkcji::setMistrzGry Ustawia mistrza gry, którego panel powiadomi o kliknięciu
 * @param mistrz
 */
void PanelAkcji::setMistrzGry(MistrzGry *mistrz)
{
	this->mistrzGry = mistrz;
}

/**
 * @brief PanelAkcji::kliknietoPrzycisk Zgłasza mistrzowi gry, że pewien przycisk został kliknięty.
 * @param n
 */
void PanelAkcji::kliknietoPrzycisk(int n)
{
	mistrzGry->wybranoDzialanie(n);
}

void PanelAkcji::wyczyscPanel()
{
	for(int i = 0; i < przyciski.size(); ++i)
	{
		uklad->removeWidget(przyciski[i]);
		delete przyciski[i];
	}
	przyciski.clear();
	delete uklad;
}

void PanelAkcji::ustawZadania(QList<Zadanie *> zadania)
{
	this->zadania = zadania;
}
