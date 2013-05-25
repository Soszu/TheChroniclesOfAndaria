#include "hex.h"

Hex::Hex(Pole* pole, qreal bok, ObszarPlanszy* obszar)
{
	this->bok = bok;
	this->obszarPlanszy = obszar;
	this->wysokosc = ObszarPlanszy::podajWysokosc(bok);
	this->pole = pole;
	setPos(ObszarPlanszy::podajSrodek(pole->getMiejsce(), bok));
	this->podswietlenie = false;
}

/**
 * @brief Hex::boundingRect Zwraca prostokąt, stanowiący granice hexa.
 * @return
 */
QRectF Hex::boundingRect() const
{
	QPointF poczatek(-wysokosc,-bok);
	QSizeF wymiary(2 * wysokosc, 2 * bok);
	return QRectF(poczatek, wymiary);
}

/**
 * @brief Hex::shape Zwraca dokładne ograniczenie hexa, sześciąkąt foremny, który zawiera hex
 * @return QPainterPath z ograniczeniem hexa
 */
QPainterPath Hex::shape()
{
	QPainterPath figura;
	figura.addPolygon(QPolygonF(podajWierzcholki()));
	return figura;
}

/**
 * @brief Hex::paint Rysuje hex.
 * @param painter
 * @param option
 * @param widget
 */
void Hex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setRenderHint(QPainter::SmoothPixmapTransform);
	painter->drawImage(boundingRect(), QImage(QString(":/hexy/" + pole->getPlikZObrazkiem())));
	if(pole->getCzyPoleZPrzeciwnikiem())
	{
		QPointF przesuniecie( wysokosc * 0.7, bok * 0.3); //przesuniecie symbolu miecza względem początku
		QRectF ograniczenieSymbolu(boundingRect().topLeft() + przesuniecie, boundingRect().size() * 0.3);

		painter->drawImage(ograniczenieSymbolu, QImage(QString(":/hexy/symbol.png")));
	}
	if(pole->getNazwa() != "")
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
		painter->fillPath(shape(),QBrush(Qt::white, Qt::Dense7Pattern));
}

void Hex::setBok(qreal bok)
{
	this->bok = bok;
	this->wysokosc = ObszarPlanszy::podajWysokosc(bok);
	setPos(ObszarPlanszy::podajSrodek(pole->getMiejsce(), bok));
}

void Hex::setPodswietlenie(bool opcja)
{
	this->podswietlenie = opcja;
	update(boundingRect());
}

/**
 * @brief Hex::podajWierzcholki Zwraca wierzchołki hexa.
 * @return QVector wierzchołków hexa
 */
QVector<QPointF> Hex::podajWierzcholki()
{
	QVector<QPointF> wierzcholki;
	wierzcholki << QPointF(0, -bok) << QPointF(wysokosc,  -bok / 2) << QPointF( wysokosc, bok / 2)
		    << QPointF(0, bok ) << QPointF(-wysokosc, bok /2) <<QPointF(-wysokosc, -bok/2);
	return wierzcholki;
}

/**
 * @brief Hex::mousePressEvent Informuje o kliknięciu na siebie
 * @param event
 */
void Hex::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	obszarPlanszy->kliknietoHex(pole->getMiejsce());
}
