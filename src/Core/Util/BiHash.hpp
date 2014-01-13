/*
The MIT License (MIT)

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

#ifndef BIHASH_HPP
#define BIHASH_HPP

#include <QtCore>
#include <initializer_list>

template <typename T, typename U>
class BiHash {

public:
        BiHash(std::initializer_list <std::pair <T, U> > initList);
        BiHash() = default;

        U operator [] (const T &arg) const;
        T operator [] (const U &arg) const;

        void insert(const T &lhs, const U &rhs);
        void insert(const U &lhs, const T &rhs);

        int size() const;

private:
        QHash <T, U> left;
        QHash <U, T> right;
};

#endif