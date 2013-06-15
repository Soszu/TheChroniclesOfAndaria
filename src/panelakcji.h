#ifndef PANELAKCJI_H
#define PANELAKCJI_H
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "mistrzgry.h"
#include "mojprzycisk.h"
#include "zadanie.h"
#include "gra.h"

class MistrzGry;

class PanelAkcji : public QObject
{
	Q_OBJECT
public:
	PanelAkcji(QGroupBox* box);
	void ustawAkcje(QList<Akcja> akcje);
	void ustawZadania(QList<Zadanie*> zadania);
	void wyswietl();
	void setMistrzGry(MistrzGry* mistrz);
private slots:
	void kliknietoPrzycisk(int n);

private:
	QList<Akcja> akcje;
	QList<Zadanie*> zadania;

	void wyczyscPanel();
	QVBoxLayout* uklad;
	QGroupBox* panel;
	MistrzGry* mistrzGry;
	QList<MojPrzycisk*> przyciski;
};

#endif // PANELAKCJI_H
