#include "zarzadzanieekwipunkiem.h"

void aktywujBonusy(Przedmiot* przedmiot, Gracz* gracz, int m)
{
	gracz->setAtakWrecz(gracz->getAtakWrecz() + (przedmiot->getBonusAWrecz() * m));
	gracz->setAtakDystansowy(gracz->getAtakDystansowy() + (przedmiot->getBonusADystansowy() * m));
	gracz->setAtakMagiczny(gracz->getAtakMagiczny() + (przedmiot->getBonusAMagiczny() * m));
	gracz->setObrona(gracz->getObrona() + (przedmiot->getBonusObrona() * m));
	gracz->setPercepcja(gracz->getPercepcja() + (przedmiot->getBonusPercepcja() * m));
	gracz->setZdrowieMaks(gracz->getZdrowieMaks() + (przedmiot->getBonusHP() * m));
	gracz->setRegeneracja(gracz->getRegeneracja() + (przedmiot->getBonusHPregen() * m ));
}

void dezaktywujBonusy(Przedmiot* przedmiot, Gracz* gracz)
{
	aktywujBonusy(przedmiot, gracz, -1);
}

bool czyDozwolony(Przedmiot* przedmiot, Gracz* gracz)
{
	if(przedmiot->getCzyPo5Lvlu() && gracz->getPoziom() <= POZIOM_GRANICZNY)
		return false;

	return czyBrakOgraniczenia(przedmiot, gracz->getKlasa());
}

bool czyBrakOgraniczenia(Przedmiot* przedmiot, int indeks)
{
	int ograniczenie = przedmiot->getOgraniczenia();
	ograniczenie /= qPow(10, LICZBA_KLAS - indeks - 1);
	ograniczenie %= 10;
	if(ograniczenie == 0)
		return false;

	return true;
}

QString dzialanie(quint8 bonus, QString dzialanie)
{
	QString wynik;
	if(bonus > 0)
		wynik = "+";
	if(bonus < 0)
		wynik = "-";
	if(bonus != 0)
		wynik += QString::number(bonus) + " " + dzialanie + "\n";

	return wynik;
}

bool czyZalozony(Przedmiot* rzecz, Gracz* gracz)
{
	Ekwipunek* ekw = gracz->getEkwipunek();

	return (ekw->getGlowa() == rzecz || ekw->getTuluw() == rzecz || ekw->getLewaReka() == rzecz || ekw->getPrawaReka() == rzecz || ekw->getZalozoneArtefakty()->contains(rzecz));
}

void wygenerujOpis(Przedmiot* rzecz, Gracz* gracz, QTextBrowser* miejsce)
{
	miejsce->clear();

	QString zalozony = czyZalozony(rzecz, gracz) ? "Tak" : "Nie";
	QString dozwolony = czyDozwolony(rzecz, gracz) ? "Tak" : "Nie";
	QString dozwolonyOd = rzecz->getCzyPo5Lvlu() ? QString::number(POZIOM_GRANICZNY) : "1";
	QString mozliweKlasy;
	for(int i = 0; i < LICZBA_KLAS; ++i)
		if(czyBrakOgraniczenia(rzecz, i))
			mozliweKlasy += KLASY[i] + ". ";
	if(mozliweKlasy.size() > 2)
		mozliweKlasy.replace(mozliweKlasy.size() - 2, 2, "");

	miejsce->setTextColor(rzecz->getKolorCzcionki());
	miejsce->setFontWeight(QFont::Bold);
	miejsce->insertPlainText(rzecz->getNazwa() + QString("\n\n"));
	miejsce->setFontWeight(QFont::Normal);
	miejsce->setTextColor(Qt::black);

	QString opis;

	opis += QString("typ: ") + RODZAJE_PRZEDMIOTOW[rzecz->getRodzaj()] + QString("\n\n");

	opis += QString::fromUtf8("dozwolony od poziomu: ") + dozwolonyOd +  QString("\n");
	opis += QString::fromUtf8("klasy zdolne używać przedmiotu: ") + mozliweKlasy +  QString("\n");
	opis += QString::fromUtf8("czy dozwolony: ") + dozwolony +  QString("\n");
	opis += QString::fromUtf8("czy założony: ") + zalozony +  QString("\n\n");

	opis += dzialanie(rzecz->getBonusAWrecz(), QString::fromUtf8("walka wręcz") );
	opis += dzialanie(rzecz->getBonusADystansowy(), QString::fromUtf8("walka bronią dystansową") );
	opis += dzialanie(rzecz->getBonusAMagiczny(),  QString::fromUtf8("walka magiczna") );
	opis += dzialanie(rzecz->getBonusObrona(), QString::fromUtf8("obrona") );
	opis += dzialanie(rzecz->getBonusPercepcja(), QString::fromUtf8("percepcja"));
	opis += dzialanie(rzecz->getBonusHP(), QString::fromUtf8("zdrowie"));
	opis += dzialanie(rzecz->getBonusHPregen(), QString::fromUtf8("regeneracja"));

	opis += QString::fromUtf8("\nwartość kupna:  ") + QString::number(rzecz->getWartosc());
	opis += QString::fromUtf8("\nwartość sprzedarzy:  ") + QString::number(rzecz->getWartosc() / 2) + QString("\n");

	miejsce->insertPlainText(opis);
}

void zalozPrzedmiot(Przedmiot* rzecz, Gracz* gracz)
{
	Ekwipunek* ekw = gracz->getEkwipunek();

	if(czyZalozony(rzecz, gracz) || rzecz == NULL)
		return;

	switch (rzecz->getRodzaj()) {
	case bronDwureczna:
		zdejmijPrzedmiot(ekw->getPrawaReka(), gracz);
		zdejmijPrzedmiot(ekw->getLewaReka(), gracz);
		ekw->setPrawaReka(rzecz);
		break;
	case bronJednoreczna:
		zdejmijPrzedmiot(ekw->getPrawaReka(), gracz);
		ekw->setPrawaReka(rzecz);
		break;
	case tarcza:
		if(ekw->getPrawaReka()->getRodzaj() == bronDwureczna)
			zdejmijPrzedmiot(ekw->getPrawaReka(), gracz);
		zdejmijPrzedmiot(ekw->getLewaReka(), gracz);
		ekw->setLewaReka(rzecz);
		break;
	case pancerz:
		zdejmijPrzedmiot(ekw->getTuluw(), gracz);
		ekw->setTuluw(rzecz);
		break;
	case helm:
		zdejmijPrzedmiot(ekw->getGlowa(), gracz);
		ekw->setGlowa(rzecz);
		break;
	case artefakt:
		ekw->getZalozoneArtefakty()->push_back(rzecz);
	}

	aktywujBonusy(rzecz, gracz);
}

void zdejmijPrzedmiot(Przedmiot* rzecz, Gracz* gracz)
{
	if(!czyZalozony(rzecz, gracz) || rzecz == NULL)
		return;

	Ekwipunek* ekw = gracz->getEkwipunek();

	switch (rzecz->getRodzaj()) {
	case bronDwureczna:
	case bronJednoreczna:
		ekw->setPrawaReka(NULL);
		break;
	case tarcza:
		ekw->setLewaReka(NULL);
		break;
	case pancerz:
		ekw->setTuluw(NULL);
		break;
	case helm:
		ekw->setGlowa(NULL);
		break;
	case artefakt:
		QList<Przedmiot*>* artefakty = ekw->getZalozoneArtefakty();
		artefakty->removeAt(artefakty->indexOf(rzecz));
		break;
	}

	dezaktywujBonusy(rzecz, gracz);
}
