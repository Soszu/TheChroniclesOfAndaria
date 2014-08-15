#pragma once

#include <QtCore>
#include "Core/Utils/BiHash.hpp"
#include "Core/Containers/TestBase.h"

class Player;

class Test : public QObject {
	Q_OBJECT
public:
	enum class Result : quint8 {
		Fail,
		Pass,
		Unsettled
	};

	Test() = default;
	void take(Player *player) const;

signals:
	void result(Player *, Result);
};