#include "hex.h"

Hex::Hex(Pole* pole, qreal bok, ObszarPlanszy* obszar)
{
	this->bok = bok;
	this->obszarPlanszy = obszar;
	this->wysokosc = ObszarPlanszy::podajWysokosc(bok);
	this->pole = pole;
	setPos(ObszarPlanszy::podajSrodek(pole->getMiejsce(), bok));
	podswietlenie = false;
	zaznaczenie = false;
	obramowanie = false;
	setAcceptHoverEvents(true);
}

/**
 * @brief Hex::boundingRect	Zwraca prostokąt, stanowiący granice hexa.
 * @return
 */
QRectF Hex::boundingRect() const
{
	QPointF poczatek(-wysokosc,-bok);
	QSizeF wymiary(2 * wysokosc, 2 * bok);
	return QRectF(poczatek, wymiary);
}

/**
 * @brief Hex::shape	Zwraca dokładne ograniczenie hexa, sześciąkąt foremny, który zawiera hex.
 * @return		QPainterPath z ograniczeniem hexa.
 */
QPainterPath Hex::shape() const
{
	QPainterPath figura;
	figura.addPolygon(QPolygonF(podajWierzcholki(1)));
	figura.closeSubpath();
	return figura;
}

/**
 * @brief Hex::paint	Rysuje hex.
 * @param painter
 * @param option
 * @param widget
 */
void Hex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setRenderHint(QPainter::SmoothPixmapTransform);
	painter->drawImage(boundingRect(), QImage(PREFIX_HEXOW + pole->getPlikZObrazkiem()));
	if(pole->getCzyPoleZPrzeciwnikiem())
	{
		QPointF przesuniecie( wysokosc * 0.7, bok * 0.3); //przesuniecie symbolu miecza względem początku
		QRectF ograniczenieSymbolu(boundingRect().topLeft() + przesuniecie, boundingRect().size() * 0.3);

		painter->drawImage(ograniczenieSymbolu, QImage(PLIK_Z_SYMBOLEM_WALKI));
	}
	if(pole->getCzyPoleZMiastem())
	{
		QPointF przesuniecie(0, bok * 1.24 ); //przesuniecie symbolu miecza względem początku
		QRectF ograniczenieTekstu(boundingRect().topLeft() + przesuniecie, boundingRect().size());

		QFont czcionka("OldEnglish", bok * 0.2, QFont::Bold);
		if(pole->getNazwa().size() >= MAX_SIZE_PRZED_SCISKANIEM)
			czcionka.setStretch(100 * MAX_SIZE_PRZED_SCISKANIEM / pole->getNazwa().size()); //zmniejsza szerokość liter
		painter->setFont(czcionka);
		painter->setPen(QPen(QColor(Qt::red)));
		painter->drawText(ograniczenieTekstu, Qt::AlignHCenter, pole->getNazwa());
	}
	if(podswietlenie)
		painter->fillPath(shape(),QBrush(Qt::gray, Qt::Dense7Pattern));
	if(obramowanie)
	{
		QPainterPath figura;
		figura.addPolygon(QPolygonF(podajWierzcholki(0.9)));
		figura.closeSubpath();
		painter->setPen(QPen(QBrush(Qt::white), bok / 5));
		painter->drawPath(figura);
	}
	if(zaznaczenie)
	{
		painter->setPen(QPen(QBrush(Qt::white), bok / 10));
		painter->drawPath(ksztaltZaznaczenia());
	}
}

/**
 * @brief Hex::setBok	Ustawia bok i wielkości od niego zależne, a następnie się przerysowuje
 * @param bok		długość nowego boku
 */
void Hex::setBok(qreal bok)
{
	this->bok = bok;
	this->wysokosc = ObszarPlanszy::podajWysokosc(bok);
	setPos(ObszarPlanszy::podajSrodek(pole->getMiejsce(), bok));
}

/**
 * @brief Hex::setPodswietlenie	Ustawia odpowiednią opcję podświetlenia, po czym się przerysowuje
 * @param opcja
 */
void Hex::setPodswietlenie(bool opcja)
{
	this->podswietlenie = opcja;
	update(boundingRect());
}

/**
 * @brief Hex::podajWierzcholki		Zwraca wierzchołki hexa.
 * @param x	modyfikator oddalenia wierzchołków od środka. 1 to standardowy rozmiar
 * @return	QVector wierzchołków hexa
 */
QVector<QPointF> Hex::podajWierzcholki(qreal x) const
{
	QVector<QPointF> wierzcholki;
	wierzcholki << QPointF(0, -bok * x) << QPointF(wysokosc * x, (-bok / 2) * x)
		    <<QPointF( wysokosc * x, (bok / 2) * x) << QPointF(0, bok * x)
		   << QPointF(-wysokosc * x, (bok / 2) * x) <<QPointF(-wysokosc * x, (-bok/ 2) * x);
	return wierzcholki;
}

/**
 * @brief Hex::zaznacz	Włącza podświetlenie danego hexa, po czym się przerysowywuje.
 */
void Hex::zaznacz()
{
	zaznaczenie = true;
	update(boundingRect());
}

/**
 * @brief Hex::odznacz	Wyłącza podświetlenie danego hexa, po czym się przerysowywuje.
 */
void Hex::odznacz()
{
	zaznaczenie = false;
	update(boundingRect());
}

/**
 * @brief Hex::mousePressEvent	Informuje o kliknięciu na siebie
 * @param event
 */
void Hex::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	obszarPlanszy->kliknietoHex(pole->getMiejsce());
}

void Hex::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
	//TODO: make it work
	/*
	QMenu menu;
	menu.addAction("Informacje o polu");
	if(pole->getCzyPoleZMiastem())
		menu.addAction(QString::fromUtf8("Zawartość bazaru"));
	QAction *a = menu.exec(event->screenPos());
	qDebug("User clicked %s", qPrintable(a->text()));
	*/
}

/**
 * @brief Hex::hoverEnterEvent	Informuje o wjechaniu kursorem na hex, powoduje narysowanie nad nim obramowania
 * @param event
 */
void Hex::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
	obramowanie = true;
	obszarPlanszy->wyswietlKomunikat(pole->getNazwa() + ";\t koszt ruchu: " + QString::number(pole->getWspolczynnik()));
	update();
}

/**
 * @brief Hex::hoverLeaveEvent	Informuje o zjechaniu kursorem z hexa, powoduje pozbawienie go obramowania
 * @param event
 */
void Hex::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
	obramowanie = false;
	update();
}

/**
 * @brief Hex::ksztaltZaznaczenia	Definuje sposób zaznaczenia hexa, reprezentowany jako QPainterPath
 * @return	ścieżka stanowiąca sposób zaznaczenia hexa.
 */
QPainterPath Hex::ksztaltZaznaczenia()
{
	QPainterPath krzyz;
	krzyz.moveTo(QPointF(0, -bok));
	krzyz.lineTo(QPointF(0, bok ));
	krzyz.moveTo(QPointF(wysokosc, -bok / 2));
	krzyz.lineTo(QPointF(-wysokosc, bok /2));
	krzyz.moveTo(QPointF( wysokosc, bok / 2));
	krzyz.lineTo(QPointF(-wysokosc, -bok/2));

	return krzyz;
}
