#ifndef PANELAKCJI_H
#define PANELAKCJI_H
#include <QGroupBox>
#include "mybutton.h"
#include <QVBoxLayout>
//#include "cyklgry.h"

class PanelAkcji : public QObject
{
	Q_OBJECT
public:
	PanelAkcji(QGroupBox* box);
	void wyswietlAkcje(QList<QString> akcje);
//	void setCyklGry(CyklGry* cykl);

private slots:
	void kliknietoPrzyciskONazwie(QString nazwa);

private:
	void zwolnijPamiec();
	QVBoxLayout* uklad;
	QGroupBox* panelAkcji;
	QList<MyButton*> przyciski;
//	CyklGry* cyklGry;
};

#endif // PANELAKCJI_H
