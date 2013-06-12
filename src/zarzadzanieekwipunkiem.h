#ifndef SZABLONOKNAEKWIPUNKU_H
#define SZABLONOKNAEKWIPUNKU_H

#include <QDialog>
#include "gracz.h"
#include "gra.h"
#include "oknogracza.h"
#include "przedmiot.h"

#include "zarzadzanieekwipunkiem.h"

void aktywujBonusy(Przedmiot* przedmiot, Gracz* gracz, int m = 1);
void dezaktywujBonusy(Przedmiot* przedmiot, Gracz* gracz);

bool czyDozwolony(Przedmiot* przedmiot, Gracz* gracz);
bool czyBrakOgraniczenia(Przedmiot* przedmiot, int indeks);

QString dzialanie(quint8 bonus, QString dzialanie);
QString wygenerujOpis(Przedmiot* rzecz, Gracz* gracz);

bool czyZalozony(Przedmiot* rzecz, Gracz* gracz);
void zalozPrzedmiot(Przedmiot* rzecz, Gracz* gracz);
void zdejmijPrzedmiot(Przedmiot* rzecz, Gracz* gracz);

#endif // SZABLONOKNAEKWIPUNKU_H
