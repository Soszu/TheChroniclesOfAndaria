#include "Gui/Elements/Tile.h"

Tile::Tile(Field *field, qreal side, BoardArea *boardArea)
	: side_(side), height_(BoardArea::calcHeight(side_)), field_(field), boardArea_(boardArea),
	highlighted_(false), selected_(false), framed_(false), tileImage_(PREFIX_HEXOW + field_->imageFile())
{
	setPos(BoardArea::calcCenter(field_->fieldId(), side_));
	setAcceptHoverEvents(true);
}

/**
 * @brief Hex::boundingRect	Zwraca prostokąt, stanowiący granice hexa.
 * @return
 */
QRectF Tile::boundingRect() const
{
	QPointF origin(-height_, -side_);
	QSizeF size(2 * height_, 2 * side_);
	return QRectF(origin, size);
}

/**
 * @brief Hex::shape	Zwraca dokładne ograniczenie hexa, sześciąkąt foremny, który zawiera hex.
 * @return		QPainterPath z ograniczeniem hexa.
 */
QPainterPath Tile::shape() const
{
	QPainterPath result;
	result.addPolygon(QPolygonF(tileVertices(1)));
	result.closeSubpath();
	return result;
}

/**
 * @brief Hex::paint	Rysuje hex.
 * @param painter
 * @param option
 * @param widget
 */
void Tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setRenderHint(QPainter::SmoothPixmapTransform);
	painter->drawImage(boundingRect(), tileImage_);

	if (field_->hasEnemy()) {
		QPointF swordShift(height_ * 0.7, side_ * 0.3);
		QRectF swordRect(boundingRect().topLeft() + swordShift, boundingRect().size() * 0.3);

		static QImage battleImage(PLIK_Z_SYMBOLEM_WALKI); //no need to read it more than once
		painter->drawImage(swordRect, battleImage);
	}

	if (field_->hasCity()) {
		QPointF textShift(0, side_ * 1.24);
		QRectF textRect(boundingRect().topLeft() + textShift, boundingRect().size());

		QFont font("OldEnglish", side_ * 0.2, QFont::Bold);
		if (field_->name().size() >= MaxSizeBeforeSqueeze)
			font.setStretch(100 * MaxSizeBeforeSqueeze / field_->name().size()); //squeeze font for long city names
		painter->setFont(font);
		painter->setPen(QPen(QColor(Qt::red)));
		painter->drawText(textRect, Qt::AlignHCenter, field_->name());
	}

	if (highlighted_)
		painter->fillPath(shape(), QBrush(Qt::gray, Qt::Dense7Pattern));

	if (framed_) {
		QPainterPath figura;
		figura.addPolygon(QPolygonF(tileVertices(0.9)));
		figura.closeSubpath();
		painter->setPen(QPen(QBrush(Qt::white), side_ / 5));
		painter->drawPath(figura);
	}

	if (selected_) {
		painter->setPen(QPen(QBrush(Qt::white), side_ / 10));
		painter->drawPath(selectionShape());
	}
}

/**
 * @brief Hex::setBok	Ustawia bok i wielkości od niego zależne, a następnie się przerysowuje
 * @param bok		długość nowego boku
 */
void Tile::setSide(qreal side)
{
	this->side_ = side;
	this->height_ = BoardArea::calcHeight(side);
	setPos(BoardArea::calcCenter(field_->fieldId(), side));
}

/**
 * @brief Hex::setPodswietlenie	Ustawia odpowiednią opcję podświetlenia, po czym się przerysowuje
 * @param opcja
 */
void Tile::setHighlighted(bool highlighted)
{
	this->highlighted_ = highlighted;
	update(boundingRect());
}

/**
 * @brief Hex::podajWierzcholki		Zwraca wierzchołki hexa.
 * @param x	modyfikator oddalenia wierzchołków od środka. 1 to standardowy rozmiar
 * @return	QVector wierzchołków hexa
 */
QVector<QPointF> Tile::tileVertices(qreal x) const
{
	QVector<QPointF> wierzcholki;
	wierzcholki << QPointF(0, -side_ * x) << QPointF(height_ * x, (-side_ / 2) * x)
	            << QPointF( height_ * x, (side_ / 2) * x) << QPointF(0, side_ * x)
	            << QPointF(-height_ * x, (side_ / 2) * x) << QPointF(-height_ * x, (-side_/ 2) * x);
	return wierzcholki;
}

/**
 * @brief Hex::zaznacz	Włącza podświetlenie danego hexa, po czym się przerysowywuje.
 */
void Tile::select()
{
	selected_ = true;
	update(boundingRect());
}

/**
 * @brief Hex::odznacz	Wyłącza podświetlenie danego hexa, po czym się przerysowywuje.
 */
void Tile::deselect()
{
	selected_ = false;
	update(boundingRect());
}

/**
 * @brief Hex::mousePressEvent	Informuje o kliknięciu na siebie
 * @param event
 */
void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	boardArea_->tileClicked(field_->fieldId());
}

void Tile::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
	//TODO: make it work
	/*
	QMenu menu;
	menu.addAction("Informacje o polu");
	if(pole->hasCity())
		menu.addAction(QString::fromUtf8("Zawartość bazaru"));
	QAction *a = menu.exec(event->screenPos());
	qDebug("User clicked %s", qPrintable(a->text()));
	*/
}

/**
 * @brief Hex::hoverEnterEvent	Informuje o wjechaniu kursorem na hex, powoduje narysowanie nad nim obramowania
 * @param event
 */
void Tile::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
	framed_ = true;
	boardArea_->displayMessage(field_->name() + ";\t koszt ruchu: " + QString::number(field_->moveCost()));
	update();
}

/**
 * @brief Hex::hoverLeaveEvent	Informuje o zjechaniu kursorem z hexa, powoduje pozbawienie go obramowania
 * @param event
 */
void Tile::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
	framed_ = false;
	update();
}

/**
 * @brief Hex::ksztaltZaznaczenia	Definuje sposób zaznaczenia hexa, reprezentowany jako QPainterPath
 * @return	ścieżka stanowiąca sposób zaznaczenia hexa.
 */
QPainterPath Tile::selectionShape()
{
	QPainterPath cross;
	cross.moveTo(QPointF(0, -side_));
	cross.lineTo(QPointF(0,  side_));
	cross.moveTo(QPointF( height_, -side_ / 2));
	cross.lineTo(QPointF(-height_,  side_ / 2));
	cross.moveTo(QPointF( height_,  side_ / 2));
	cross.lineTo(QPointF(-height_, -side_ / 2));

	return cross;
}
