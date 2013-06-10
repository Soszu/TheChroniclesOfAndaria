#include "parserukladu.h"

ParserUkladu::ParserUkladu(Plansza* plansza)
{
	bylBlad = false;
	this->plansza = plansza;
	QFile ustawienie(QString(":/dane/plansza.txt"));

	if(!ustawienie.open(QIODevice::ReadOnly))
	{
		trescBledu = QString::fromUtf8("Nie udało się wczytać pliku.");
		bylBlad = true;
		ustawienie.close();
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
 * @brief ParserUkladu::bladWczytywania Zwraca, czy pojawił się jakiś błąd przy wczytywaniu układu
 * @return true pojawił się błąd, false w przeciwnym wypadku
 */
bool ParserUkladu::bladWczytywania()
{
	return bylBlad;
}

bool ParserUkladu::wczytajWymiary(QTextStream* wejscie)
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
	plansza->szerokoscPlanszy = szerokosc;
	wysokosc = podzial.at(1).toUInt(&ok2);
	plansza->wysokoscPlanszy = wysokosc;
	if(!ok1 || !ok2 || szerokosc < 1 || wysokosc < 1)
	{
		trescBledu = QString::fromUtf8("Podane wymiary nie są poprawne.");
		return true;
	}
	return false;
}

bool ParserUkladu::wczytajLegende(QTextStream* wejscie)
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

		if(podzial.size() != 6)
		{
			trescBledu = QString::fromUtf8("Wystąpił błąd przy wczytywaniu legendy.\nZła ilość pol. Wadliwy element: ") + QString::number(i + 1);
			return true;
		}

		bool bezBledu = true;
		info informacje;
		informacje.nazwa = podzial.at(1);
		informacje.plik = podzial.at(2);
		informacje.wspolczynnik = podzial.at(5).toInt(&bezBledu);

		if(podzial.at(3) == "1")
			informacje.czyPoleZPrzeciwnikiem = true;
		else if(podzial.at(3) == "0")
			informacje.czyPoleZPrzeciwnikiem = false;
		else bezBledu == false;

		if(podzial.at(4) == "1")
			informacje.czyPoleZMiastem = true;
		else if(podzial.at(4) == "0")
			informacje.czyPoleZMiastem = false;
		else bezBledu == false;

		if(!bezBledu || podzial.at(0).isEmpty())
		{
			trescBledu = QString::fromUtf8("Wystąpił błąd przy wczytywaniu legendy.\nZły element: ") + QString::number(i + 1);
			return true;
		}
		legenda.insert(podzial.at(0), informacje);
	}
	return false;
}

bool ParserUkladu::wczytajUstawienie(QTextStream* wejscie)
{
	QList<Pole*>* listaPol = new QList<Pole*>;

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
			IDPola miejsce = {j,i};
			listaPol->push_back(new Pole(miejsce, dane.nazwa, dane.wspolczynnik, dane.czyPoleZPrzeciwnikiem, dane.czyPoleZMiastem, dane.plik));
		}
	}
	plansza->pola = listaPol;
	return false;
}

/**
 * @brief ParserUkladu::nastepny Zwraca linię z podanego strumienia, która nie jest komentarzem, oraz nie jest pusta
 * @param wejscie Strumień wejścia z danymi
 * @return QString z oczekiwaną zawartością, w przypadku błędu zwraca pusty QString
 */
QString ParserUkladu::nastepny(QTextStream *wejscie)
{
	while(!wejscie->atEnd())
	{
		QString tmp = wejscie->readLine();
		if( !tmp.isEmpty() && !(tmp.size() >= 2 && tmp[0] == '/' && tmp[1] == '/') )
			return tmp;
	}
	return "";
}
