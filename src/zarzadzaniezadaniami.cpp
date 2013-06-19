#include "zarzadzaniezadaniami.h"

/**
 * @brief wygenerujOpis		Generuje opis dla podanego zadania.
 * @param zadanie
 * @param miejsce	QTextBrowser którego tekst ma zostać podmieniony na wygenerowany opis.
 */
void wygenerujOpis(Zadanie* zadanie, QTextBrowser* miejsce)
{
	miejsce->clear();

	QString powrot = zadanie->getCzyPowrot() ? "Tak" : "Nie";
	Nagroda* nagroda = zadanie->getNagroda();

	miejsce->setTextColor(zadanie->getKolorCzcionki());
	miejsce->setFontWeight(QFont::Bold);
	miejsce->insertPlainText(zadanie->getTytul() + QString("\n\n"));
	miejsce->setFontWeight(QFont::Normal);
	miejsce->setTextColor(Qt::black);

	QString opis;
	opis += zadanie->getTresc() + QString("\n\n");

	opis += QString::fromUtf8("Czy wymagany jest powrót?: ") +
		powrot +
		QString("\n\n");

	opis += QString::fromUtf8("Liczba przeciwników do pokonania: ") +
		QString::number(zadanie->getPrzeciwnicy()->size()) +
		QString("\n\n");

	opis += QString("Opis nagrody:\n\n");

	if(nagroda->getDoswiadczenie() != 0)
		opis += QString::fromUtf8("Szacowane doświadczenie: ") +
			 QString::number(nagroda->getDoswiadczenie());

	if(nagroda->getZloto() != 0)
		opis += QString::fromUtf8("\n\nZłoto do zdobycia: ") +
			 QString::number(nagroda->getZloto()) +
			 QString("\n\n");

	for(int i = 0; i < LICZBA_KROLESTW; ++i)
	{
		int zmiana = nagroda->getReputacja()[i];
		if(zmiana > 0)
			opis += QString("+");
		if(zmiana < 0)
			opis += QString("-");
		if(zmiana != 0)
			opis += QString::number(zmiana) +
				 QString(" reputacja (") +
				 KROLESTWA[i] +
				 QString(")\n");
	}

	miejsce->insertPlainText(opis);
}
