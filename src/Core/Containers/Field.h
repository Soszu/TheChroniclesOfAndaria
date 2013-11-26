#ifndef FIELD_H
#define FIELD_H

#include <QtCore>

typedef QPoint FieldId;

class Field {

public:
	Field(FieldId fieldId, QString name, int coefficient, bool hasEnemy, bool hasCity, QString imageFile, int fraction);
	FieldId fieldId() const;
	QString name() const;
	int moveCost() const;
	bool hasEnemy() const;
	bool hasCity() const;
	QString imageFile() const;
	int fraction() const;

private:
	FieldId fieldId_;
	QString name_;
	int moveCost_;
	bool hasEnemy_;
	bool hasCity_;
	QString imageFile_;
	int fraction_;
};

#endif
