#include "parserzadan.h"

ParserZadan::ParserZadan(MistrzGry *mistrz)
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

bool ParserZadan::bladWczytywania()
{
	return bylBlad;
}

bool ParserZadan::wczytajWymiary(QTextStream *wejscie)
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

bool ParserZadan::wczytajDane(QTextStream *wejscie)
{
	QString linia;
	int numerLinii = 1;

	while((linia = nastepny(wejscie)) != "")
	{
//-----------ILOŚĆ ARGUMENTÓW
		QStringList podzial = linia.split(";");
		if(podzial.size() != 9)
		{
			trescBledu = QString::fromUtf8( "Zła ilość pól. Wadliwa linia: ") + QString::number(numerLinii);
			return true;
		}
		QStringList pole = podzial.at(6).split(",");
		if(pole.size() != 2)
		{
			trescBledu = QString::fromUtf8( "Zła ilość współrzędnych pola.\n Wadliwa linia: ") + QString::number(numerLinii);
			return true;
		}
//-----------TEKSTY
		informacje info;
		info.tytul = podzial.at(2);
		info.tresc = podzial.at(3);
		if (podzial.at(5).size() != 1)
		{
			trescBledu = QString::fromUtf8("Zła ilość znaków w symbolu koloru\nw linii ") + QString::number(numerLinii);
			return true;
		}
		info.kolorCzcionki = podzial.at(5)[0].toAscii();

//-----------POPRAWNOŚĆ KOLORU
		QColor kolorCzcionki;
		if(info.kolorCzcionki == 'b')
			kolorCzcionki = Qt::black; //żeby nie zlewało się z jasnym tłem zamiana biały na czarny
		else if(info.kolorCzcionki == 'n')
			kolorCzcionki = Qt::darkBlue;
		else if(info.kolorCzcionki == 'c')
			kolorCzcionki = Qt::darkRed;
		else{
			trescBledu = QString::fromUtf8("Niepoprawny symbol koloru w linii ") + QString::number(numerLinii);
			return true;
		}
//-----------LICZBY CAŁKOWITE
		bool okID;
		bool okRodzaj;
		bool okIDNagrody;
		bool okCelX;
		bool okCelY;
		int celX, celY;
		info.id = podzial.at(0).toInt(&okID);
		info.rodzaj = (RodzajZadania)podzial.at(1).toInt(&okRodzaj);
		info.idNagrody = podzial.at(7).toInt(&okIDNagrody);
		celX = pole.at(0).toInt(&okCelX);
		celY = pole.at(1).toInt(&okCelY);

		if(!okID ||!okRodzaj || !okIDNagrody || !okCelX || !okCelY)
		{
			trescBledu = QString::fromUtf8("Niepoprawne dane w linii ") + QString::number(numerLinii);
			return true;
		}

		if(info.rodzaj <= 0 || info.rodzaj > LICZBA_RODZAJOW_ZADAN)
		{
			trescBledu = QString::fromUtf8("Niepoprawny rodzaj zadania w linii ") + QString::number(numerLinii);
			return true;
		}

		if (!mistrzGry->nagrody.contains(info.idNagrody))
		{
			trescBledu = QString::fromUtf8("Niepoprawne ID nagrody w linii ") + QString::number(numerLinii);
			return true;
		}
//-----------WARTOSCI BOOLOWSKIE
		QString powrot = podzial.at(4);
		powrot.remove(" ");
		if(powrot == "1")
			info.czyPowrot == true;
		else if(powrot == "0")
			info.czyPowrot == false;
		else
		{
			trescBledu = QString::fromUtf8("Niepoprawna wartosc \"czy Powrot\" w linii") + QString::number(numerLinii);
			return true;
		}
//-----------POPRAWNOSC CELU
		if(celX > szerokoscPlanszy || celX < 1 || celY > wysokoscPlanszy || celY <1) //CHECK: indeksowanie od 0 czy od 1
		{
			trescBledu = QString::fromUtf8("Podane współrzędne nie są poprawne. Linia: ") + QString::number(numerLinii);
			return true;
		}
		info.cel.x = celX;
		info.cel.y = celY;
//-----------PRZECIWNICY
		//TODO:
		info.idPrzeciwnikow = new QList<Przeciwnik*>;
		bool blad = false;
		if(!podzial.at(8).isEmpty())
		{
			QList<int> wartosciID;
			QStringList identyfikatory = podzial.at(8).split(",");
			for(int i = 0; i < identyfikatory.size(); ++i)
			{
				bool ok;
				wartosciID.push_back(identyfikatory.at(i).toInt(&ok));
				if(!ok)
					blad = true;
				else
					if(!mistrzGry->przeciwnicy.contains(wartosciID.back()))
					{
						trescBledu = QString::fromUtf8("Niepoprawny identyfikator przeciwnika w linii ") + QString::number(numerLinii);
						return true;
					}
					else
						info.idPrzeciwnikow->push_back(mistrzGry->przeciwnicy[wartosciID.back()]);
			}
		}
//-----------ZAPISANIE DANYCH
		Nagroda* nagroda = mistrzGry->nagrody[info.idNagrody];
		Zadanie* nowy = new Zadanie(info.rodzaj, info.tytul, info.tresc, info.czyPowrot, info.cel, info.kolorCzcionki, nagroda, info.idPrzeciwnikow);
		mistrzGry->zadania.insert(info.id, nowy);
		++numerLinii;
	}
	return false;
}

QString ParserZadan::nastepny(QTextStream *wejscie)
{
	while(!wejscie->atEnd())
	{
		QString tmp = wejscie->readLine();
		if( !tmp.isEmpty() && !(tmp.size() >= 2 && tmp[0] == '/' && tmp[1] == '/') )
			return tmp;
	}
	return "";
}
