#include "Editor/CustomWidgets/EnumEdit.h"

EnumEdit::EnumEdit(QWidget *parent) : QComboBox(parent)
{
	connect(this, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &EnumEdit::updateValue);
}

const QVariant & EnumEdit::value() const
{
	return value_;
}

void EnumEdit::setValue(const QVariant &value)
{
	value_ = value;
	setCurrentIndex(findData(value));
}

void EnumEdit::updateValue(int index)
{
	value_ = itemData(index);
	emit valueChanged(value_);
}
