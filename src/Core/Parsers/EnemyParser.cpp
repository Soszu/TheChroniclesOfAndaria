/**
Copyright (C) 2013 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
Thanks to 2013 Łukasz Piesiewicz <wookesh [at] gmail [dot] com>
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

#include "Core/Parsers/EnemyParser.h"

EnemyParser::EnemyParser(GameMaster *mistrzGry)
{
	this->mistrzGry = mistrzGry;
	aktualnaGrupa = -1;
	bylBlad = false;

	QFile plik(PLIK_PRZECIWNIKOW);
	if(!plik.open(QIODevice::ReadOnly))
	{
		trescBledu = QString::fromUtf8( "Nie udało się wczytać pliku");
		bylBlad = true;
		return;
	}
	QTextStream wejscie(&plik);

	bylBlad = wczytajDane(&wejscie);
	plik.close();

	if(!bylBlad && aktualnaGrupa != -1 && !mistrzGry->enemyGroups_.contains(aktualnaGrupa))
	{
		trescBledu = QString::fromUtf8("Grupa nie może być pusta.\n Pusta jest grupa: ") + aktualnaGrupa;
		bylBlad = true;
	}

}

/**
 * @brief EnemyParser::bladWczytywania Mówi czy wystąpił błąd podczas wczytywania
 * @return true -> był błąd podczas wczytywania, false w p.p.
 */
bool EnemyParser::bladWczytywania()
{
	return bylBlad;
}

/**
 * @brief EnemyParser::wczytajDane Wczytuje dane o przeciwnikach korzystając z podanego wejscia
 * @param wejscie
 * @return true, jeśli wystąpił błąd, false, w p.p.
 */
bool EnemyParser::wczytajDane(QTextStream* wejscie)
{
	QString linia;
	int numerLinii = 1;

	while((linia = nastepny(wejscie)) != "")
	{
//-----------NAZWA GRUPY
		if(linia[0] == '$')
		{
			if(aktualnaGrupa != -1 && !mistrzGry->enemyGroups_.contains(aktualnaGrupa))
			{
				trescBledu = QString::fromUtf8("Grupa nie może być pusta.\nPusta jest grupa: ") + aktualnaGrupa;
				return true;
			}
			QString grupa = linia.right(linia.size() - 1);
			bool okGrupa;
			aktualnaGrupa = grupa.toInt(&okGrupa);
			if(!okGrupa)
			{
				trescBledu = QString::fromUtf8("Nieprawidłowa name grupy.\nPodano: ") + grupa;
				return true;
			}

			continue;
		} else if(aktualnaGrupa == -1)
		{
			trescBledu = QString::fromUtf8("Nie podano nazwy grupy.");
			return true;
		}

//-----------ILOŚĆ ARGUMENTÓW
		QStringList podzial = linia.split(";");
		if(podzial.size() != 8)
		{
			trescBledu = QString::fromUtf8( "Zła ilość pol. Wadliwa linia: ") + QString::number(numerLinii);
			return true;
		}

		QStringList atak = podzial.at(3).split(",");
		if (atak.size() != 2)
		{
			trescBledu = QString::fromUtf8("Niepoprawne dane dot. ataku w wierszu ") + QString::number(numerLinii);
			return true;
		}
//-----------ZAPISANIE TEKSTÓW
		informacje info;
		info.name = podzial.at(1);
		info.nameObrazka = podzial.at(2);
//-----------LICZBY CAŁKOWITE
		bool okID;
		bool okMin;
		bool okMaks;
		bool okObrona;
		bool okHP;
		bool okIDNagrody;
		bool okPercepcja;
		info.id = podzial.at(0).toInt(&okID);
		info.atakMin = atak.at(0).toInt(&okMin);
		info.atakMaks = atak.at(1).toInt(&okMaks);
		info.defence = podzial.at(4).toInt(&okObrona);
		info.zdrowie = podzial.at(5).toInt(&okHP);
		info.idNagrody = podzial.at(6).toInt(&okIDNagrody);
		info.perception = podzial.at(7).toInt(&okPercepcja);

		if(!okID ||!okMin || !okMaks || !okObrona || !okHP || !okIDNagrody || !okPercepcja)
		{
			trescBledu = QString::fromUtf8("Niepoprawne dane w linii ") + QString::number(numerLinii);
			return true;
		}
		if(!mistrzGry->prizes_.contains(info.idNagrody))
		{
			trescBledu = QString::fromUtf8("Niepoprawny identyfikator nagrody w linii ") + QString::number(numerLinii);
			return true;
		}

		if(info.atakMin > info.atakMaks || info.atakMin < 0 || info.defence < 0 || info.zdrowie < 0 || info.perception < 0)
		{
			trescBledu = QString::fromUtf8("Niepoprawne wartosci w linii ") + QString::number(numerLinii);
			return true;
		}

//-----------ZAPISANIE DANYCH
		QList<int>* poprzednia;
		if(mistrzGry->enemyGroups_.contains(aktualnaGrupa))
			poprzednia = mistrzGry->enemyGroups_[aktualnaGrupa];
		else
		{
			poprzednia = new QList<int>;
			mistrzGry->enemyGroups_.insert(aktualnaGrupa, poprzednia);
		}
		poprzednia->push_back(info.id);
		Enemy* nowy = new Enemy(info.name, info.nameObrazka, info.atakMin, info.atakMaks, info.defence, info.perception, info.zdrowie, FightParticipant::AttackType::Melee, mistrzGry->prizes_[info.idNagrody]);
		mistrzGry->enemies_.insert(info.id, nowy);

		++numerLinii;
	}
	return false;

}

/**
 * @brief EnemyParser::nastepny Zwraca linię z podanego strumienia, która nie jest komentarzem, oraz nie jest pusta
 * @param wejscie Strumień wejścia z danymi
 * @return QString z oczekiwaną zawartością, w przypadku błędu zwraca pusty QString
 */
QString EnemyParser::nastepny(QTextStream *wejscie)
{
	while(!wejscie->atEnd())
	{
		QString tmp = wejscie->readLine();
		if( !tmp.isEmpty() && !(tmp.size() >= 2 && tmp[0] == '/' && tmp[1] == '/') )
			return tmp;
	}
	return "";
}
