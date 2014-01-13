/**
Copyright (C) 2013 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
This file is part of The Chronicles Of Andaria Project.

	The Chronicles of Andaria Project is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	The Chronicles of Andaria Project is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with The Chronicles Of Andaria.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Core/Parsers/BoardParser.h"

BoardParser::BoardParser(Board* plansza)
{
	bylBlad = false;
	this->plansza = plansza;
	QFile ustawienie(PLIK_USTAWIENIA_PLANSZY);

	if(!ustawienie.open(QIODevice::ReadOnly))
	{
		trescBledu = QString::fromUtf8("Nie udało się wczytać pliku.");
		bylBlad = true;
		return;
	}
	QTextStream wejscie(&ustawienie);

	bylBlad = wczytajWymiary(&wejscie);
	if(!bylBlad)
		bylBlad = wczytajLegende(&wejscie);
	if(!bylBlad)
		bylBlad = wczytajUstawienie(&wejscie);

	if(!bylBlad && !nastepny(&wejscie).isEmpty())
	{
		trescBledu = QString::fromUtf8("Plik wejściowy jest za długi.");
		bylBlad = true;
	}
	ustawienie.close();
}

/**
 * @brief BoardParser::bladWczytywania Zwraca, czy pojawił się jakiś błąd przy wczytywaniu układu
 * @return true pojawił się błąd, false w przeciwnym wypadku
 */
bool BoardParser::bladWczytywania()
{
	return bylBlad;
}

/**
 * @brief BoardParser::wczytajWymiary	Wczytuje wymiary planszy, znajdujące się w pierwszej linijce
 * @param wejscie	QTextStream, z którego odczytywane są dane
 * @return		true, jeśli wystąpił błąd, false w p.p.
 */
bool BoardParser::wczytajWymiary(QTextStream* wejscie)
{
	QString linia = nastepny(wejscie);

	QStringList podzial = linia.split(";");
	if(podzial.size() != 2)
	{
		trescBledu = QString::fromUtf8("Wystąpił błąd przy wczytaniu wymiarów");
		return true;
	}

	bool ok1 = true;
	bool ok2 = true;
	szerokosc = podzial.at(0).toUInt(&ok1);
	plansza->boardWidth_ = szerokosc;
	wysokosc = podzial.at(1).toUInt(&ok2);
	plansza->boardHeight_ = wysokosc;
	if(!ok1 || !ok2 || szerokosc < 1 || wysokosc < 1)
	{
		trescBledu = QString::fromUtf8("Podane wymiary nie są poprawne.");
		return true;
	}
	return false;
}

/**
 * @brief BoardParser::wczytajLegende		Wczytuje legendę zawierającą symbole hexów
 * @param wejscie	QTextStream, z którego odczytywane są dane
 * @return		true, jeśli wystąpił błąd, false w p.p.
 */
bool BoardParser::wczytajLegende(QTextStream* wejscie)
{
	bool ok = true;
	int dlLegendy = nastepny(wejscie).toInt(&ok);

	if(!ok)
	{
		trescBledu = QString::fromUtf8("Wystąpił błąd przy wczytywaniu długości legendy");
		return true;
	}

	for(int i = 0; i < dlLegendy; ++i)
	{
		QString linia = nastepny(wejscie);
		QStringList podzial = linia.split(";");

		if(podzial.size() != 7)
		{
			trescBledu = QString::fromUtf8("Wystąpił błąd przy wczytywaniu legendy.\nZła ilość pol. Wadliwy element: ") + QString::number(i + 1);
			return true;
		}

		bool bezBledu = true;
		bool bezBledu2 = true;
		info informacje;
		informacje.name = podzial.at(1);
		informacje.plik = podzial.at(2);
		informacje.wspolczynnik = podzial.at(5).toInt(&bezBledu);
		informacje.frakcja = podzial.at(6).toInt(&bezBledu2);

		if(podzial.at(3) == "1")
			informacje.czyPoleZEnemyiem = true;
		else if(podzial.at(3) == "0")
			informacje.czyPoleZEnemyiem = false;
		else bezBledu = false;

		if(podzial.at(4) == "1")
			informacje.czyPoleZMiastem = true;
		else if(podzial.at(4) == "0")
			informacje.czyPoleZMiastem = false;
		else bezBledu = false;

		if(!bezBledu || !bezBledu2 || podzial.at(0).isEmpty())
		{
			trescBledu = QString::fromUtf8("Wystąpił błąd przy wczytywaniu legendy.\nZły element: ") + QString::number(i + 1);
			return true;
		}
		legenda.insert(podzial.at(0), informacje);
	}
	return false;
}

/**
 * @brief BoardParser::wczytajUstawienie	Wczytuje ustawienie planszy
 *						zgodnie z wcześniej wczytaną legendą i wymiarami.
 * @param wejscie	QTextStream, z którego odczytywane są dane
 * @return		true, jeśli wystąpił błąd, false w p.p.
 */
bool BoardParser::wczytajUstawienie(QTextStream* wejscie)
{
	QList<Field*>* listaPol = new QList<Field*>;

	for(int i = 0; i < wysokosc; ++i)
	{
		QString linia = nastepny(wejscie);
		QStringList podzial = linia.split(";");
		if(podzial.size() != szerokosc)
		{
			trescBledu = QString::fromUtf8("Wystąpił błąd przy wczytywaniu odwzorowania.\nZła ilosc danych. Wadliwy wiersz: ") + QString::number(i + 1);
			return true;
		}
		for(int j = 0; j < szerokosc; ++j)
		{
			QString symbol = (podzial.at(j));
			symbol.remove(QChar(' '));

			if(!legenda.contains(symbol))
			{
				trescBledu = QString::fromUtf8("Wystąpił błąd przy wczytywaniu odwzorowania.\nNie znaleniono odpowiedniego symbolu.\nWadliwy wiersz: ")  + QString::number(i + 1) + QString(". Symbol: ") + symbol;
				return true;
			}
			info dane = legenda[symbol];
			FieldId miejsce = {j,i};
			listaPol->push_back(new Field(miejsce, dane.name, dane.wspolczynnik, dane.czyPoleZEnemyiem, dane.czyPoleZMiastem, dane.plik, dane.frakcja));

			if(dane.czyPoleZMiastem)
				plansza->cities_.push_back(plansza->fieldIdToIndex(miejsce));
		}
	}
	plansza->fields_ = listaPol;
	return false;
}

/**
 * @brief BoardParser::nastepny Zwraca linię z podanego strumienia, która nie jest komentarzem, oraz nie jest pusta
 * @param wejscie Strumień wejścia z danymi
 * @return QString z oczekiwaną zawartością, w przypadku błędu zwraca pusty QString
 */
QString BoardParser::nastepny(QTextStream *wejscie)
{
	while(!wejscie->atEnd())
	{
		QString tmp = wejscie->readLine();
		if( !tmp.isEmpty() && !(tmp.size() >= 2 && tmp[0] == '/' && tmp[1] == '/') )
			return tmp;
	}
	return "";
}
