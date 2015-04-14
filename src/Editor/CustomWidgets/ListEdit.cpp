/*
Copyright (C) 2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
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

QWidget * ListEdit::createEditWidget()
{
	return new QWidget;
}

void ListEdit::editRemoved(int index)
{
}

void ListEdit::reset()
{
	while (! edits_.isEmpty())
		removeEdit(0);
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

void ListEdit::removeEdit(int index)
{
	auto item = mainLayout_->takeAt(index);
	if (item == nullptr)
		return;

	delete item->widget();
	delete item;

	edits_.removeAt(index);
	minuses_.removeAt(index);
}

void ListEdit::addRow(QWidget * btn, QWidget * widget)
{
	auto hLayout = new QHBoxLayout;

	hLayout->addWidget(btn);
	if (widget == nullptr)
		hLayout->addStretch();
	else
		hLayout->addWidget(widget, 1);

	//placeholder is here for easy removing from layout
	auto placeholder = new QWidget;
	placeholder->setLayout(hLayout);
	mainLayout_->insertWidget(edits_.count() - 1, placeholder);
}

void ListEdit::onEditAdded()
{
	addEdit(createEditWidget());
}

void ListEdit::onEditRemoved(QWidget * widget)
{
	int index = minuses_.lastIndexOf(widget);
	removeEdit(index);
	editRemoved(index);
}
