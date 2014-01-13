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

#include "Core/Containers/Player.h"
#include "Core/Operations/QuestManagement.h"

/**
 * @brief wygenerujOpis		Generuje opis dla podanego zadania.
 * @param zadanie
 * @param miejsce	QTextBrowser którego tekst ma zostać podmieniony na wygenerowany opis.
 */
void generateDescription(Quest *quest, QTextBrowser *target)
{
	target->clear();

	QString returnRequired = quest->isReturnRequired() ? "Tak" : "Nie";
	Prize *prize = quest->prize();

	//TODO color title acording to quest level
	target->setFontWeight(QFont::Bold);
	target->insertPlainText(quest->title() + QString("\n\n"));
	target->setFontWeight(QFont::Normal);

	QString description;
	description += quest->description() + QString("\n\n");
	description += QString::fromUtf8("Czy wymagany jest powrót?: ") + returnRequired + QString("\n\n");
	description += QString::fromUtf8("Liczba przeciwników do pokonania: ") + QString::number(quest->enemies()->size()) + QString("\n\n");

	QString fraction = "Zadanie neutralne";
	if (quest->fraction() != -1)
		fraction = KingdomString[quest->fraction()];

	description += QString::fromUtf8("Frakcja zlecająca: ") + fraction + QString("\n\n");
	description += QString("Opis nagrody:\n\n");

	if (prize->experience() != 0)
		description += QString::fromUtf8("Szacowane doświadczenie: ") + QString::number(prize->experience());

	if (prize->gold() != 0)
		description += QString::fromUtf8("\n\nZłoto do zdobycia: ") + QString::number(prize->gold()) + QString("\n\n");

	for (int i = 0; i < KingdomCount; ++i) {
		int reputationChange = prize->reputation()[i];
		if (reputationChange > 0)
			description += QString("+");
		if (reputationChange < 0)
			description += QString("-");
		if (reputationChange != 0)
			description += QString("%1 reputacja (%2)\n").arg(reputationChange).arg(KingdomString[i]);
	}

	target->insertPlainText(description);
}
