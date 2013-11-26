#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "Core/Containers/Item.h"

class Equipment {

public:
	Equipment();

	//TODO CFiend moze to powinno zwracac const Item & dla wygodniejszej skladni?
	const Item * head() const;
	void setHead(const Item *item);
	const Item * torso() const;
	void setTorso(const Item *item);
	const Item * leftHand() const;
	void setLeftHand(const Item *item);
	const Item * rightHand() const;
	void setRightHand(const Item *item);

	quint8 smallPotions() const;
	void setSmallPotions(quint8 cnt);
	quint8 largePotions() const;
	void setLargePotions(quint8 cnt);

	const QList <const Item *> & backpack() const;
	const QList <const Item *> & usedArtifacts() const;

	void addItem(const Item *item);
	void removeItem(const Item *item);

	void addArtifact(const Item *item);
	void removeArtifact(const Item *item);

	static const quint8 StartingNumberOfSmallPotions = 2;
	static const quint8 StartingNumberOfLargePotions = 1;

private:
	const Item *head_;
	const Item *torso_;
	const Item *leftHand_;
	const Item *rightHand_;
	QList <const Item *> usedArtifacts_;
	QList <const Item *> backpack_;
	quint8 smallPotions_;
	quint8 largePotions_;
};

#endif
