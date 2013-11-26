#include "Gui/Elements/PlayerMarker.h"

PlayerMarker::PlayerMarker(QColor color, QString description, QPointF srodek, qreal radius)
	: color_(color), radius_(radius)
{
	setPos(srodek);
	this->setToolTip(description);
}

/**
 * @brief Pionek::boundingRect Zwraca ograniczenie pionka.
 * @return najmniejszy prostokąt zawierający pionek
 */
QRectF PlayerMarker::boundingRect() const
{
	QPointF origin(-radius_, -radius_);
	QSizeF size(2 * radius_, 2 * radius_);
	return QRectF(origin, size);
}

void PlayerMarker::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setRenderHint(QPainter::Antialiasing);
	QRadialGradient radialGradient(QPointF(0,0), radius_);
	radialGradient.setColorAt(0, Qt::white);
	radialGradient.setColorAt(1, color_);
	painter->setBrush(QBrush(radialGradient));
	painter->setPen(color_);
	painter->drawEllipse(QPointF(0,0), radius_, radius_);
}

void PlayerMarker::setRadius(qreal radius)
{
	this->radius_ = radius;
}
