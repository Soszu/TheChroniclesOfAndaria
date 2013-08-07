#include "parserprzeciwnikow.h"

ParserPrzeciwnikow::ParserPrzeciwnikow(MistrzGry *mistrzGry)
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

	if(!bylBlad && aktualnaGrupa != -1 && !mistrzGry->grupyPrzeciwnikow.contains(aktualnaGrupa))
	{
		trescBledu = QString::fromUtf8("Grupa nie może być pusta.\n Pusta jest grupa: ") + aktualnaGrupa;
		bylBlad = true;
	}

}

/**
 * @brief ParserPrzeciwnikow::bladWczytywania Mówi czy wystąpił błąd podczas wczytywania
 * @return true -> był błąd podczas wczytywania, false w p.p.
 */
bool ParserPrzeciwnikow::bladWczytywania()
{
	return bylBlad;
}

/**
 * @brief ParserPrzeciwnikow::wczytajDane Wczytuje dane o przeciwnikach korzystając z podanego wejscia
 * @param wejscie
 * @return true, jeśli wystąpił błąd, false, w p.p.
 */
bool ParserPrzeciwnikow::wczytajDane(QTextStream* wejscie)
{
	QString linia;
	int numerLinii = 1;

	while((linia = nastepny(wejscie)) != "")
	{
//-----------NAZWA GRUPY
		if(linia[0] == '$')
		{
			if(aktualnaGrupa != -1 && !mistrzGry->grupyPrzeciwnikow.contains(aktualnaGrupa))
			{
				trescBledu = QString::fromUtf8("Grupa nie może być pusta.\nPusta jest grupa: ") + aktualnaGrupa;
				return true;
			}
			QString grupa = linia.right(linia.size() - 1);
			bool okGrupa;
			aktualnaGrupa = grupa.toInt(&okGrupa);
			if(!okGrupa)
			{
				trescBledu = QString::fromUtf8("Nieprawidłowa nazwa grupy.\nPodano: ") + grupa;
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
		info.nazwa = podzial.at(1);
		info.nazwaObrazka = podzial.at(2);
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
		info.obrona = podzial.at(4).toInt(&okObrona);
		info.zdrowie = podzial.at(5).toInt(&okHP);
		info.idNagrody = podzial.at(6).toInt(&okIDNagrody);
		info.percepcja = podzial.at(7).toInt(&okPercepcja);

		if(!okID ||!okMin || !okMaks || !okObrona || !okHP || !okIDNagrody || !okPercepcja)
		{
			trescBledu = QString::fromUtf8("Niepoprawne dane w linii ") + QString::number(numerLinii);
			return true;
		}
		if(!mistrzGry->nagrody.contains(info.idNagrody))
		{
			trescBledu = QString::fromUtf8("Niepoprawny identyfikator nagrody w linii ") + QString::number(numerLinii);
			return true;
		}

		if(info.atakMin > info.atakMaks || info.atakMin < 0 || info.obrona < 0 || info.zdrowie < 0 || info.percepcja < 0)
		{
			trescBledu = QString::fromUtf8("Niepoprawne wartosci w linii ") + QString::number(numerLinii);
			return true;
		}

//-----------ZAPISANIE DANYCH
		QList<int>* poprzednia;
		if(mistrzGry->grupyPrzeciwnikow.contains(aktualnaGrupa))
			poprzednia = mistrzGry->grupyPrzeciwnikow[aktualnaGrupa];
		else
		{
			poprzednia = new QList<int>;
			mistrzGry->grupyPrzeciwnikow.insert(aktualnaGrupa, poprzednia);
		}
		poprzednia->push_back(info.id);
		Przeciwnik* nowy = new Przeciwnik(info.nazwa, info.nazwaObrazka, info.atakMin, info.atakMaks, info.obrona, info.percepcja, info.zdrowie, mistrzGry->nagrody[info.idNagrody]);
		mistrzGry->przeciwnicy.insert(info.id, nowy);

		++numerLinii;
	}
	return false;

}

/**
 * @brief ParserPrzeciwnikow::nastepny Zwraca linię z podanego strumienia, która nie jest komentarzem, oraz nie jest pusta
 * @param wejscie Strumień wejścia z danymi
 * @return QString z oczekiwaną zawartością, w przypadku błędu zwraca pusty QString
 */
QString ParserPrzeciwnikow::nastepny(QTextStream *wejscie)
{
	while(!wejscie->atEnd())
	{
		QString tmp = wejscie->readLine();
		if( !tmp.isEmpty() && !(tmp.size() >= 2 && tmp[0] == '/' && tmp[1] == '/') )
			return tmp;
	}
	return "";
}
