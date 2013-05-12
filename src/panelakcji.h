#ifndef PANELAKCJI_H
#define PANELAKCJI_H
#include <QGroupBox>
#include "mybutton.h"
#include <QVBoxLayout>

class PanelAkcji : public QObject
{
	Q_OBJECT
public:
	static PanelAkcji& getPanelAkcji();
	void wyswietlAkcje(QList<QString> akcje);
	void setGroupBox (QGroupBox* box);

private slots:
	void kliknietoPrzyciskONazwie(QString nazwa);

private:

	PanelAkcji();
	void zwolnijPamiec();
	QVBoxLayout* uklad;
	QGroupBox* panelAkcji;
	QList<MyButton*> przyciski;
};

#endif // PANELAKCJI_H
