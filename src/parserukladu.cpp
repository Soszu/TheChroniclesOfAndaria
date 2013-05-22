#include "parserukladu.h"

ParserUkladu::ParserUkladu(Plansza* plansza)
{
	bylBlad = false;
	this->plansza = plansza;
	QFile ustawienie(QString(":/dane/plansza.txt"));

	if(!ustawienie.open(QIODevice::ReadOnly))
	{
		qDebug() << "Nie udalo sie wczytac pliku z ustawieniami planszy";
		bylBlad = true;
		ustawienie.close();
		return;
	}
	QTextStream wejscie(&ustawienie);

	bylBlad = !wczytajWymiary(&wejscie);
	if(!bylBlad)
		bylBlad = !wczytajLegende(&wejscie);
	if(!bylBlad)
		bylBlad = !wczytajUstawienie(&wejscie);

	if(!bylBlad && !nastepny(&wejscie).isEmpty())
	{
		qDebug() << "Plik wejsciowy jest za dlugi.";
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
		qDebug() << "Wystapil blad przy wczytaniu wymiarow";
		return false;
	}

	bool ok1 = true;
	bool ok2 = true;
	szerokosc = podzial.at(0).toUInt(&ok1);
	plansza->szerokoscPlanszy = szerokosc;
	wysokosc = podzial.at(1).toUInt(&ok2);
	plansza->wysokoscPlanszy = wysokosc;
	if(!ok1 || !ok2 || szerokosc < 1 || wysokosc < 1)
	{
		qDebug() << "Podane wymiary nie są poprawne.";
		return false;
	}
	return true;
}

bool ParserUkladu::wczytajLegende(QTextStream* wejscie)
{
	bool ok = true;
	int dlLegendy = nastepny(wejscie).toInt(&ok);

	if(!ok)
	{
		qDebug() << "Wystapil blad przy wczytaniu dlugosci legendy";
		return false;
	}

	for(int i = 0; i < dlLegendy; ++i)
	{
		QString linia = nastepny(wejscie);
		QStringList podzial = linia.split(";");

		if(podzial.size() != 5)
		{
			qDebug() << "Wystapil blad przy wczytaniu legendy. Zla ilosc pol. Wadliwy element: " <<i + 1;
			return false;
		}

		bool bezBledu = true;
		info informacje;
		informacje.nazwa = podzial.at(1);
		informacje.plik = podzial.at(2);
		informacje.wspolczynnik = podzial.at(4).toInt(&bezBledu);
		if(podzial.at(3) == "1")
			informacje.czyPoleZPrzeciwnikiem = true;
		else if(podzial.at(3) == "0")
			informacje.czyPoleZPrzeciwnikiem = false;
		else bezBledu == true;

		if(!bezBledu || podzial.at(0).isEmpty())
		{
			qDebug() << "Wystapil blad przy wczytaniu legendy. Zly element: " <<i + 1;
			return false;
		}
		legenda.insert(podzial.at(0), informacje); //sprawdzić, czy nie zapisuje po adresie i nie likwiduje zawartości
	}
	return true;
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
			qDebug() << "Wystapil blad przy wczytaniu ustawienia. Zla ilosc danych. Wadliwy wiersz: " <<i + 1;
			return false;
		}
		for(int j = 0; j < szerokosc; ++j)
		{
			QString symbol = (podzial.at(j));
			symbol.remove(QChar(' '));

			if(!legenda.contains(symbol))
			{
				qDebug() << "Wystapil blad przy wczytaniu ustawienia. Nie znaleniono odpowiedniego symbolu. Wadliwy wiersz: " <<i + 1 <<"Symbol: " <<symbol;;
				return false;
			}
			info dane = legenda[symbol];
			IDPola miejsce = {i,j}; //sprawdzić czy napewno jest dostępny, bo jeżeli przekazywany jest wskaźnik to może nie być
			listaPol->push_back(new Pole(miejsce, dane.nazwa, dane.wspolczynnik, dane.czyPoleZPrzeciwnikiem, dane.plik));
		}
	}
	plansza->pola = listaPol;
	return true;
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
