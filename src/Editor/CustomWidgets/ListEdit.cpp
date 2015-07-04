/*
Copyright (C) 2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
Copyright (C) 2015 by Bartosz Szreder <szreder [at] mimuw [dot] edu [dot] pl>
This file is part of The Chronicles Of Andaria Project.

	The Chronicles of Andaria Project is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	The Chronicles of Andaria Project is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with The Chronicles Of Andaria.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "Editor/CustomWidgets/ListEdit.hpp"

#include "Core/Resources.hpp"

ListEdit::ListEdit(QWidget * parent) : QWidget(parent)
{
	initLayout();

	connect(&buttonsMapper_, static_cast<void (QSignalMapper::*)(QWidget *)>(&QSignalMapper::mapped),
	        this, &ListEdit::onEditRemoved);
}

void ListEdit::reset()
{
	while (!edits_.isEmpty())
		removeRow(0);
}

void ListEdit::setEdits(const QList<QWidget *> & edits)
{
	reset();
	for (auto & edit : edits)
		addEdit(edit);
}

void ListEdit::initLayout()
{
	mainLayout_ = new QVBoxLayout;
	mainLayout_->setSpacing(0);
	setLayout(mainLayout_);

	auto plusBtn = new QPushButton(QIcon(QPixmap(Icons::Plus)), {});
	connect(plusBtn, &QPushButton::clicked, this, &ListEdit::onEditAdded);

	addRow(plusBtn);
}

void ListEdit::addEdit(QWidget * edit)
{
	auto newMinus = new QPushButton(QIcon(QPixmap(Icons::Minus)), {});
	connect(newMinus, &QPushButton::clicked,
	        &buttonsMapper_, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
	buttonsMapper_.setMapping(newMinus, newMinus);

	minuses_.append(newMinus);
	edits_.append(edit);
	addRow(newMinus, edit);
}

void ListEdit::removeRow(int index)
{
	delete mainLayout_->takeAt(index);
	delete edits_.takeAt(index);
	delete minuses_.takeAt(index);
}

void ListEdit::addRow(QWidget * btn, QWidget * widget)
{
	QHBoxLayout *row = new QHBoxLayout;
	row->addWidget(btn);
	if (widget != nullptr)
		row->addWidget(widget, 1);
	else
		row->addStretch();
	mainLayout_->insertLayout(edits_.count() - 1, row);
}

void ListEdit::onEditAdded()
{
	addEdit(createEditWidget());
}

void ListEdit::onEditRemoved(QWidget * widget)
{
	int index = minuses_.lastIndexOf(widget);
	removeRow(index);
	rowRemoved(index);
}
