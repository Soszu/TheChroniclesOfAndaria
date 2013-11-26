#include "Gui/CustomWidgets/MyButton.h"

MyButton::MyButton(int n)
{
	this->ID = n;
	connect(this, SIGNAL(clicked()), this, SLOT(emitujID()));
}

void MyButton::setID(int n)
{
	this->ID = n;
}

void MyButton::emitujID()
{
	emit kliknietyID(ID);
}
