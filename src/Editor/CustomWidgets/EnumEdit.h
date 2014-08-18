#pragma once

#include <QtWidgets>
#include "Core/Utils/BiHash.hpp"

class EnumEdit : public QComboBox {
	Q_OBJECT
	Q_PROPERTY(QVariant value_
	           READ value
	           WRITE setValue
	           NOTIFY valueChanged
	           USER true)
public:
	EnumEdit(QWidget *parent = nullptr);
	const QVariant & value() const;
	void setValue(const QVariant &value);

private:
	QVariant value_;

private slots:
	void updateValue(int index);

signals:
	void valueChanged(QVariant value);
};