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

#include "Core/Parsers/PrizeParser.hpp"

#include "Core/Mod.hpp"
#include "Core/Paths.hpp"
#include "Core/Enums.hpp"

PrizeParser::PrizeParser(Mod *mod)
{
	bylBlad = false;
	this->mod = mod;
	QFile plik(PLIK_NAGROD);
	if(!plik.open(QIODevice::ReadOnly))
	{
		trescBledu = QString::fromUtf8( "Nie udało się wczytać pliku.");
		bylBlad = true;
		return;
	}
	QTextStream wejscie(&plik);
	bylBlad = wczytajDane(&wejscie);
	plik.close();
}

/**
 * @brief PrizeParser::bladWczytywania Mówi czy wystąpił błąd podczas wczytywania
 * @return true -> był błąd podczas wczytywania, false w p.p.
 */
bool PrizeParser::bladWczytywania()
{
	return bylBlad;
}

/**
 * @brief PrizeParser::wczytajDane Wczytuje dane o prizech korzystając z podanego wejscia
 * @param wejscie
 * @return true, jeśli wystąpił błąd, false, w p.p.
 */
bool PrizeParser::wczytajDane(QTextStream* wejscie)
{
	QString linia;
	int numerLinii = 1;

	while((linia = nastepny(wejscie)) != "")
	{
//-----------ILOŚĆ ARGUMENTÓW
		QStringList podzial = linia.split(";");
		if(podzial.size() != 6)
		{
			trescBledu = QString::fromUtf8( "Zła ilość pól. Wadliwa linia: ") + QString::number(numerLinii);
			return true;
		}
		QStringList reputacja = podzial.at(1).split(",");
		if(reputacja.size() != 4)
		{
			trescBledu = QString::fromUtf8( "Zła ilość pól reputacji.\nWadliwa linia: ") + QString::number(numerLinii);
			return true;
		}
//LICZBY CAŁKOWITE I GRUPY
		informacje info;
		if(!podzial.at(4).isEmpty())
			info.grupy = podzial.at(4).split(",");

		bool okID;
		bool okZloto;
		bool okDoswiadczenie;
		info.id = podzial.at(0).toInt(&okID);
		info.zloto = podzial.at(2).toUInt(&okZloto);
		info.doswiadczenie = podzial.at(3).toUInt(&okDoswiadczenie);

		if(!okID ||!okZloto || !okDoswiadczenie)
		{
			trescBledu = QString::fromUtf8("Niepoprawne dane w linii ") + QString::number(numerLinii);
			return true;
		}

		if(info.doswiadczenie < 0)
		{
			trescBledu = QString::fromUtf8("Niepoprawne wartości w linii ") + QString::number(numerLinii);
			return true;
		}
//-----------REPUTACJA
		bool blad = false;
		for(int i = 0; i < 4; ++i)
		{
			bool ok;

			Kingdom kingdom;
			switch (i) {
				case 0: kingdom = Kingdom::Humans; break;
				case 1: kingdom = Kingdom::Dwarfs; break;
				case 2: kingdom = Kingdom::Elves; break;
				case 3: kingdom = Kingdom::Halflings; break;
			}

			info.reputacja.insert(kingdom, reputacja.at(i).toInt(&ok));

			if (!ok)
				blad = true;
		}
		if(blad)
		{
			trescBledu = QString::fromUtf8("Niepoprawne wartości reputacji  w linii ") + QString::number(numerLinii);
			return true;
		}
//-----------KONKRETNE PRZEDMIOTY
		blad = false;
		if(!podzial.at(5).isEmpty())
		{
			QStringList konkrety = podzial.at(5).split(",");
			for(int i = 0; i < konkrety.size(); ++i)
			{
				bool ok;
				info.przedmioty.push_back(konkrety.at(i).toUInt(&ok));
				if(!ok)
					blad = true;
// 				else
// 					if(!dataKeeper->items_.contains(info.przedmioty.back()))
// 					{
// 						trescBledu = QString::fromUtf8("Niepoprawny identyfikator przedmiotu w linii ") + QString::number(numerLinii);
// 						return true;
// 					}
			}
		}
//-----------ZAPISANIE DANYCH
// 		const Prize* nowy = new Prize(info.reputacja, info.zloto, info.doswiadczenie, info.grupy, info.przedmioty);
		Prize* nowy = new Prize({}, info.doswiadczenie, info.przedmioty, info.zloto, info.reputacja);
		mod->prizes_.insert(info.id, nowy);
		++numerLinii;
	}
	return false;
}

/**
 * @brief PrizeParser::nastepny Zwraca linię z podanego strumienia, która nie jest komentarzem, oraz nie jest pusta
 * @param wejscie Strumień wejścia z danymi
 * @return QString z oczekiwaną zawartością, w przypadku błędu zwraca pusty QString
 */
QString PrizeParser::nastepny(QTextStream *wejscie)
{
	while(!wejscie->atEnd())
	{
		QString tmp = wejscie->readLine();
		if( !tmp.isEmpty() && !(tmp.size() >= 2 && tmp[0] == '/' && tmp[1] == '/') )
			return tmp;
	}
	return "";
}
