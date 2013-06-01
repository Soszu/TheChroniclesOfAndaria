#include "parserprzedmiotow.h"

ParserPrzedmiotow::ParserPrzedmiotow(MistrzGry *mistrz)
{
	this->mistrzGry = mistrz;
	aktualnaGrupa = "";
	bylBlad = false;

	QFile plik(QString(":/dane/przedmioty.txt"));
		if(!plik.open(QIODevice::ReadOnly))
		{
			qDebug() << "Nie udalo sie wczytac pliku z danymi przedmiotow";
			bylBlad = true;
			plik.close();
			return;
		}
		QTextStream wejscie(&plik);
		bylBlad = wczytajDane(&wejscie);
		plik.close();
}

/**
 * @brief ParserPrzedmiotow::bladWczytywaniaMówi czy wystąpił błąd podczas wczytywania
 * @return true -> był błąd podczas wczytywania, false w p.p.
 */
bool ParserPrzedmiotow::bladWczytywania()
{
	return bylBlad;
}

/**
 * @brief ParserPrzedmiotow::wczytajDane Wczytuje dane o przedmiotach korzystając z podanego wejścia
 * @param wejscie
 * @return true, jeśli wystąpił błąd, false w p.p.
 */
bool ParserPrzedmiotow::wczytajDane(QTextStream *wejscie)
{
	QString linia;
	while((linia = nastepny(wejscie)) != "")
		qDebug() <<linia;
	return false;
}

/**
 * @brief ParserPrzedmiotow::nastepny  Zwraca linię z podanego strumienia, która nie jest komentarzem, oraz nie jest pusta
 * @param wejscie Strumień wejścia z danymi
 * @return QString z oczekiwaną zawartością, w przypadku błędu lub konca pliku zwraca pusty QString
 */
QString ParserPrzedmiotow::nastepny(QTextStream *wejscie)
{
	while(!wejscie->atEnd())
	{
		QString tmp = wejscie->readLine();
		if( !tmp.isEmpty() && !(tmp.size() >= 2 && tmp[0] == '/' && tmp[1] == '/') )
			return tmp;
	}
	return "";
}
