#include "Gui/CustomWidgets/MyTaskbar.h"

/**
 * @brief MojPasek::MojPasek Tworzy poziomy pasek ustalonego koloru c. O jego wypełnieniu decyduje wartość d.
 * @param d Wartość z przedziału [0; 1] mówiąca jaką część paska należy wypełnić. Jeśli d > 1 - pasek jest zapełniony; d < 0 - pasek pusty.
 * @param c kolor wypełnienia
 */
MyTaskbar::MyTaskbar(qreal d, QColor c)
	: width_(MinLength), markersVisible_(false), isTwoParted_(false),
	  firstLength_(qBound(0.0, d, 1.0)), secondLength_(0),
	  firstColor_(c), secondColor_(c)
{
}

/**
 * @brief MojPasek::MojPasek Tworzy poziomy pasek wypełniony po części kolorem c1 oraz c2. O jego wypełnieniu decyduje wartość d1 i d2.
 * @param d1 Wartość z przedziału [0; 1] mówiąca jaką część paska należy wypełnić kolorem c1. Jeśli d1 + d2 > 1 - pasek jest zapełniony; d1 + d2 < 0 - pasek pusty.
 * @param d2 Wartość z przedziału [0; 1] mówiąca jaką część paska należy wypełnić kolorem c2. Jeśli d1 + d2 > 1 - pasek jest zapełniony; d1 + d2 < 0 - pasek pusty.
 * @param c1 Kolor pierwszej części paska.
 * @param c2 Kolor drugiej części paska.
 */
MyTaskbar::MyTaskbar(qreal d1, qreal d2, QColor c1, QColor c2)
	: width_(MinLength), markersVisible_(false), isTwoParted_(true),
	  firstLength_(qBound(0.0, d1, 1.0)), secondLength_(qBound(0.0, d2, 1.0)),
	  firstColor_(c1), secondColor_(c2)
{
	if (firstLength_ + secondLength_ > 1.0)
		secondLength_ = 1.0 - firstLength_;
}

/**
 * @brief MojPasek::MojPasek tworzy pionowy pasek mieszczący n znaczników koloru c, gdzie p już wstawiono.
 * @param n Maksymalna liczba znaczników.
 * @param p Liczba początkowo wstawionych znaczników.
 * @param c Kolor znaczników.
 */
MyTaskbar::MyTaskbar(int n, int p, QColor c)
	: width_(MinLength), markersVisible_(true), isTwoParted_(false),
	  firstColor_(c), markerCount_(p), markerLimit_(n)
{
}

/**
 * @brief MojPasek::wypelnij Jeśli wybrany pasek to pojedyńcze poziome wypełnienie, zmienia wartość wypełnienia.
 * @param newD nowa wartość wypełnienia (jego poprawność jest sprawdzana)
 */
void MyTaskbar::fill(qreal newD)
{
	if (!markersVisible_ && !isTwoParted_) {
		firstLength_ = qBound(0.0, newD, 1.0);
		this->update();
	}
}

/**
 * @brief MojPasek::wypelnijPierwszy Jeśli wybrany pasek to podwójne poziome wypełnienia, zmienia wartość pierwszej jego części.
 * @param newD nowa wartość wypełnienia (jego poprawność jest sprawdzana)
 */
void MyTaskbar::fillFirst(qreal newD)
{
	if (!markersVisible_ && isTwoParted_) {
		firstLength_ = qBound(0.0, newD, 1.0);
		if (firstLength_ + secondLength_ > 1.0)
			secondLength_ = 1.0 - firstLength_;
		this->update();
	}
}

/**
 * @brief MojPasek::wypelnijDrugi Jeśli wybrany pasek to podwójne poziome wypełnienia, zmienia wartość drugiej jego części.
 * @param newD nowa wartość wypełnienia (jego poprawność jest sprawdzana)
 */
void MyTaskbar::fillSecond(qreal newD)
{
	if(!markersVisible_ && isTwoParted_) {
		secondLength_ = qBound(0.0, newD, 1.0);
		if(firstLength_ + secondLength_ > 1.0)
			secondLength_ = 1.0 - firstLength_;
		this->update();
	}
}

/**
 * @brief MojPasek::ustaw Ustawia liczbę wyświetlonych znaczników na a
 * @param a
 */
void MyTaskbar::setMarkerCount(int markerCnt)
{
	if (markersVisible_ && markerCount_ != markerCnt) {
		markerCount_ = markerCnt;
		update();
	}
}

/**
 * @brief MojPasek::sizeHint zwraca wymiary paska.
 * @return Wymiary paska.
 */
QSize MyTaskbar::sizeHint()
{
	return QSize(width_, Width);
}

/**
 * @brief MojPasek::minimumSizeHint Zależnie od rodzaju paska zwraca minimalny jego rozmiar.
 * @return Minimalny rozmiar paska.
 */
QSize MyTaskbar::minimumSizeHint()
{
	return QSize(MinLength, Width);
}

/**
 * @brief MojPasek::paintEvent Metoda pozwalająca widgetowi się narysować.
 * @param e
 */
void MyTaskbar::paintEvent(QPaintEvent *e)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	if (markersVisible_) {
		QPainterPath path;
		qreal delta = (qreal)width_ / markerLimit_;
		path.addRoundRect(0, 0, delta * markerCount_, Width, 25, 25);
		painter.fillPath(path, firstColor_);

		for (int i = 0; i < markerLimit_ - 1; ++i)
			painter.drawLine(delta * (i + 1), 0, delta * (i + 1), Width / 2);
	} else {
		if (isTwoParted_) {
			QPainterPath secondPart;
			secondPart.addRoundRect(0, 0, width_ * (firstLength_ + secondLength_), Width, 40, 40);
			painter.fillPath(secondPart, QBrush(secondColor_, Qt::Dense3Pattern));

			QPainterPath firstPart;
			firstPart.addRoundRect(0, 0, width_ * firstLength_, Width, 25, 25);
			painter.fillPath(firstPart, firstColor_);
		} else {
			QPainterPath path;
			path.addRoundRect(0, 0, width_ * firstLength_, Width, 25, 25);
			painter.fillPath(path, firstColor_);
		}
	}

	painter.setPen(Qt::black);
	painter.drawRoundRect(QRect(0, 0, width_, Width), 25, 25);
}
