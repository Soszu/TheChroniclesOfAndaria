#include "panelakcji.h"
#include <QDebug>

PanelAkcji::PanelAkcji(QGroupBox* box)
{
	uklad = NULL;
	panel = box;
}

/**
 * @brief PanelAkcji::wyswietl	Wyświetla Panel zgodnie z obecnymi ustawieniami
 */
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

/**
 * @brief PanelAkcji::wyczyscPanel	Usuwa wszystkie przyciski z panelu.
 */
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

/**
 * @brief PanelAkcji::ustawAkcje	Ustawia akcje do wyświetlenia
 * @param akcje		Lista akcji, które powinny zostać wyświetlone.
 */
void PanelAkcji::ustawAkcje(QList<Akcja> akcje)
{
	this->akcje = akcje;
}

/**
 * @brief PanelAkcji::ustawZadania	Ustawia zadania do wyświetlenia.
 * @param zadania	Lista zadań, które powinny zostać wyswietlone
 */
void PanelAkcji::ustawZadania(QList<Zadanie *> zadania)
{
	this->zadania = zadania;
}
