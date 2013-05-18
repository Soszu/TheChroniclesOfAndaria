#ifndef MOJPASEK_H
#define MOJPASEK_H

#include <QWidget>
#include <QPainter>


class MojPasek : public QWidget
{
	Q_OBJECT
public:
	explicit MojPasek(qreal d, QColor c);
	explicit MojPasek(qreal d1, qreal d2, QColor c1, QColor c2);
	explicit MojPasek(int n, int p, QColor c);
	void wypelnij(qreal newD);
	void wypelnijPierwszy(qreal newD);
	void wypelnijDrugi(qreal newD);
	void ustaw(int a);
	QSize sizeHint();
	QSize minimumSizeHint();
protected:
	void paintEvent(QPaintEvent *e);
private:
	static const int DLUGOSC_MINIMUM = 100;
	static const int GRUBOSC = 20;
	qreal sprawdzWartosc(qreal x, qreal a, qreal b);
	int wysokosc;
	int szerokosc;
	bool czyPodzialka;
	bool czy2skladowe;
	qreal dlPierwsza;
	qreal dlDruga;
	QColor kolorPierwszy;
	QColor kolorDrugi;
	int liczbaZnacznikow;
	int limitZnacznikow;
signals:

public slots:

};

#endif // MOJPASEK_H
