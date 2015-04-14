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
#pragma once

#include <QtCore>

#include "Editor/CustomWidgets/ListEdit.hpp"
#include "Editor/CustomWidgets/EffectEdit.hpp"
#include "Core/Containers/Effect.hpp"

class EffectsEdit : public ListEdit {
	Q_OBJECT
	Q_PROPERTY(QList<Effect> effects
	           READ effects
	           WRITE setEffects
	           RESET reset
	           NOTIFY contentChanged
	           USER true)

public:
	EffectsEdit(QWidget * parent = nullptr);

	QList<Effect> effects() const;
	void setEffects(const QList<Effect> & effects);

	void reset();

private:
	QWidget * createEditWidget();
	void editRemoved(int index);

	QList<EffectEdit *> effectEdits_;

signals:
	void contentChanged();
};
