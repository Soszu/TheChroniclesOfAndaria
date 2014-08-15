#include "Journal.h"
/*
void QuestBook::generateDescription(Quest *quest, QTextBrowser *target)
{
	target->clear();

	QString returnRequired = quest->isReturnRequired() ? "Tak" : "Nie";
	const Prize *prize = quest->prize();

	//TODO color title acording to quest level
	target->setFontWeight(QFont::Bold);
	target->insertPlainText(quest->title() + QString("\n\n"));
	target->setFontWeight(QFont::Normal);

	QString description;
	description += quest->description() + QString("\n\n");
	description += QString::fromUtf8("Czy wymagany jest powrót?: ") + returnRequired + QString("\n\n");
	description += QString::fromUtf8("Liczba przeciwników do pokonania: ") + QString::number(quest->enemiesToDefeat().size()) + QString("\n\n");

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

void GameMaster::doQuest(int questId)
{
	currentPlayer_->setHasFoughtRecently(false);
	int questIndex = 0;
	while (currentPlayer_->quest(questIndex)->id() != questId)
		++questIndex;

	Quest *quest = currentPlayer_->quest(questIndex);
	switch (quest->type()) {
		case przynies:
			if (quest->isPartiallyCompleted()) {
				grantPrize(currentPlayer_, quest->prize(), false);
				currentPlayer_->removeQuest(questId);
				determinePossibleActions();
				actionPanel_->displayActions(possibleActions_);
			} else {
				quest->setIsPartiallyCompleted(true);
				quest->setTargetField(quest->employerField());
				gameCycle_->endTurn();
			}
			break;
		case odnajdz: {
			if (quest->isPartiallyCompleted()) {
				grantPrize(currentPlayer_, quest->prize(), false);
				currentPlayer_->removeQuest(questId);
				determinePossibleActions();
				actionPanel_->displayActions(possibleActions_);
				break;
			}
			int chance = BAZOWA_SZANSA_NA_ODNALEZIENIE + currentPlayer_->perception() * BONUS_Z_PERCEPCJI;
			bool success = qrand() % 100 < chance;
			QMessageBox::information(
				gameCycle_->mainWindow(),
									 quest->title(),
									 success ?
									 QString::fromUtf8("UdaÅo Ci siÄ wykonaÄ zadanie.") :
									 QString::fromUtf8("Niestety, nie udaÅo Ci siÄ wykonaÄ zadania.")
			);

			if (success)  {
				if (quest->isReturnRequired()) {
					quest->setIsPartiallyCompleted(true);
					quest->setTargetField(quest->employerField());
				} else {
					grantPrize(currentPlayer_, quest->prize(), true);
					currentPlayer_->removeQuest(questId);
				}
			}
			gameCycle_->endTurn();
			break;
		}
		case pokonaj:
			if (quest->isPartiallyCompleted()) {
				grantPrize(currentPlayer_, quest->prize(), false);
				currentPlayer_->removeQuest(questId);
				determinePossibleActions();
				actionPanel_->displayActions(possibleActions_);
			} else {
				currentQuest_ = quest;
				startFight(QuestEnemy);
			}
			break;
	}
}
*/