#include "mybutton.h"

MyButton::MyButton(QString nazwa, QWidget *parent) :	QPushButton(parent)
{
	setText(nazwa);
	connect(this, SIGNAL(clicked()), this, SLOT(emitujNazwe()));
}

void MyButton::emitujNazwe()
{
	emit kliknietyNazwa(text());
}
