#ifndef MOJPRZYCISK_H
#define MOJPRZYCISK_H

#include <QPushButton>

class MojPrzycisk : public QPushButton
{
	Q_OBJECT
public:
	explicit MojPrzycisk(int n, QWidget *parent = 0);

	void setID(int n);
signals:
	void kliknietyID(int n);
private slots:
	void emitujID();
private:
	int ID;
};

#endif // MOJPRZYCISK_H
