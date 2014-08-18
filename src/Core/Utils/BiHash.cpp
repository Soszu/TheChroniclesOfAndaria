/*
 T *he MIT License (MIT)

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

template <typename T, typename U>
inline BiHash <T, U>::BiHash(std::initializer_list <std::pair <T, U> > initList)
{
	for (const std::pair <T, U> p : initList)
		insert(p.first, p.second);
}

template <typename T, typename U>
inline const U BiHash <T, U>::operator [] (const T &arg) const
{
	return left[arg];
}

template <typename T, typename U>
inline const T BiHash <T, U>::operator [] (const U &arg) const
{
	return right[arg];
}

template <typename T, typename U>
inline bool BiHash <T, U>::contains(const T &arg) const
{
	return left.contains(arg);
}

template <typename T, typename U>
inline bool BiHash <T, U>::contains(const U &arg) const
{
	return right.contains(arg);
}

template <typename T, typename U>
inline void BiHash <T, U>::insert(const T &lhs, const U &rhs)
{
	left.insert(lhs, rhs);
	right.insert(rhs, lhs);
}

template <typename T, typename U>
inline void BiHash <T, U>::insert(const U &lhs, const T &rhs)
{
	right.insert(lhs, rhs);
	left.insert(rhs, lhs);
}

template <typename T, typename U>
inline bool BiHash <T, U>::remove(const T &arg)
{
	if (left.contains(arg)) {
		right.remove(left[arg]);
		left.remove(arg);
		return true;
	}
	return false;
}

template <typename T, typename U>
inline bool BiHash <T, U>::remove(const U &arg)
{
	if (right.contains(arg)) {
		left.remove(right[arg]);
		right.remove(arg);
		return true;
	}
	return false;
}

template <typename T, typename U>
inline int BiHash <T, U>::size() const
{
	Q_ASSERT(left.size() == right.size());
	return left.size();
}

template <typename T, typename U>
inline const T BiHash <T, U>::value(const U &arg) const
{
	return value(arg, T{});
}

template <typename T, typename U>
inline const U BiHash <T, U>::value(const T &arg) const
{
	return value(arg, U{});
}

template <typename T, typename U>
inline const T BiHash <T, U>::value(const U &arg, const T &defaultValue) const
{
	auto iter = right.find(arg);
	if (iter != right.end())
		return iter.value();
	return defaultValue;
}

template <typename T, typename U>
inline const U BiHash <T, U>::value(const T &arg, const U &defaultValue) const
{
	auto iter = left.find(arg);
	if (iter != left.end())
		return iter.value();
	return defaultValue;
}

template <typename T, typename U>
inline QList<T> BiHash <T, U>::leftKeys() const
{
	return left.keys();
}

template <typename T, typename U>
inline QList<U> BiHash <T, U>::rightKeys() const
{
	return right.keys();
}