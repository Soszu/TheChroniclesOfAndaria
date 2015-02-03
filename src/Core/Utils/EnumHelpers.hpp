/*
 The MIT License (MIT)

 Copyright (c) 2013,2014 Bartosz Szreder

 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 the Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef EnumHelpers_hpp
#define EnumHelpers_hpp

#include <type_traits>

template <typename ET>
constexpr typename std::underlying_type <ET>::type toUnderlying(ET et)
{
	return static_cast<typename std::underlying_type<ET>::type>(et);
}

template <typename ET>
constexpr typename std::underlying_type <ET>::type & toUnderlyingRef(ET &et)
{
	return reinterpret_cast<typename std::underlying_type<ET>::type &>(et);
}

#include <QtCore/qglobal.h>
#include <QtCore/QDataStream>
#include <QtCore/QVector>

#define EnumClass(EnumName, EnumType, ...) \
struct EnumName { \
friend uint qHash(EnumName); \
friend QDataStream & operator << (QDataStream &, const EnumName &); \
friend QDataStream & operator >> (QDataStream &, EnumName &); \
enum EnumName ## Internal : EnumType { \
__VA_ARGS__ \
}; \
static const QVector <EnumName ## Internal> & labels() \
{ \
static QVector <EnumName ## Internal> labels_{__VA_ARGS__}; \
return labels_; \
} \
inline bool operator == (const EnumName &a) const \
{ \
return value == a.value; \
} \
inline bool operator != (const EnumName &a) const \
{ \
return value != a.value; \
} \
constexpr EnumName(EnumName ## Internal v) : value(v) {} \
protected: \
	EnumName ## Internal value; \
	}; \
	uint qHash(EnumType, uint) noexcept (true); \
	inline uint qHash(EnumName enumVar) \
	{ \
	return qHash(toUnderlying(enumVar.value), 0); \
	} \
	inline QDataStream & operator << (QDataStream &out, const EnumName &enumVar) \
	{ \
	out << toUnderlying(enumVar.value); \
	return out; \
	} \
	inline QDataStream & operator >> (QDataStream &in, EnumName &enumVar) \
	{ \
	in >> toUnderlyingRef(enumVar.value); \
	return in; \
	}

	#define EnumSubClass(ParentEnumName, EnumName, ...) \
	struct EnumName : public ParentEnumName { \
	static const QVector <ParentEnumName ## Internal> labels() \
	{ \
	static QVector <ParentEnumName ## Internal> labels_{__VA_ARGS__}; \
	return labels_; \
	} \
	constexpr EnumName(ParentEnumName ## Internal v) : ParentEnumName(v) {} \
	}; \
	inline uint qHash(EnumName enumVar) \
	{ \
	return qHash(ParentEnumName(enumVar)); \
	}

	#include <QtCore/QHash>

	#endif