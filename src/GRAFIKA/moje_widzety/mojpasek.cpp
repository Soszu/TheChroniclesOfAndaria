#include "mojpasek.h"

/**
 * @brief MojPasek::MojPasek Tworzy poziomy pasek ustalonego koloru c. O jego wypełnieniu decyduje wartość d.
 * @param d Wartość z przedziału [0; 1] mówiąca jaką część paska należy wypełnić. Jeśli d > 1 - pasek jest zapełniony; d < 0 - pasek pusty.
 * @param c kolor wypełnienia
 */
MojPasek::MojPasek(qreal d, QColor c)
{
	szerokosc = DLUGOSC_MINIMUM;
	czyPodzialka = false;
	czy2skladowe = false;
	dlPierwsza = d;
	dlDruga = 0;
	kolorPierwszy = c;
	kolorDrugi = c;

	if(dlPierwsza < 0)
		dlPierwsza = 0;
	if(dlPierwsza > 1)
		dlPierwsza = 1;
}

/**
 * @brief MojPasek::MojPasek Tworzy poziomy pasek wypełniony po części kolorem c1 oraz c2. O jego wypełnieniu decyduje wartość d1 i d2.
 * @param d1 Wartość z przedziału [0; 1] mówiąca jaką część paska należy wypełnić kolorem c1. Jeśli d1 + d2 > 1 - pasek jest zapełniony; d1 + d2 < 0 - pasek pusty.
 * @param d2 Wartość z przedziału [0; 1] mówiąca jaką część paska należy wypełnić kolorem c2. Jeśli d1 + d2 > 1 - pasek jest zapełniony; d1 + d2 < 0 - pasek pusty.
 * @param c1 Kolor pierwszej części paska.
 * @param c2 Kolor drugiej części paska.
 */
MojPasek::MojPasek(qreal d1, qreal d2, QColor c1, QColor c2)
{
	szerokosc = DLUGOSC_MINIMUM;
	czy2skladowe = true;
	czyPodzialka = false;
	dlPierwsza = d1;
	dlDruga = d2;
	kolorPierwszy = c1;
	kolorDrugi = c2;

	dlPierwsza = sprawdzWartosc(d1, 0, 1);
	dlDruga = sprawdzWartosc(d2, 0, 1);
	if(dlPierwsza + dlDruga > 1)
		dlDruga = 1 - dlPierwsza;

}

/**
 * @brief MojPasek::MojPasek tworzy pionowy pasek mieszczący n znaczników koloru c, gdzie p już wstawiono.
 * @param n Maksymalna liczba znaczników.
 * @param p Liczba początkowo wstawionych znaczników.
 * @param c Kolor znaczników.
 */
MojPasek::MojPasek(int n, int p, QColor c)
{
	szerokosc = DLUGOSC_MINIMUM;
	czyPodzialka = true;
	czy2skladowe = false;
	limitZnacznikow = n;
	liczbaZnacznikow = p;
	kolorPierwszy = c;
}

/**
 * @brief MojPasek::wypelnij Jeśli wybrany pasek to pojedyńcze poziome wypełnienie, zmienia wartość wypełnienia.
 * @param newD nowa wartość wypełnienia (jego poprawność jest sprawdzana)
 */
void MojPasek::wypelnij(qreal newD)
{
	if(!czyPodzialka && !czy2skladowe)
	{
		dlPierwsza = sprawdzWartosc(newD, 0, 1);
		this->update();
	}
}

/**
 * @brief MojPasek::wypelnijPierwszy Jeśli wybrany pasek to podwójne poziome wypełnienia, zmienia wartość pierwszej jego części.
 * @param newD nowa wartość wypełnienia (jego poprawność jest sprawdzana)
 */
void MojPasek::wypelnijPierwszy(qreal newD)
{
	if(!czyPodzialka && czy2skladowe)
	{
		dlPierwsza = sprawdzWartosc(newD, 0, 1);
		if(dlPierwsza + dlDruga > 1)
			dlDruga = 1 - dlPierwsza;
		this->update();
	}
}

/**
 * @brief MojPasek::wypelnijDrugi Jeśli wybrany pasek to podwójne poziome wypełnienia, zmienia wartość drugiej jego części.
 * @param newD nowa wartość wypełnienia (jego poprawność jest sprawdzana)
 */
void MojPasek::wypelnijDrugi(qreal newD)
{
	if(!czyPodzialka && czy2skladowe)
	{
		dlDruga = sprawdzWartosc(newD, 0, 1);
		if(dlPierwsza + dlDruga > 1)
			dlDruga = 1 - dlPierwsza;
		this->update();
	}
}

/**
 * @brief MojPasek::ustaw Ustawia liczbę wyświetlonych znaczników na a
 * @param a
 */
void MojPasek::ustaw(int a)
{
	if(czyPodzialka && liczbaZnacznikow != a)
	{
		liczbaZnacznikow = a;
		update();
	}
}

/**
 * @brief MojPasek::sizeHint zwraca wymiary paska.
 * @return Wymiary paska.
 */
QSize MojPasek::sizeHint()
{
	return QSize(szerokosc, GRUBOSC);
}

/**
 * @brief MojPasek::minimumSizeHint Zależnie od rodzaju paska zwraca minimalny jego rozmiar.
 * @return Minimalny rozmiar paska.
 */
QSize MojPasek::minimumSizeHint()
{
	return QSize(DLUGOSC_MINIMUM, GRUBOSC);
}

/**
 * @brief MojPasek::paintEvent Metoda pozwalająca widgetowi się narysować.
 * @param e
 */
void MojPasek::paintEvent(QPaintEvent *e)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	if(czyPodzialka)
	{
		QPainterPath path1;
		qreal delta = (qreal) szerokosc / limitZnacznikow;
		path1.addRoundRect(0,0,delta * liczbaZnacznikow, GRUBOSC,25,25);
		painter.fillPath(path1, kolorPierwszy);

		for(int i = 0; i < limitZnacznikow - 1; ++i)
			painter.drawLine(delta * (i + 1), 0, delta * (i + 1), GRUBOSC / 2 );
	}
	else
	{
		if(czy2skladowe)
		{

			QPainterPath path2;
			path2.addRoundRect(0, 0, szerokosc * (dlPierwsza + dlDruga), GRUBOSC, 40,40);
			painter.fillPath(path2, QBrush(kolorDrugi, Qt::Dense3Pattern));

			QPainterPath path1;
			path1.addRoundRect(0,0,szerokosc * dlPierwsza, GRUBOSC,25, 25);
			painter.fillPath(path1, kolorPierwszy);
		}
		else
		{
			QPainterPath path1;
			path1.addRoundRect(0,0,szerokosc * dlPierwsza, GRUBOSC,25,25);
			painter.fillPath(path1, kolorPierwszy);
		}
	}

	painter.setPen(Qt::black);
	painter.drawRoundRect(QRect(0,0,szerokosc, GRUBOSC), 25, 25);
}
/**
 * @brief MojPasek::sprawdzWartosc Sprawdza czy podana liczba należy do zadanego przedziału.
 * @param x zadana wartość
 * @param a początek przedziału
 * @param b koniec przedziału
 * @return Jeśli x leży przed przedziałem zwraca jego początek, jeśli za nim, to jego koniec. Jeśli x należy do przedziału zwraca x.
 */
qreal MojPasek::sprawdzWartosc(qreal x, qreal a, qreal b)
{
	if(x < a)
		return a;
	if(x > b)
		return b;
	return x;
}

