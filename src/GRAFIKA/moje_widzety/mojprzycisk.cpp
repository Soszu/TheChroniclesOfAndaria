#include "mojprzycisk.h"

MojPrzycisk::MojPrzycisk(int n)
{
	this->ID = n;
	connect(this, SIGNAL(clicked()), this, SLOT(emitujID()));
}

void MojPrzycisk::setID(int n)
{
	this->ID = n;
}

void MojPrzycisk::emitujID()
{
	emit kliknietyID(ID);
}
