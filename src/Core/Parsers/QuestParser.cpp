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

#include "Core/Parsers/QuestParser.h"

QuestParser::QuestParser(GameMaster *mistrz)
{
	bylBlad = false;
	this->mistrzGry = mistrz;

//plik z ustawieniami planszy i pobranie wymiarów
	QFile ustawienie(PLIK_USTAWIENIA_PLANSZY);
	if(!ustawienie.open(QIODevice::ReadOnly))
	{
		trescBledu = QString::fromUtf8("Nie udało się wczytać pliku z ustawieniem planszy.\n(w celu pobrania wymiarów)");
		bylBlad = true;
		return;
	}

	QTextStream wejscieUstawienia(&ustawienie);
	bylBlad = wczytajWymiary(&wejscieUstawienia);
	ustawienie.close();
	if(bylBlad)
		return;

//pobranie zadan
	QFile plik(PLIK_ZADAN);
	if(!plik.open(QIODevice::ReadOnly))
	{
		trescBledu = QString::fromUtf8( "Nie udało się wczytać pliku\nz danymi zadań.");
		bylBlad = true;
		return;
	}
	QTextStream wejscie(&plik);
	bylBlad = wczytajDane(&wejscie);
	plik.close();
}

/**
 * @brief QuestParser::bladWczytywania		Informuje czy wystąpił błąd podczas wczytywania
 * @return		true - jeżeli wystąpił, false, w p.p.
 */
bool QuestParser::bladWczytywania()
{
	return bylBlad;
}

/**
 * @brief QuestParser::wczytajWymiary	Wczytuje wymiary planszy, znajdujące się w pierwszej linijce pliku z układem planszy
 * @param wejscie	QTextStream, z którego odczytywane są dane
 * @return		true, jeśli wystąpił błąd, false w p.p.
 */
bool QuestParser::wczytajWymiary(QTextStream *wejscie)
{
	QString linia = nastepny(wejscie);

	QStringList podzial = linia.split(";");
	if(podzial.size() != 2)
	{
		trescBledu = QString::fromUtf8("Wystąpił błąd przy wczytaniu wymiarów.\n Zła ilość danych.");
		return true;
	}

	bool ok1 = true;
	bool ok2 = true;
	szerokoscPlanszy = podzial.at(0).toUInt(&ok1);
	wysokoscPlanszy = podzial.at(1).toUInt(&ok2);
	if(!ok1 || !ok2 || szerokoscPlanszy < 1 || wysokoscPlanszy < 1)
	{
		trescBledu = QString::fromUtf8("Podane wymiary nie są poprawne.");
		return true;
	}
	return false;
}
/**
 * @brief QuestParser::wczytajDane	Wczytuje dane zadań z podanego wejścia
 *					i informuje o ewentualnym błędzie
 * @param wejscie	QTextStream, z którego odczytywane są dane
 * @return		true - jeżeli wystąpił, false, w p.p.
 */
bool QuestParser::wczytajDane(QTextStream *wejscie)
{
	QString linia;
	int numerLinii = 1;

	while((linia = nastepny(wejscie)) != "")
	{
//-----------ILOŚĆ ARGUMENTÓW
		QStringList podzial = linia.split(";");
		if(podzial.size() != 10)
		{
			trescBledu = QString::fromUtf8( "Zła ilość pól. Wadliwa linia: ") + QString::number(numerLinii);
			return true;
		}
		QStringList pole = podzial.at(7).split(",");
		if(pole.size() != 2)
		{
			trescBledu = QString::fromUtf8( "Zła ilość współrzędnych pola.\n Wadliwa linia: ") + QString::number(numerLinii);
			return true;
		}
//-----------TEKSTY
		informacje info;
		info.tytul = podzial.at(4);
		info.tresc = podzial.at(5);

//-----------LICZBY CAŁKOWITE
		bool okID;
		bool okRodzaj;
		bool okPoziom;
		bool okFrakcja;
		bool okIDNagrody;
		bool okCelX;
		bool okCelY;
		int celX, celY;
		info.id = podzial.at(0).toInt(&okID);
		info.rodzaj = podzial.at(1).toInt(&okRodzaj);
		info.poziom = podzial.at(2).toInt(&okPoziom);
		info.frakcja = podzial.at(3).toInt(&okFrakcja);
		info.idNagrody = podzial.at(8).toInt(&okIDNagrody);
		celX = pole.at(0).toInt(&okCelX);
		celY = pole.at(1).toInt(&okCelY);

		if(!okID || !okRodzaj || !okPoziom || !okFrakcja || !okIDNagrody || !okCelX || !okCelY)
		{
			trescBledu = QString::fromUtf8("Niepoprawne dane w linii ") + QString::number(numerLinii);
			return true;
		}

		if(info.rodzaj <= 0 || info.rodzaj > LICZBA_RODZAJOW_ZADAN)
		{
			trescBledu = QString::fromUtf8("Niepoprawny rodzaj zadania w linii ") + QString::number(numerLinii);
			return true;
		}

		if(info.poziom < 0 || info.poziom >= LICZBA_POZIOMOW_ZADAN)
		{
			trescBledu = QString::fromUtf8("Niepoprawny poziom zadania w linii ") + QString::number(numerLinii);
			return true;
		}
		if (!mistrzGry->prizes_.contains(info.idNagrody))
		{
			trescBledu = QString::fromUtf8("Niepoprawne ID nagrody w linii ") + QString::number(numerLinii);
			return true;
		}
		if (info.frakcja < -1 && info.frakcja >= PlayerRaceCount)
		{
			trescBledu = QString::fromUtf8("Niepoprawna frakcja w linii ") + QString::number(numerLinii);
			return true;
		}
//-----------WARTOSCI BOOLOWSKIE
		QString powrot = podzial.at(6);
		powrot.remove(" ");
		if(powrot == "1")
			info.czyPowrot = true;
		else if(powrot == "0")
			info.czyPowrot = false;
		else
		{
			trescBledu = QString::fromUtf8("Niepoprawna wartosc \"czy Powrot\" w linii") + QString::number(numerLinii);
			return true;
		}
//-----------POPRAWNOSC CELU
		if(celX > szerokoscPlanszy || celX < 1 || celY > wysokoscPlanszy || celY <1)
		{
			trescBledu = QString::fromUtf8("Podane współrzędne nie są poprawne. Linia: ") + QString::number(numerLinii);
			return true;
		}
		//NOTE: trzeba przesunąć indeksowanie w pliku (zostało za późno doprecyzowane)
		info.cel.rx() = celX - 1;
		info.cel.ry() = celY - 1;
//-----------PRZECIWNICY
		info.idWrogow = new QList<Enemy*>;
		bool blad = false;
		if(!podzial.at(9).isEmpty())
		{
			QList<int> wartosciID;
			QStringList identyfikatory = podzial.at(9).split(",");
			for(int i = 0; i < identyfikatory.size(); ++i)
			{
				bool ok;
				wartosciID.push_back(identyfikatory.at(i).toInt(&ok));
				if(!ok)
					blad = true;
				if(blad || !mistrzGry->enemies_.contains(wartosciID.back()))
				{
					trescBledu = QString::fromUtf8("Niepoprawny identyfikator przeciwnika w linii ") + QString::number(numerLinii);
					return true;
				}
				else
					info.idWrogow->push_back(mistrzGry->enemies_[wartosciID.back()]);
			}
		}
//-----------ZAPISANIE DANYCH
		Prize *prize = mistrzGry->prizes_[info.idNagrody];
		Quest* nowy = new Quest(info.id,
		                        (QuestType)info.rodzaj,
		                        (QuestLevel)info.poziom,
		                        info.frakcja,
		                        info.tytul,
		                        info.tresc,
		                        info.czyPowrot,
		                        info.cel,
		                        prize,
		                        info.idWrogow);
		mistrzGry->quests_.insert(info.id, nowy);
		++numerLinii;
	}
	return false;
}

/**
 * @brief QuestParser::nastepny Zwraca linię z podanego strumienia, która nie jest komentarzem, oraz nie jest pusta
 * @param wejscie Strumień wejścia z danymi
 * @return QString z oczekiwaną zawartością, w przypadku błędu zwraca pusty QString
 */
QString QuestParser::nastepny(QTextStream *wejscie)
{
	while(!wejscie->atEnd())
	{
		QString tmp = wejscie->readLine();
		if( !tmp.isEmpty() && !(tmp.size() >= 2 && tmp[0] == '/' && tmp[1] == '/') )
			return tmp;
	}
	return "";
}
