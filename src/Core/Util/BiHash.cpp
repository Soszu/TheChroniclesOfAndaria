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

#include "BiHash.hpp"
#include "EnumHelpers.hpp"

template <typename T, typename U>
BiHash <T, U>::BiHash(std::initializer_list <std::pair <T, U> > initList)
{
        for (const std::pair <T, U> p : initList)
                insert(p.first, p.second);
}

template <typename T, typename U>
U BiHash <T, U>::operator [] (const T &arg) const
{
        return left[arg];
}

template <typename T, typename U>
T BiHash <T, U>::operator [] (const U &arg) const
{
        return right[arg];
}

template <typename T, typename U>
void BiHash <T, U>::insert(const T &lhs, const U &rhs)
{
        left.insert(lhs, rhs);
        right.insert(rhs, lhs);
}

template <typename T, typename U>
void BiHash <T, U>::insert(const U &lhs, const T &rhs)
{
        right.insert(lhs, rhs);
        left.insert(rhs, lhs);
}

template <typename T, typename U>
int BiHash <T, U>::size() const
{
        return left.size();
}