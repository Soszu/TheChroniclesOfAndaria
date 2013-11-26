#include "Core/Parsers/PrizeParser.h"

PrizeParser::PrizeParser(GameMaster *mistrz)
{
	bylBlad = false;
	this->mistrzGry = mistrz;
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
		if(reputacja.size() != KingdomCount)
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
		info.zloto = podzial.at(2).toInt(&okZloto);
		info.doswiadczenie = podzial.at(3).toInt(&okDoswiadczenie);

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
		info.reputacja = new int[KingdomCount];
		bool blad = false;
		for(int i = 0; i < KingdomCount; ++i)
		{
			bool ok;
			info.reputacja[i] = reputacja.at(i).toInt(&ok);
			if (!ok)
				blad = true;
		}
		if(blad)
		{
			trescBledu = QString::fromUtf8("Niepoprawne wartości reputacji  w linii ") + QString::number(numerLinii);
			return true;
		}
//-----------KONKRETNE PRZEDMIOTY
		info.przedmioty = new QList<int>;
		blad = false;
		if(!podzial.at(5).isEmpty())
		{
			QStringList konkrety = podzial.at(5).split(",");
			for(int i = 0; i < konkrety.size(); ++i)
			{
				bool ok;
				info.przedmioty->push_back(konkrety.at(i).toInt(&ok));
				if(!ok)
					blad = true;
				else
					if(!mistrzGry->items_.contains(info.przedmioty->back()))
					{
						trescBledu = QString::fromUtf8("Niepoprawny identyfikator przedmiotu w linii ") + QString::number(numerLinii);
						return true;
					}
			}
		}
//-----------ZAPISANIE DANYCH
		Prize* nowy = new Prize(info.reputacja, info.zloto, info.doswiadczenie, info.grupy, info.przedmioty);
		mistrzGry->prizes_.insert(info.id, nowy);

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

