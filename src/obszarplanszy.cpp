#include "obszarplanszy.h"

ObszarPlanszy::ObszarPlanszy()
{
	bokHexa = POCZATKOWY_ROZMIAR_HEXA;

	ticTac = new QTimeLine(CZAS_TRWANIA_JEDNEGO_PRZEJSCIA, this);
	ticTac->setFrameRange(0,100);
	connect(ticTac, SIGNAL(frameChanged(int)), this, SLOT(krokAnimacji(int)));
	connect(ticTac, SIGNAL(finished()),this, SLOT(kolejnePrzejscie()));
}

void ObszarPlanszy::setPlansza(Plansza *plansza)
{
	this->plansza = plansza;
}

/**
 * @brief ObszarPlanszy::narysujPlansze Rysuje plansze na ekranie
 * @param pola lista pól planszy
 * @param kolumny ilość kolumn planszy
 * @param wiersze ilość wierszy planszy
 * @param pozycjeGraczy mapa, w której każdemu kolorowi gracza przypisana jest jego pozycja
 */
void ObszarPlanszy::narysujPlansze(QList<Pole *> *pola, int kolumny, int wiersze, QList<QPair<QColor, IDPola> > *pozycjeGraczy)
{
	this->pola = pola;
	this->wiersze = wiersze;
	this->kolumny = kolumny;
	this->pozycjeGraczy = pozycjeGraczy;
	setBackgroundBrush(QBrush(Qt::black));
	setSceneRect(podajOgraniczenie());

	for(int i = 0; i < pola->size(); ++i)
	{
		hexy.push_back(new Hex(pola->at(i), bokHexa, this));
		addItem(hexy.at(i));
	}

	for(int i = 0; i < pozycjeGraczy->size(); ++i)
	{
		pionki.push_back(new Pionek(pozycjeGraczy->at(i).first, podajSrodekPionka(i), bokHexa / 2));
		addItem(pionki.at(i));
	}
}

/**
 * @brief ObszarPlanszy::kliknietoHex Informuje planszę o kliknięciu na hex
 * @param id
 */
void ObszarPlanszy::kliknietoHex(IDPola id)
{
	plansza->kliknietoHex(id);
}

/**
 * @brief ObszarPlanszy::wykonajRuch Zmienia potrzedne zmienne i zaczyna wykonywanie animowanego ruchu.
 * @param droga Lista poł po których pionek ma się poruszać.
 * @param indeks indeks gracza, który wykonuje ruch.
 */
void ObszarPlanszy::wykonajRuch(QList<IDPola> droga, int indeks)
{
	qDebug() <<"ruch; droga; " <<droga.size();
	doAnimacji = droga;
	indeksAnimowanego = indeks;

	while(!podswietlone.isEmpty())
	{
		hexy[podswietlone.back()]->setPodswietlenie(false);
		podswietlone.pop_back();
	}

	kolejnePrzejscie();
}

/**
 * @brief ObszarPlanszy::podswietl Podświetla zadane pola.
 * @param lista
 */
void ObszarPlanszy::podswietl(QList<IDPola> lista)
{
	while(!podswietlone.isEmpty())
	{
		hexy[podswietlone.back()]->setPodswietlenie(false);
		podswietlone.pop_back();
	}

	for(int i = 0; i < lista.size(); ++i)
	{
		hexy[lista[i].y * kolumny + lista[i].x]->setPodswietlenie(true);
		hexy[lista[i].y * kolumny + lista[i].x]->update();
		podswietlone.push_back(lista[i].y * kolumny + lista[i].x);
	}
}

/**
 * @brief ObszarPlanszy::animacjaTrwa Informuje czy trwa animacja. Z myślą o wykonywaniu akcji przez mistrza gry.
 * @return
 */
bool ObszarPlanszy::animacjaTrwa()
{
	return ticTac->state() == QTimeLine::Running;
}

/**
 * @brief ObszarPlanszy::podajOgraniczenie Na podstawie ilości hexów w kolumnach i wierszach oraz długości boku hexa zwraca najmniejszy prostokąt, w którym zawiera się cała plansza.
 * @param wiersze
 * @param kolumny
 * @param bokHexa
 * @return
 */
QRectF ObszarPlanszy::podajOgraniczenie()
{
	qreal szerokoscSceny = kolumny * podajWysokosc(bokHexa) * 2;
	if (wiersze > 1)
		szerokoscSceny += podajWysokosc(bokHexa);
	qreal wysokoscSceny = 2 * bokHexa + (wiersze - 1) * 1.5 * bokHexa;
	return QRectF(0,0, szerokoscSceny, wysokoscSceny);
}

/**
 * @brief ObszarPlanszy::podajSrodekPionka Na podstawie listy pozycjeGraczy, podaje gdzie powinien stać pionek.
 * @param indeks indeks gracza na liscie "pozycjeGraczy"
 * @param bok bok Hexa
 * @return
 */
QPointF ObszarPlanszy::podajSrodekPionka(int indeks)
{
	QPointF srodek = podajSrodek(pozycjeGraczy->at(indeks).second, bokHexa);
	if(indeks >= LICZBA_PRZEWIDZIANYCH_MODYFIKATOROW)
		return srodek;

	int liczbaUstawionych = 0;  //liczba innych pionków już ustawionych na danym polu
	IDPola pole = pozycjeGraczy->at(indeks).second;
	for(int i = 0; i <indeks; ++i)
		if(pozycjeGraczy->at(i).second.x == pole.x && pozycjeGraczy->at(i).second.y == pole.y)
			++liczbaUstawionych;

	QPointF przesuniecie(MODYFIKATORY_POZYCJI[liczbaUstawionych].x * bokHexa / 4,
			     MODYFIKATORY_POZYCJI[liczbaUstawionych].y * bokHexa / 4);
	return srodek + przesuniecie;
}

/**
 * @brief ObszarPlanszy::podajSrodek Na podstawie długości boku i współrzędnych pola podaje jego środek.
 * @param id współrzędne pola
 * @param bok środek pola
 * @return jeśli dane są poprawne, zwraca środek, w przeciwnym razie punkt (-1,-1)
 */
QPointF ObszarPlanszy::podajSrodek(const IDPola id, const qreal bok)
{
	if(bok < 0 || id.x < 0 || id.y < 0)
		return QPointF(-1,-1);
	qreal wysokosc = podajWysokosc(bok);
	QPointF srodek = QPointF(wysokosc * (1 + 2 * id.x), bok *(1 + 1.5 * id.y));
	if(id.y % 2 == 1) //przesunięcie co drugiego wiersza nieco w prawo
		srodek.setX(srodek.x() + wysokosc);
	return srodek;
}

/**
 * @brief ObszarPlanszy::podajWysokosc Zwraca wysokość trójkąta równobocznego
 * @param bok bok trójkąta
 * @return wysokość trójkąta równobocznego, lub 0, jeśli bok jest ujemny.
 */
qreal ObszarPlanszy::podajWysokosc(qreal bok)
{
	if(bok < 0)
		return 0;
	return bok * qSqrt(3)/ 2;
}

/**
* @brief ObszarPlanszy::zmienRozmiar Zmienia rozmiar planszy o d punktów, jeśli tylko nie przekroczy przez to minimalnego lub maksymalnego rozmiaru.
* @param d
*/
void ObszarPlanszy::zmienRozmiar(int d)
{
	if(bokHexa + d < MINIMALNY_ROZMIAR_HEXA || bokHexa + d > MAKSYMALNY_ROZMIAR_HEXA)
		return;
	this->bokHexa+= d;

	for(int i = 0; i < hexy.size(); ++i)
		hexy.at(i)->setBok(bokHexa);

	for(int i = 0; i < pionki.size(); ++i)
	{
		pionki.at(i)->setPromien(bokHexa / 2);
		pionki.at(i)->setPos(podajSrodekPionka(i));
	}

	setSceneRect(podajOgraniczenie());
	update();
}

/**
 * @brief ObszarPlanszy::keyReleaseEvent Obsługuje skróty klawiszowe odpowiedzialne za manipulacje rozmiarem planszy
 * @param event
 */
void ObszarPlanszy::keyReleaseEvent(QKeyEvent *event)
{
	switch(event->key()){
	case Qt::Key_Minus:
		if(event->modifiers() == Qt::CTRL)
			zmienRozmiar(-5);
		break;
	case Qt::Key_Equal:
		if(event->modifiers() == Qt::CTRL )
			zmienRozmiar(5);
		break;
	case Qt::Key_0:
		if(event->modifiers() == Qt::CTRL)
			zmienRozmiar(POCZATKOWY_ROZMIAR_HEXA - bokHexa);
		break;
	}
}

/**
 * @brief ObszarPlanszy::kolejnePrzejscie Wykonuje animowane przejscie na sąsiadujące pole.
 */
void ObszarPlanszy::kolejnePrzejscie()
{
	qDebug() <<"wywolanie";
	if(doAnimacji.empty())
	{
		for(int i = 0; i < pionki.size(); ++i)
			pionki[i]->setPos(podajSrodekPionka(i));
		return;
	}

	poczatekAnimacji = pionki[indeksAnimowanego]->pos();

	pozycjeGraczy->insert(indeksAnimowanego, QPair<QColor, IDPola>(pozycjeGraczy->at(indeksAnimowanego).first, doAnimacji.back())); //dodaje animowanego gracza do listy pozycji
	pozycjeGraczy->removeAt(indeksAnimowanego + 1); //usuwam jego stary wpis

	koniecAnimacji = podajSrodekPionka(indeksAnimowanego); //ustawiam nowy cel

	doAnimacji.pop_back();
	ticTac->start();
}

/**
 * @brief ObszarPlanszy::krokAnimacji Przesuwa pionek nad planszą na podstawie fazy animacji
 * @param faza faza animacji
 */
void ObszarPlanszy::krokAnimacji(int faza)
{
	qreal posX = poczatekAnimacji.x() + (koniecAnimacji.x() - poczatekAnimacji.x()) * faza / 100;
	qreal posY = poczatekAnimacji.y() + (koniecAnimacji.y() - poczatekAnimacji.y()) * faza / 100;

	pionki[indeksAnimowanego]->setPos(posX, posY);
}
