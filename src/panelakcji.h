#ifndef PANELAKCJI_H
#define PANELAKCJI_H
#include <QGroupBox>
#include "mybutton.h"
#include <QVBoxLayout>
#include "mistrzgry.h"

class MistrzGry;

class PanelAkcji : public QObject
{
	Q_OBJECT
public:
	PanelAkcji(QGroupBox* box);
	void wyswietlAkcje(QList<QString> akcje);
	void setMistrzGry(MistrzGry* mistrz);

private slots:
	void kliknietoPrzyciskONazwie(QString nazwa);

private:
	void zwolnijPamiec();
	QVBoxLayout* uklad;
	QGroupBox* panelAkcji;
	QList<MyButton*> przyciski;
	MistrzGry* mistrzGry;
};

#endif // PANELAKCJI_H
