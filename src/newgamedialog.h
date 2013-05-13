#ifndef NEWGAMEDIALOG_H
#define NEWGAMEDIALOG_H

#include <QDialog>
#include <QList>
#include <QBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QMessageBox>
#include <QStringList>
#include "gra.h"
#include "gracz.h"

class NewGameDialog : public QDialog
{
	Q_OBJECT
public:
	explicit NewGameDialog(QWidget *parent = 0);
	~NewGameDialog();
signals:

public slots:

private:

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
	Gracz* dajGracza(int indeks);

private slots:
	void przekazDane();
	void dodajWiersz();
	void usunWiersz();
};

#endif // NEWGAMEDIALOG_H
