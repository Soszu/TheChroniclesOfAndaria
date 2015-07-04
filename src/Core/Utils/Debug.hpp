/*
Copyright (C) 2015 by Piotr Majcherczyk <fynxor [at] gmail [dot] com>
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
#include <cstdio>

// Message levels
// 0 - no messages at all
// 1 - critical
// 2 - error
// 3 - warning
// 4 - info
// 5 - log

// Functions
// crit
// err
// warn
// info
// log

#define MESSAGE_LEVEL 5

// Additional log messages if log level is enabled
// 0 - no logs
// 1 - normal logs
// 2 - long logs (very extensive ones)

// Functions
// datalog
// ldatalog
// graphicslog
// lgraphicslog

#define ENABLE_DATA_LOGS     2
#define ENABLE_GRAPHICS_LOGS 1


namespace {
	static const QString BashRed     = "0;31m";
	static const QString BashGreen   = "0;32m";
	static const QString BashYellow  = "0;33m";
	static const QString BashDefault = "0m";

	inline void message(const QString &msg)
	{
		fprintf(stderr, (msg + "\n").toStdString().c_str());
	}

	inline QString colour(const QString &msg, const QString &colour)
	{
		return "\033[" + colour + msg + "\033[" + BashDefault;
	}
}


#if MESSAGE_LEVEL >= 1
inline void crit(const QString &msg)
{
	message(colour(msg, BashRed));
	exit(0);
}
#else
inline void crit(const QString &)
{
	exit(0);
}
#endif


#if MESSAGE_LEVEL >= 2
inline void err(const QString &msg)
{
	message(colour(msg, BashRed));
}
#else
inline void err(const QString &) {}
#endif


#if MESSAGE_LEVEL >= 3
inline void warn(const QString &msg)
{
	message(colour(msg, BashYellow));
}
#else
inline void warn(const QString &) {}
#endif


#if MESSAGE_LEVEL >= 4
inline void info(const QString &msg)
{
	message(colour(msg, BashGreen));
}
#else
inline void info(const QString &) {}
#endif


#if MESSAGE_LEVEL == 5
inline void log(const QString &msg)
{
	message(msg);
}

#if ENABLE_DATA_LOGS == 2
inline void ldatalog(const QString &msg)
{
	message("\t" + msg);
}
#else
inline void ldatalog(const QString &) {}
#endif

#if ENABLE_DATA_LOGS >= 1
inline void datalog(const QString &msg)
{
	message(msg);
}
#else
inline void datalog(const QString &) {}
#endif

#if ENABLE_GRAPHICS_LOGS == 2
inline void lgraphicslog(const QString &msg)
{
	message("\t" + msg);
}
#else
inline void lgraphicslog(const QString &) {}
#endif

#if ENABLE_GRAPHICS_LOGS >= 1
inline void graphicslog(const QString &msg)
{
	message(msg);
}
#else
inline void graphicslog(const QString &msg) {}
#endif

#else
inline void log(const QString &) {}
inline void ldatalog(const QString &) {}
inline void datalog(const QString &) {}
inline void lgraphicslog(const QString &) {}
inline void graphicslog(const QString &) {}
#endif
