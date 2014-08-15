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

#include "Core/Containers/Item.h"
#include "Core/Containers/Player.h"
#include "Game/Windows/RulesWindow.h"

RulesWindow::RulesWindow(QWidget *parent)
	: QDialog(parent)
{
	setWindowTitle("Zasady i pomoc");

	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	QTabWidget *tabWidget = new QTabWidget();

	QLabel *reminderLabel = new QLabel(QString::fromUtf8("Możesz wyświetlić zasady w dowolnym momencie naciskając F1"));
	QPushButton *confirmButton = new QPushButton("Ok");
	connect(confirmButton, SIGNAL(clicked()), this, SLOT(close()));
	QHBoxLayout *bottomLayout = new QHBoxLayout();
	bottomLayout->addWidget(reminderLabel);
	bottomLayout->addStretch();
	bottomLayout->addWidget(confirmButton);

	mainLayout->addWidget(tabWidget);
	mainLayout->addLayout(bottomLayout);

	QTextBrowser *generalHelp = new QTextBrowser();
	tabWidget->addTab(generalHelp, QString::fromUtf8("Ogólne"));

	generalHelp->setText(QString::fromUtf8("Jest to gra typu RPG, gdzie każdy gracz posiada własną postać z określonymi statystykami i ekwipunkiem, którą rozwija przez całą rozgrywkę.\nGracz wybiera rasę i klasę dla swojej postaci, które mają wpływ na statystykę oraz ekwipunek.\nGracze kolejno w swoich turach poruszają się po planszy pomiędzy czterema królestwami, walczą z przeciwnikami lub wykonują zlecone zadania. Co turę postać gracza regeneruje się (ilość regenerowanych punktów zdrowia jest podana w nawiasach obok paska zdrowia)."));

	QTextBrowser *equipmentHelp = new QTextBrowser();
	tabWidget->addTab(equipmentHelp, QString("Ekwipunek"));
	equipmentHelp->setText(QString::fromUtf8("Każdy gracz dysponuje własnym ekwipunkiem, którym może zarządzać poza walką, a także handlować na bazarze w miastach.\nGracz może posiadać założony jednocześnie hełm, zbroję, broń jedno- albo dwuręczną, tarczę oraz artefakty. Tarcza nie może być używana równocześnie z bronią dwuręczną. Nie można jednocześnie nosić wiecej niż ") + QString::number(Item::ArtifactLimit) + QString::fromUtf8(" artefaktów.\nPrzedmioty posiadają ograniczenia ze względu na klasę postaci, która miałaby go używać. Dodatkowo wiele przedmiotów jest na tyle mocnych, że gracz może ich użyć dopiero od ") + QString::number(ItemDifficultyLimit) + QString::fromUtf8(" poziomu. Warto zwrócić na to uwagę przed ewentualnym zakupem!\nGracz może tylko raz na turę zajrzeć na bazar.\nbonus Małej Mikstury Zdrowia: ") + QString::number(DZIALANIE_MALYCH_POTOW) + QString::fromUtf8(",\nbonus Dużej Mikstury Zdrowia: ") + QString::number(DZIALANIE_DUZYCH_POTOW));

	QTextBrowser *movementHelp = new QTextBrowser();
	tabWidget->addTab(movementHelp, QString("Poruszanie"));
	movementHelp->setText(QString::fromUtf8("Gracz może raz na turę, przed skorzystaniem z opcji pola na którym stoi przesunąć swój pionek na planszy. Osiągalne pola są automatycznie podświetlane.\nKażde pole ma przypisany współczynnik poruszania się po nim. Suma współczynników przekraczanych pól nie może być większa od punktów ruchu gracza, którymi w dany momencie dysponuje.\nWspółczynniki pól:\nmiasto: 0\ndroga: 1\nrównina: 2\nlas: 2\nwoda: 3\ngóry: 3\nbagno: 4"));

	QTextBrowser *questsHelp = new QTextBrowser();
	tabWidget->addTab(questsHelp, QString("Zadania"));
	questsHelp->setText(QString::fromUtf8("Gracz może będąc w tawernie podjąc się wykonania zadań, ale w tym samym czasie może wykonywać ich nie więcej niż ") + QString::number(MaximumNumberOfQuestsTaken) + QString::fromUtf8(".\nZadania są jedynym źródłem reputacji. Gracz może tylko raz na turę zajrzeć do tawerny.\n W nawiasach obok zadania podany jest orientacyjny poziom przeciwnika, z  którym przyjdzie się mierzyć lub (*) jeśli wykonanie zadania nie wymaga walki"));

	QTextBrowser *fightHelp = new QTextBrowser();
	tabWidget->addTab(fightHelp, QString("Walka"));
	fightHelp->setText(QString::fromUtf8("Na planszy znajdują się wyszczególnione pola z planszą, gdzie gracz może walczyć ze słabszym albo mocniejszym przeciwnikiem. Niemożliwe jest jednak skorzystanie z tego samego pola dwukrotnie w kolejnych turach. \n\nWalka to ciąg naprzemiennych ataków gracza i przeciwnika. Walka trwa, dopóki jeden z walczących nie zginie, lub gdy gracz zdecyduje się uciec.\nObrażenia zadane przez gracza to:  bazowa wartość wybranego ataku + losowa wartość z przedziału [1; ") + QString::number(PlayerDice) + QString::fromUtf8("] -  wartość obrony przeciwnika (obrażenia nie mogą być ujemne).\nObrażenia zadane przez przeciwnika to: losowa wartość z przedziału przypisanego do przeciwnika - wartość obrony gracza (obrażenia nie mogą być ujemne).\nPo walce następuje automatyczny koniec tury."));

	QTextBrowser *levelUpHelp = new QTextBrowser();
	tabWidget->addTab(levelUpHelp, QString("Awans"));
	QString attributesString;
	for (int i = 0; i < LICZBA_ATRYBOTOW_DO_AWANSU; ++i)
		attributesString += MOZLIWE_AWANSE[i] + QString(", ");
	levelUpHelp->setText(QString::fromUtf8("Po zebraniu odpowiedniej ilości doświadczenia gracz awansuje na wyższy poziom. Może przy tej okazji rozdzielić ") + QString::number(AttributePointsPerLevel) + QString::fromUtf8(" punkty atrybutów, które może przeznaczyć na zwiększenie o 1 jednego z następujących atrybutów: ") + attributesString + QString::fromUtf8(".Dodatkowo przy każdym awansie liczba maksymalnych punktów zdrowia zwiększa się o ") + QString::number(HealthIncreasePerLevel) + QString("."));

	QTextBrowser *endHelp = new QTextBrowser();
	tabWidget->addTab(endHelp, QString("Koniec"));
	endHelp ->setText(QString::fromUtf8("Gra kończy się, gdy w grze pozostanie tylko 1 gracz, lub gdy jeden z graczy osiągnie maksymalny ") + QString::number(MaximumLevel) + QString::fromUtf8(" poziom oraz będzie posiadał ") + QString::number(MaximumReputation) + QString::fromUtf8(" punktów reputacji w co najmniej ") + QString::number(MaximumReputationsToWin) + QString::fromUtf8(" królestwach."));
}
