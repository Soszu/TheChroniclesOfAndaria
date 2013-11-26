#ifndef MYTASKBAR_H
#define MYTASKBAR_H

#include <QtWidgets>

//TODO CFiend zmianic nazwe klasy?
//TODO CFiend ta klasa chyba probuje robic zbyt wiele jednoczesnie
class MyTaskbar : public QWidget {

public:
	MyTaskbar(qreal d, QColor c);
	MyTaskbar(qreal d1, qreal d2, QColor c1, QColor c2);
	MyTaskbar(int n, int p, QColor c);
	void fill(qreal newD);
	void fillFirst(qreal newD);
	void fillSecond(qreal newD);
	void setMarkerCount(int markerCnt);
	QSize sizeHint();
	QSize minimumSizeHint();

protected:
	void paintEvent(QPaintEvent *e);

private:
	static const int MinLength = 66;
	static const int Width = 20;

	int height_;
	int width_;
	bool markersVisible_;
	bool isTwoParted_;
	qreal firstLength_;
	qreal secondLength_;
	QColor firstColor_;
	QColor secondColor_;
	int markerCount_;
	int markerLimit_;

};

#endif
