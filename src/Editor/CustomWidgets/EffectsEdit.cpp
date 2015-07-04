/*
 * Copyright (C) 2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
 * This file is part of The Chronicles Of Andaria Project.
 *
 *	The Chronicles of Andaria Project is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	The Chronicles of Andaria Project is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with The Chronicles Of Andaria.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "Editor/CustomWidgets/EffectsEdit.hpp"

#include "Editor/CustomWidgets/EffectEdit.hpp"

EffectsEdit::EffectsEdit(QWidget * parent) : ListEdit(parent)
{}

QList<Effect> EffectsEdit::effects() const
{
	QList<Effect> effects;
	for (auto obj : effectEdits_)
		effects.append(obj->effect());

	return effects;
}

void EffectsEdit::setEffects(const QList<Effect> & effects)
{
	if (this->effects() == effects)
		return;

	effectEdits_.clear();
	QList<QWidget *> edits;
	for (auto & obj : effects) {
		auto oe = new EffectEdit(obj);
		effectEdits_.append(oe);
		connect(oe, &EffectEdit::contentChanged, this, &EffectsEdit::contentChanged);
		edits.append(oe);
	}

	ListEdit::setEdits(edits);
}

void EffectsEdit::reset()
{
	effectEdits_.clear();

	emit contentChanged();

	ListEdit::reset();
}

QWidget * EffectsEdit::createEditWidget()
{
	auto oe = new EffectEdit;
	effectEdits_.append(oe);
	connect(oe, &EffectEdit::contentChanged, this, &EffectsEdit::contentChanged);

	emit contentChanged();

	return oe;
}

void EffectsEdit::rowRemoved(int index)
{
	if (index < 0 || index > effectEdits_.count())
		return;

	effectEdits_.removeAt(index);
	emit contentChanged();
}
