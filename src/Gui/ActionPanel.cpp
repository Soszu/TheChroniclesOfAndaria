#include "Gui/ActionPanel.h"

ActionPanel::ActionPanel(GameMaster *gameMaster, QGroupBox *box)
	: gameMaster_(gameMaster), panel(box), buttonLayout(new QVBoxLayout(panel)), buttonMapper(new QSignalMapper(this))
{
	connect(buttonMapper, static_cast<void (QSignalMapper::*)(int)>(&QSignalMapper::mapped), this, &ActionPanel::executeAction);
}

/**
 * @brief PanelAkcji::wyswietl	Wyświetla Panel zgodnie z obecnymi ustawieniami
 */
void ActionPanel::displayActions(const QList <QPair <int, QString> > &actions)
{
	clearPanel();

	for (const QPair <int, QString> &action : actions) {
		QPushButton *button = new QPushButton(action.second);
		buttons.append(button);
		buttonLayout->addWidget(button);
		buttonMapper->setMapping(button, action.first);
		connect(button, &QPushButton::clicked, buttonMapper, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
	}
}

/**
 * @brief PanelAkcji::kliknietoPrzycisk Zgłasza mistrzowi gry, że pewien przycisk został kliknięty.
 * @param n
 */
void ActionPanel::executeAction(int actionId)
{
	gameMaster_->selectedAction(actionId);
}

/**
 * @brief PanelAkcji::wyczyscPanel	Usuwa wszystkie przyciski z panelu.
 */
void ActionPanel::clearPanel()
{
	for (QPushButton *button : buttons) {
		buttonMapper->removeMappings(button);
		buttonLayout->removeWidget(button);
	}

	qDeleteAll(buttons);
	buttons.clear();
}
