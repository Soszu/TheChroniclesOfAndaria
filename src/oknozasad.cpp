#include "oknozasad.h"

OknoZasad::OknoZasad(QWidget *parent) :
	QDialog(parent)
{
	setWindowTitle("Zasady i pomoc");

	layoutGlowny = new QVBoxLayout(this);
	zakladki = new QTabWidget();

	przypomnienie = new QLabel(QString::fromUtf8("Możesz wyświetlić zasady w dowolnym momencie naciskając F1"));
	ok = new QPushButton("Ok");
	connect(ok, SIGNAL(clicked()), this, SLOT(close()));
	layoutDolny = new QHBoxLayout();
	layoutDolny->addWidget(przypomnienie);
	layoutDolny->addStretch();
	layoutDolny->addWidget(ok);

	layoutGlowny->addWidget(zakladki);
	layoutGlowny->addLayout(layoutDolny);

	ogolne = new QTextBrowser();
	zakladki->addTab(ogolne, QString::fromUtf8("ogólne"));

	ogolne->setText(QString::fromUtf8("Jest to gra typu RPG, gdzie każdy gracz posiada własną postać z określonymi statystykami i ekwipunkiem, którą rozwija przez całą rozgrywkę.\nGracz wybiera rasę i klasę dla swojej postaci, które mają wpływ na statystykę oraz ekwipunek.\nGracze kolejno w swoich turach poruszają się po planszy pomiędzy czterema królestwami, walczą z przeciwnikami lub wykonują zlecone zadania."));

	ekwipunek = new QTextBrowser();
	zakladki->addTab(ekwipunek, QString("Ekwipunek"));
	ekwipunek->setText(QString::fromUtf8("Każdy gracz dysponuje własnym ekwipunkiem, którym może zarządzać poza walką, a także handlować na bazarze w miastach.\nGracz może posiadać założony jednocześnie hełm, zdroję, broń jedno- albo dwuręczną, tarczę oraz artefakty. Tarcza nie może być używana równocześnie z bronią dwuręczną. Nie można jednocześnie nosić wiecej niż ") + QString::number(LIMIT_ARTEFAKTOW) + QString::fromUtf8(" artefaktów.\nPrzedmioty posiadają ograniczenia ze względu na klasę postaci, która miałaby go używać. Dodatkowo wiele przedmiotów jest na tyle mocnych, że gracz może ich użyć dopiero od ") + QString::number(POZIOM_GRANICZNY) + QString::fromUtf8(" poziomu. Warto zwrócić na to uwagę przed ewentualnym zakupem!/nGracz może tylko raz na turę zajrzeć na bazar.\nbonus Małej Mikstury Zdrowia: ") + QString::number(DZIALANIE_MALYCH_POTOW) + QString::fromUtf8(",\nbonus Dużej Mikstury Zdrowia: ") + QString::number(DZIALANIE_DUZYCH_POTOW));

	poruszanie = new QTextBrowser();
	zakladki->addTab(poruszanie, QString("Poruszanie"));
	poruszanie->setText(QString::fromUtf8("Gracz może raz na turę, przed skorzystaniem z opcji pola na którym stoi przesunąć swój pionek na planszy. Osiągalne pola są automatycznie podświetlane.\nKażde pole ma przypisany współczynnik poruszania się po nim. Suma współczynników przekraczanych pól nie może być większa od punktów ruchu gracza, którymi w dany momencie dysponuje.\nWspółczynniki pól:\nmiasto: 0\ndroga: 1\nrównina: 2\nlas: 2\nwoda: 3\ngóry: 3\nbagno: 4"));

	zadania = new QTextBrowser();
	zakladki->addTab(zadania, QString("Zadania"));
	zadania->setText(QString::fromUtf8("Gracz może będąc w tawernie podjąc się wykonania zadań, ale w tym samym czasie może wykonywać ich nie więcej niż ") + QString::number(MAKSYMALNA_LICZBA_ZADAN) + QString::fromUtf8(".\nZadania są jedynym źródłem reputacji. Gracz może tylko raz na turę zajrzeć do tawerny."));

	walka = new QTextBrowser();
	zakladki->addTab(walka, QString("Walka"));
	walka->setText(QString::fromUtf8("Na planszy znajdują się wyszczególnione pola z planszą, gdzie gracz może walczyć ze słabszym albo mocniejszym przeciwnikiem. Niemożliwe jest jednak skorzystanie z tego samego pola dwukrotnie w kolejnych turach. \n\nWalka to ciąg naprzemiennych ataków gracza i przeciwnika. Walka trwa, dopóki jeden z walczących nie zginie, lub gdy gracz zdecyduje się uciec.\nObrażenia zadane przez gracza to:  bazowa wartość wybranego ataku + losowa wartość z przedziału [1; ") + QString::number(KOSTKA_GRACZA) + QString::fromUtf8("] -  wartość obrony przeciwnika (obrażenia nie mogą być ujemne).\nObrażenia zadane przez przeciwnika to: losowa wartość z przedziału przypisanego do przeciwnika - wartość obrony gracza (obrażenia nie mogą być ujemne).\nPo walce następuje automatyczny koniec tury."));

	awans = new QTextBrowser();
	zakladki->addTab(awans, QString("Awans"));
	QString spisAtrybutow;
	for(int i = 0; i < LICZBA_ATRYBOTOW_DO_AWANSU; ++i)
		spisAtrybutow += MOZLIWE_AWANSE[i] + QString(", ");
	awans ->setText(QString::fromUtf8("Po zebraniu odpowiedniej ilości doświadczenia gracz awansuje na wyższy poziom. Może przy tej okazji rozdzielić ") + QString::number(LICZBA_ATRYBOTOW_DO_AWANSU) + QString::fromUtf8(" punkty atrybutów, które może przeznaczyć na zwiększenie o 1 jednego z następujących atrybutów: ") + spisAtrybutow + QString::fromUtf8(".Dodatkowo przy każdym awansie liczba maksymalnych punktów zdrowia zwiększa się o ") + QString::number(BONUS_DO_HP_PRZY_AWANSIE) + QString("."));

	koniec = new QTextBrowser();
	zakladki->addTab(koniec, QString("Koniec"));
	koniec ->setText(QString::fromUtf8("Gra kończy się, gdy w grze pozostanie tylko 1 gracz, lub gdy jeden z graczy osiągnie maksymalny ") + QString::number(MAKSYMALNY_POZIOM) + QString::fromUtf8(" poziom oraz będzie posiadał ") + QString::number(MAX_REPUTACJA) + QString::fromUtf8(" punktów reputacji w co najmniej ") + QString::number(LICZBA_POTRZEBNYCH_REPUTACJI) + QString::fromUtf8(" królestwach."));

	widok = new QTextBrowser();
	zakladki->addTab(widok, QString("Widok"));
	widok->setText(QString::fromUtf8("Skróty klawiszowe:\nCtrl + +\tPowiększenie rozmiaru planszy\nCtrl + -\tPomniejszenie rozmiaru planszy\nCtrl + 0\tPrzywrócenie domyślnego rozmiaru planszy"));
}
