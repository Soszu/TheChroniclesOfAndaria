#include "Gui/ActionPanel.h"
#include <QDebug>

ActionPanel::ActionPanel(QGroupBox* box)
{
	uklad = nullptr;
	panel = box;
}

/**
 * @brief PanelAkcji::wyswietl	Wyświetla Panel zgodnie z obecnymi ustawieniami
 */
void ActionPanel::displayActions(QList<QPair<int, QString> >* dzialania)
{
	wyczyscPanel();
	uklad = new QVBoxLayout(panel);

	for(int i = 0; i < dzialania->size(); ++i)
	{
		przyciski.push_back(new MyButton(dzialania->at(i).first));
		przyciski.back()->setText(dzialania->at(i).second);
		uklad->addWidget(przyciski.back());
		connect(przyciski.back(), SIGNAL(kliknietyID(int)), this, SLOT(kliknietoPrzycisk(int)));
	}

	qDebug() << "Panel Akcji wyswietlil zadane akcje";
}

void ActionPanel::setGameMaster(GameMaster *gameMaster)
{
	this->gameMaster_ = gameMaster;
}

/**
 * @brief PanelAkcji::kliknietoPrzycisk Zgłasza mistrzowi gry, że pewien przycisk został kliknięty.
 * @param n
 */
void ActionPanel::kliknietoPrzycisk(int n)
{
	gameMaster_->selectedAction(n);
}

/**
 * @brief PanelAkcji::wyczyscPanel	Usuwa wszystkie przyciski z panelu.
 */
void ActionPanel::wyczyscPanel()
{
	for(int i = 0; i < przyciski.size(); ++i)
	{
		uklad->removeWidget(przyciski[i]);
		delete przyciski[i];
	}
	przyciski.clear();
	delete uklad;
}
