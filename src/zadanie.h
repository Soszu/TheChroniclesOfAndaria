#ifndef ZADANIE_H
#define ZADANIE_H
#include <QString>
#include "nagroda.h"
#include "gra.h"

class Zadanie
{
public:
	Zadanie(QString tytul, QString tresc, bool czyPowrot, quint8 poziomTrudnosci, IDPola poleCelu, Nagroda* nagroda);

	QString getTytul();
	QString getTresc();
	bool getCzyPowrot();
	quint8 getPoziomTrudnosci();
	IDPola getPoleCelu();
	Nagroda* getNagroda();

private:
	QString tytul;
	QString tresc;
	bool czyPowrot;
	quint8 poziomTrudnosci;
	IDPola poleCelu; //lista
	//przeciwnicy
	Nagroda* nagroda;
};

#endif // ZADANIE_H

/*
pomyślałem o zadaniach, teraz jestem w stanie zrealizować 3 różne typy( realizują 6 rodzajów napisanych przez ciebie zadań),
dlatego przy pisaniu zadań chciałbym żebyś każdemy przydzielił typ i podał odpowiednie wartości:
W kolejnej wersji dodam realizację reszty.

typ(1,2 lub 3); tytul, tresc; czyPowrtót; (poziom Trudności); polaCelu (wypisane po przecinkach współrzędne); przeciwnicy(wypisane po przecinkach ich liczby porządkowe); <opis nagrody>

(nie wiem czy już nie wspominałem) współrzędne to może być numer wiersza i kolumny pola, albo pojedyńcza liczba stosownie do jakiegoś ponumerowania np. kolejno wierszami rosnąco numery

Typy zadań:
Typ 1. Zabij przeciwnika/ przeciwników (ilość zależna od ilości podanych)
	tu potrzebuje 1 miejsca, na którym odbywa się szlachtowanie przeciwników, oraz przeciwników
Typ 2. Idź gdzieś / Zbierz kilka przedmiotów
	tu potrzebuje 1 miejsca, albo niejednego miejsca (wtedy automatycznie wybiorę o co chodzi)
Typ 3. Odnajdź kogoś i rzuć kością czy to tu
	tu potrzebuje pola i ile procent na sukces jest (bez pisania znaczku %)
*/
