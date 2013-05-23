#ifndef PANELAKCJI_H
#define PANELAKCJI_H
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "mistrzgry.h"
#include "mojprzycisk.h"
#include "gra.h"

class MistrzGry;

class PanelAkcji : public QObject
{
	Q_OBJECT
public:
	PanelAkcji(QGroupBox* box);
	void wyswietlAkcje(QList<Akcja> akcje);
	void setMistrzGry(MistrzGry* mistrz);

private slots:
	void kliknietoPrzycisk(int n);

private:
	void wyczyscPanel();
	QVBoxLayout* uklad;
	QGroupBox* panel;
	MistrzGry* mistrzGry;
	QList<MojPrzycisk*> przyciski;
	QLabel* informacja;
};

#endif // PANELAKCJI_H
