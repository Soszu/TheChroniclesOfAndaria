#include "parserprzeciwnikow.h"

ParserPrzeciwnikow::ParserPrzeciwnikow(MistrzGry *mistrzGry)
{
	this->mistrzGry = mistrzGry;
	bylBlad = false;
	QFile plik(QString(":/dane/przeciwnicy.txt"));
	if(!plik.open(QIODevice::ReadOnly))
	{
		qDebug() << "Nie udalo sie wczytac pliku z danymi przeciwnikow";
		bylBlad = true;
		plik.close();
		return;
	}
	QTextStream wejscie(&plik);
	bylBlad = wczytajDane(&wejscie);
	plik.close();
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
//-----------ILOŚĆ ARGUMENTÓW
		QStringList podzial = linia.split(";");
		if(podzial.size() != 8)
		{
			qDebug() << "Zla ilosc pol. Wadliwa linia: " <<numerLinii;
			return true;
		}

		QStringList atak = podzial.at(4).split(",");
		if (atak.size() != 2)
		{
			qDebug() <<"Niepoprawne dane dot. ataku w wierszu " <<numerLinii;
			return true;
		}
//-----------ZAPISANIE TEKSTÓW
		informacje info;
		info.nazwa = podzial.at(1);
		info.nazwaObrazka = podzial.at(2);
		info.opis = podzial.at(3);
//-----------LICZBY CAŁKOWITE
		bool okID;
		bool okMin;
		bool okMaks;
		bool okObrona;
		bool okHP;
		bool okIDNagrody;
		info.id = podzial.at(0).toInt(&okID);
		info.atakMin = atak.at(0).toInt(&okMin);
		info.atakMaks = atak.at(1).toInt(&okMaks);
		info.obrona = podzial.at(5).toInt(&okObrona);
		info.zdrowie = podzial.at(6).toInt(&okHP);
		info.idNagrody = podzial.at(7).toInt(&okIDNagrody);

		if(!okID ||!okMin || !okMaks || !okObrona || !okHP || !okID)
		{
			qDebug() <<"Niepoprawne dane w linii " <<numerLinii;
			return true;
		}

		if(!mistrzGry->nagrody.contains(info.idNagrody))
		{
			qDebug() <<"Niepoprawny identyfikator nagrody w linii " <<numerLinii;
			return true;
		}

		if(info.atakMin > info.atakMaks || info.atakMin < 0 || info.obrona < 0 || info.zdrowie <= 0)
		{
			qDebug() <<"Niepoprawne wartosci w linii " <<numerLinii;
			return true;
		}
//-----------ZAPISANIE DANYCH
		Przeciwnik* nowy = new Przeciwnik(info.nazwa, info.nazwaObrazka, info.opis, info.atakMin, info.atakMaks, info.obrona, info.zdrowie, mistrzGry->podajNagrode(info.idNagrody));
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
