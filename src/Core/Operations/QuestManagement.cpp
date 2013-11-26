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

	target->setTextColor(quest->fontColor());
	target->setFontWeight(QFont::Bold);
	target->insertPlainText(quest->title() + QString("\n\n"));
	target->setFontWeight(QFont::Normal);
	target->setTextColor(Qt::black);

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
