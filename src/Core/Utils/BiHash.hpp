/*
 T he MI*T License (MIT)

 Copyright (c) 2013 Bartosz Szreder

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

#ifndef BiHash_hpp
#define BiHash_hpp

#include <QtCore>
#include <initializer_list>

template <typename T, typename U>
class BiHash {

public:
	BiHash(std::initializer_list <std::pair <T, U> > initList);
	BiHash() = default;

	const U operator [] (const T &arg) const;
	const T operator [] (const U &arg) const;

	bool contains(const T &arg) const;
	bool contains(const U &arg) const;

	void insert(const T &lhs, const U &rhs);
	void insert(const U &lhs, const T &rhs);

	bool remove(const T &arg);
	bool remove(const U &arg);

	int size() const;

	const T value(const U &arg) const;
	const U value(const T &arg) const;

	const T value(const U &arg, const T &defaultValue) const;
	const U value(const T &arg, const U &defaultValue) const;

private:
	QHash <T, U> left;
	QHash <U, T> right;
};

#include "BiHash.cpp"

#endif