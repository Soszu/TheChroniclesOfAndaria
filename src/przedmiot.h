#ifndef PRZEDMIOT_H
#define PRZEDMIOT_H

class Przedmiot
{
public:
	Przedmiot( string nazwa, short wartosc, string opis, bool czyPo5Lvlu, short ograniczenia, int rodzaj );

private:
	string nazwa;
	short wartosc;
	string opis;
	bool czyPo5Lvlu;

	short ograniczenia;
	int rodzaj;

	string getNazwa();
	short getWartosc();
	string getOpis();
	bool getCzyPo5Lvlu();
	short getOgraniczenia();
	int getRodzaj();
};

#endif /* PRZEDMIOT_H */
