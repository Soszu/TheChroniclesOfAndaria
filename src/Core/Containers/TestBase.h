#pragma once

#include <QtCore>
#include "Core/Utils/BiHash.hpp"

class Player;

class TestBase {
public:
	enum class Type : quint8 {
		Fight,
		Blank,
		Skills
	};

	TestBase() = default;
};