#ifndef OKNONOWEJGRY_H
#define OKNONOWEJGRY_H

#include <QDialog>
#include <QList>
#include <QBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QMessageBox>
#include <QStringList>
#include <QMainWindow>
#include "gra.h"
#include "gracz.h"
#include "cyklgry.h"

class OknoNowejGry : public QDialog
{
	Q_OBJECT
public:
	explicit OknoNowejGry(QWidget *parent = 0);
	~OknoNowejGry();
	void setCyklGry(CyklGry* cykl);
	void setMainWindow(QMainWindow* mainWindow);
signals:

public slots:

private:
	CyklGry* cyklGry;
	QMainWindow* mainWindow;
	quint8 liczbaGraczy;

	struct wierszWyboru{
		QLineEdit* nazwa;
		QComboBox* rasa;
		QComboBox* klasa;
		QComboBox* kolor;
		QCheckBox* ai;
	};

	QList<wierszWyboru> gracze;

	QPushButton* dodajGracza;
	QPushButton* usunGracza;
	QPushButton* anuluj;
	QPushButton* ok;

	QHBoxLayout* layoutyWierszy[MAX_GRACZY];
	QVBoxLayout layoutNaWierszeWyboru;
	QHBoxLayout layoutNaPrzyciski;
	QVBoxLayout* layoutGlowny;

	QMessageBox* komunikat;

	void wypelnij(wierszWyboru *wiersz, int numer);

private slots:
	void przekazDane();
	void dodajWiersz();
	void usunWiersz();
};

#endif //OKNONOWEJGRY_H
