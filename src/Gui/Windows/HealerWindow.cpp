/*
Copyright (C) 2013 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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

#include "Gui/Windows/HealerWindow.h"

HealerWindow::HealerWindow(Player *player, PlayerWindow *playerWindow)
	: player_(player), playerWindow_(playerWindow)
{
	wounds = player->healthMax() - player->healthCurrent();
	int maxCost = qMin((int)player->gold(), qCeil((qreal)wounds / HealingPerGoldPiece));

	this->setWindowTitle("Dom uzdrowiciela");
	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	QHBoxLayout *sliderLayout = new QHBoxLayout();
	QHBoxLayout *buttonsLayout = new QHBoxLayout();

	QLabel *description = new QLabel(QString::fromUtf8("Jesteś w domu uzdrowiciela, który może uleczyć Twoje rany.  \nMusisz jednak zapłacić za jego pracę i medykamenty. "));

	decisionLabel = new QLabel();

	slider = new QSlider(Qt::Horizontal);
	slider->setToolTip(QString::fromUtf8("Przesuń suwak, aby zmienić warunki leczenia."));
	slider->setRange(0, maxCost);
	connect(slider, SIGNAL(valueChanged(int)), this, SLOT(updateDecision(int)));
	slider->setValue(0);
	updateDecision(0);

	if (maxCost == 0) {
		slider->setEnabled(false);
		decisionLabel->setEnabled(false);
	}

	QPushButton *cancelButton = new QPushButton("Anuluj", this);
	cancelButton->setToolTip(QString::fromUtf8("Zrezygnuj z jakiejkolwiej pomocy."));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));

	QPushButton *confirmButton = new QPushButton("OK", this);
	confirmButton->setToolTip(QString::fromUtf8("Poproś o uzdrowienie zgodnie z ustaleniami."));
	connect(confirmButton, SIGNAL(clicked()), this, SLOT(confirm()));

	mainLayout->addWidget(description);
	mainLayout->addLayout(sliderLayout);
	mainLayout->addLayout(buttonsLayout);

	sliderLayout->addWidget(slider);
	sliderLayout->addWidget(decisionLabel);

	buttonsLayout->addStretch();
	buttonsLayout->addWidget(cancelButton);
	buttonsLayout->addWidget(confirmButton);
}

void HealerWindow::confirm()
{
	player_->setHealthCurrent(healthAfterHealing);
	player_->setGold(player_->gold() - slider->value());
	playerWindow_->displayPlayer(player_);
	this->close();
}

void HealerWindow::updateDecision(int goldPaid)
{
	int toHeal = player_->healthCurrent() + HealingPerGoldPiece * goldPaid;
	healthAfterHealing = qMin(player_->healthMax(), toHeal);

	QString text = QString::fromUtf8("Koszt w złocie: ");
	text += QString::number(goldPaid);

	text += QString("\nZdrowie po leczeniu: ");
	text += QString::number(healthAfterHealing);
	text += QString("/");
	text += QString::number(player_->healthMax());

	decisionLabel->setText(text);
}
