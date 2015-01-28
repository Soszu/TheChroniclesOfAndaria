/**
Copyright (C) 2013 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
Copyright (C) 2013 Łukasz Piesiewicz <wookesh [at] gmail [dot] com>

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

#include "Core/Parsers/ItemParser.h"

#include "Core/Paths.h"
#include "Core/Enums.hpp"

#include "Core/Containers/Bases/ItemBase.h"

ItemParser::ItemParser(Mod *mod)
{
	this->mod = mod;
	aktualnaGrupa = "";
	bylBlad = false;

	QFile plik(PLIK_PRZEDMIOTOW);
		if(!plik.open(QIODevice::ReadOnly))
		{
			trescBledu = QString::fromUtf8("Nie udało się wczytać pliku");
			bylBlad = true;
			return;
		}
		QTextStream wejscie(&plik);
		bylBlad = wczytajDane(&wejscie);
		plik.close();
}

/**
 * @brief ItemParser::bladWczytywaniaMówi czy wystąpił błąd podczas wczytywania
 * @return true -> był błąd podczas wczytywania, false w p.p.
 */
bool ItemParser::bladWczytywania()
{
	return bylBlad;
}

/**
 * @brief ItemParser::wczytajDane Wczytuje dane o przedmiotach korzystając z podanego wejścia
 * @param wejscie
 * @return true, jeśli wystąpił błąd, false w p.p.
 */
bool ItemParser::wczytajDane(QTextStream *wejscie)
{
	QString linia;
	int numerLinii = 1;
	while((linia = nastepny(wejscie)) != "")
	{
//-----------NAZWA GRUPY
		if(linia[0] == '$')
		{
			aktualnaGrupa = linia.right(linia.size() - 1);
			continue;
		}
//-----------ILOSC ARGUMENTÓW
		QStringList podzial = linia.split(";");
		if(podzial.size() != 15)
		{
			trescBledu = QString::fromUtf8("Zła ilość pól. Wadliwa linia: ") + QString::number(numerLinii);
			return true;
		}
		informacje info;
//-----------NAZWA I DŁUGOŚĆ SMBOLI
		info.name = podzial.at(1);
		if(podzial.at(2).size()!= 1 && podzial.at(14).size() != 1)
		{
			trescBledu = QString::fromUtf8("Niepoprawne symbole. Wadliwa linia: ") + QString::number(numerLinii);
			return true;
		}
		info.typ = podzial.at(2)[0].toLatin1();

//-----------WARTOŚCI BOOL-OWSKIE
		bool blad = false;

		QString tmp2 = podzial.at(11);
		tmp2.remove(" ");
		if(tmp2 == "0")
			info.czy1Reczna = false;
		else if(tmp2 == "1")
			info.czy1Reczna = true;
		else blad = true;

		tmp2 = podzial.at(12);
		tmp2.remove(" ");
		if(tmp2 == "0")
			info.czyMocny = false;
		else if(tmp2 == "1")
			info.czyMocny = true;
		else blad = true;

		if(blad)
		{
			trescBledu = QString::fromUtf8("Niepoprawne wartości. Wadliwa linia: ") + QString::number(numerLinii);
			return true;
		}
//-----------LICZBY CAŁKOWITE
		bool okID;
		bool okWrecz;
		bool okDystans;
		bool okMagia;
		bool okObrona;
		bool okPercepcja;
		bool okHP;
		bool okHPRegen;
		bool okOgraniczenia;
		bool okWartosc;
		bool okJakosc;

		info.id = podzial.at(0).toInt(&okID);
		info.wrecz = podzial.at(3).toInt(&okWrecz);
		info.dystans = podzial.at(4).toInt(&okDystans);
		info.magia = podzial.at(5).toInt(&okMagia);
		info.defence = podzial.at(6).toInt(&okObrona);
		info.perception = podzial.at(7).toInt(&okPercepcja);
		info.HP = podzial.at(8).toInt(&okHP);
		info.HPregen = podzial.at(9).toInt(&okHPRegen);
		info.ograniczenie = podzial.at(10).toInt(&okOgraniczenia);
		info.wartosc = podzial.at(13).toInt(&okWartosc);
		info.jakosc = podzial.at(14).toInt(&okJakosc);

		if(!okID ||!okWrecz || !okDystans || !okMagia || !okObrona || !okPercepcja || !okHP || !okHPRegen || !okOgraniczenia || !okWartosc || !okJakosc)
		{
			trescBledu = QString::fromUtf8("Niepoprawne dane w linii ") + QString::number(numerLinii);
			return true;
		}

		if( info.wartosc < 0)
		{
			trescBledu = QString::fromUtf8("Niepoprawna wartość przedmiotu w linii ") + QString::number(numerLinii);
			return true;
		}

		if( info.jakosc < 0 || info.jakosc >= 4)
		{
			trescBledu = QString::fromUtf8("Niepoprawna wartość jakości w linii ") + QString::number(numerLinii);
			return true;
		}

		ItemBase::Quality jakosc = ItemBase::Quality::NotApplicable;
		switch (info.jakosc) {
			case 1: jakosc = ItemBase::Quality::Standard;
			case 2: jakosc = ItemBase::Quality::Magical;
			case 3: jakosc = ItemBase::Quality::Legendary;
		}
//-----------POPRAWNOŚĆ OGRANICZENIA
		blad = false;
		int tmp = info.ograniczenie;
		for(int i = 0; i < 4; ++i, tmp /= 10)
			if(tmp % 10 != 0 && tmp % 10 != 1)
				blad = true;
		if(blad || podzial.at(10).size() != 4)
		{
			trescBledu = QString::fromUtf8("Niepoprawne ograniczenia w linii ") + QString::number(numerLinii);
			return true;
		}
//-----------POPRAWNOŚĆ TYPU
		//można było zamiast czy1ręczna dołożyć 1 typ przy wczytywaniu, ale teraz już jest za dużo pracy przy zamianie.
		//na dłuższą metę nie ma to znaczenia
		ItemBase::Type rodzaj;
		switch (info.typ) {
		case 'w':
			if(info.czy1Reczna)
				rodzaj = ItemBase::Type::OneHandedWeapon;
			else
				rodzaj = ItemBase::Type::TwoHandedWeapon;
			break;
		case 't':
			rodzaj = ItemBase::Type::Shield;
			break;
		case 'p':
			rodzaj = ItemBase::Type::Armor;
			break;
		case 'h':
			rodzaj = ItemBase::Type::Helmet;
			break;
		case 'a':
			rodzaj = ItemBase::Type::Artifact;
			break;
		case 'm':
			rodzaj = ItemBase::Type::Potion;
			break;
		default:
			trescBledu = QString::fromUtf8("Niepoprawny symbol typu w linii ") + QString::number(numerLinii);
			return true;
			break;
		}

//-----------ZAPISANIE DANYCH
		ItemBase* nowy = new ItemBase(info.id, info.name);
		nowy->setPrice(info.wartosc);
		nowy->setType(rodzaj);
		if (info.HP)         nowy->addEffect(Effect(Effect::Type::MaxHealth,    info.HP));
		if (info.wrecz)      nowy->addEffect(Effect(Effect::Type::MeleeBase,    info.wrecz));
		if (info.dystans)    nowy->addEffect(Effect(Effect::Type::RangedBase,   info.dystans));
		if (info.magia)      nowy->addEffect(Effect(Effect::Type::MagicalBase,  info.magia));
		if (info.defence)    nowy->addEffect(Effect(Effect::Type::Defence,      info.defence));
		if (info.perception) nowy->addEffect(Effect(Effect::Type::Perception,   info.perception));
		if (info.HPregen)    nowy->addEffect(Effect(Effect::Type::Regeneration, info.HPregen));
		nowy->setQuality(jakosc);

		mod->items_.insert(info.id, nowy);

		++numerLinii;

	}
	return false;
}

/**
 * @brief ItemParser::nastepny  Zwraca linię z podanego strumienia, która nie jest komentarzem, oraz nie jest pusta
 * @param wejscie Strumień wejścia z danymi
 * @return QString z oczekiwaną zawartością, w przypadku błędu lub konca pliku zwraca pusty QString
 */
QString ItemParser::nastepny(QTextStream *wejscie)
{
	while(!wejscie->atEnd())
	{
		QString tmp = wejscie->readLine();
		if( !tmp.isEmpty() && !(tmp.size() >= 2 && tmp[0] == '/' && tmp[1] == '/') )
			return tmp;
	}
	return "";
}