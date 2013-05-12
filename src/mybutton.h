#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>

class MyButton : public QPushButton
{
	Q_OBJECT
public:
	explicit MyButton(QString nazwa, QWidget *parent = 0);

signals:
	void kliknietyNazwa(QString nazwa);

private slots:
	void emitujNazwe();
};

#endif // MYBUTTON_H
