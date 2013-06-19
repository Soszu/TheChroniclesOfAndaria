#include "parserprzedmiotow.h"

ParserPrzedmiotow::ParserPrzedmiotow(MistrzGry *mistrz)
{
	this->mistrzGry = mistrz;
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
		info.nazwa = podzial.at(1);
		if(podzial.at(2).size()!= 1 && podzial.at(14).size() != 1)
		{
			trescBledu = QString::fromUtf8("Niepoprawne symbole. Wadliwa linia: ") + QString::number(numerLinii);
			return true;
		}
		info.typ = podzial.at(2)[0].toAscii();
		info.kolorCzcionki = podzial.at(14)[0].toAscii();

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

		info.id = podzial.at(0).toInt(&okID);
		info.wrecz = podzial.at(3).toInt(&okWrecz);
		info.dystans = podzial.at(4).toInt(&okDystans);
		info.magia = podzial.at(5).toInt(&okMagia);
		info.obrona = podzial.at(6).toInt(&okObrona);
		info.percepcja = podzial.at(7).toInt(&okPercepcja);
		info.HP = podzial.at(8).toInt(&okHP);
		info.HPregen = podzial.at(9).toInt(&okHPRegen);
		info.ograniczenie = podzial.at(10).toInt(&okOgraniczenia);
		info.wartosc = podzial.at(13).toInt(&okWartosc);

		if(!okID ||!okWrecz || !okDystans || !okMagia || !okObrona || !okPercepcja || !okHP || !okHPRegen || !okOgraniczenia || !okWartosc)
		{
			trescBledu = QString::fromUtf8("Niepoprawne dane w linii ") + QString::number(numerLinii);
			return true;
		}

		if( info.wartosc < 0)
		{
			trescBledu = QString::fromUtf8("Niepoprawna wartość w linii ") + QString::number(numerLinii);
			return true;
		}
//-----------POPRAWNOŚĆ OGRANICZENIA
		blad = false;
		int tmp = info.ograniczenie;
		for(int i = 0; i < LICZBA_KLAS; ++i, tmp/= 10)
			if(tmp % 10 != 0 && tmp % 10 != 1)
				blad = true;
		if(blad || podzial.at(10).size() != LICZBA_KLAS)
		{
			trescBledu = QString::fromUtf8("Niepoprawne ograniczenia w linii ") + QString::number(numerLinii);
			return true;
		}
//-----------POPRAWNOŚĆ TYPU
		//można było zamiast czy1ręczna dołożyć 1 typ przy wczytywaniu, ale teraz już jest za dużo pracy przy zamianie.
		//na dłuższą metę nie ma to znaczenia
		RodzajPrzedmiotu rodzaj;
		switch (info.typ) {
		case 'w':
			if(info.czy1Reczna)
				rodzaj = bronJednoreczna;
			else
				rodzaj = bronDwureczna;
			break;
		case 't':
			rodzaj = tarcza;
			break;
		case 'p':
			rodzaj = pancerz;
			break;
		case 'h':
			rodzaj = helm;
			break;
		case 'a':
			rodzaj = artefakt;
			break;
		case 'm':
			rodzaj = mikstura;
			break;
		default:
			trescBledu = QString::fromUtf8("Niepoprawny symbol typu w linii ") + QString::number(numerLinii);
			return true;
			break;
		}
//-----------POPRAWNOŚĆ KOLORU
		QColor kolorCzcionki;
		if(info.kolorCzcionki == 'b')
			kolorCzcionki = Qt::darkGreen; //żeby nie zlewało się z tłem
		else if(info.kolorCzcionki == 'n')
			kolorCzcionki = Qt::darkBlue;
		else if(info.kolorCzcionki == 'c')
			kolorCzcionki = Qt::darkRed;
		else if(info.kolorCzcionki == 'z')
			kolorCzcionki = Qt::darkYellow;
		else{
			trescBledu = QString::fromUtf8("Niepoprawny symbol koloru w linii ") + QString::number(numerLinii);
			return true;
		}

//-----------ZAPISANIE DANYCH
		QList<int>* poprzednie;
		if(mistrzGry->grupy.contains(aktualnaGrupa))
			poprzednie = mistrzGry->grupy[aktualnaGrupa];
		else
		{
			poprzednie = new QList<int>;
			mistrzGry->grupy.insert(aktualnaGrupa, poprzednie);
		}
		poprzednie->push_back(info.id);
		Przedmiot* nowy = new Przedmiot(info.nazwa, rodzaj, info.wrecz, info.dystans, info.magia, info.obrona, info.percepcja, info.HP, info.HPregen, info.ograniczenie, info.wartosc, info.czyMocny, kolorCzcionki);
		mistrzGry->przedmioty.insert(info.id, nowy);

		++numerLinii;

	}
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
