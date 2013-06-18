#include "pionek.h"

Pionek::Pionek(QColor kolor, QPointF srodek, qreal promien)
{
	this->kolor = kolor;
	setPos(srodek);
	this->promien = promien;
}

/**
 * @brief Pionek::boundingRect Zwraca ograniczenie pionka.
 * @return najmniejszy prostokąt zawierający pionek
 */
QRectF Pionek::boundingRect() const
{
	QPointF poczatek(-promien, -promien);
	QSizeF wymiary(2 * promien, 2 * promien);
	return QRectF(poczatek, wymiary);
}

void Pionek::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setRenderHint(QPainter::Antialiasing);
	QRadialGradient radialGradient(QPointF(0,0), promien);
	radialGradient.setColorAt(0, Qt::white);
	radialGradient.setColorAt(1, kolor);
	painter->setBrush(QBrush(radialGradient));
	painter->setPen(kolor);
	painter->drawEllipse(QPointF(0,0), promien, promien);
}

void Pionek::setPromien(qreal promien)
{
	this->promien = promien;
}
