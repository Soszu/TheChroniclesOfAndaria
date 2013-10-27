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
void PanelAkcji::wyswietl(QList<QPair<int, QString> >* dzialania)
{
	wyczyscPanel();
	uklad = new QVBoxLayout(panel);

	for(int i = 0; i < dzialania->size(); ++i)
	{
		przyciski.push_back(new MojPrzycisk(dzialania->at(i).first));
		przyciski.back()->setText(dzialania->at(i).second);
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
