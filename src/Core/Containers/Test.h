#pragma once

#include <QtCore>

class Test {

public:
	enum class Result : quint8 {
		Fail,
		Pass,
		Unsettled
	};

	enum class Type : quint8 {
		Fight,
		Blank,
		Skills
	};
};
QDataStream & operator<<(QDataStream &out, const Test &effect);
QDataStream & operator>>(QDataStream &in, Test &effect);
