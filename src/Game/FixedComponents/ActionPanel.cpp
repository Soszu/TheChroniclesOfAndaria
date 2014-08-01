/*
Copyright (C) 2013-2014 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
This file is part of The Chronicles Of Andaria Project.

	The Chronicles of Andaria Project is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	The Chronicles of Andaria Project is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with The Chronicles Of Andaria.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Game/FixedComponents/ActionPanel.h"

ActionPanel::ActionPanel(GameMaster *gameMaster)
	: gameMaster_(gameMaster), buttonLayout(new QVBoxLayout(this)), buttonMapper(new QSignalMapper(this))
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
