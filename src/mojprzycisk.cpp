#include "mojprzycisk.h"

MojPrzycisk::MojPrzycisk(int n, QWidget *parent) : QPushButton(parent)
{
	this->ID = n;
//NOTE: Czy poniższa linijka ma sens, po co jest dziedziczenie w konstruktorze,
//jak zrobić żeby parent rzeczywiście się ustawiał w razie potrzeby (teraz i tak nie używam chyba)
	setParent(parent);
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
