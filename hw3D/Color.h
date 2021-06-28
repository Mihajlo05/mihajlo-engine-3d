#pragma once

#include <cassert>
#include <typeinfo>

template<typename T>
class ColorT
{
protected:
	ColorT(T r, T g, T b, T a)
		:
		r(r),
		g(g),
		b(b),
		a(a)
	{
		if (typeid(T) == typeid(float))
		{
			assert(r >= 0.0f && r <= 1.0f);
			assert(g >= 0.0f && g <= 1.0f);
			assert(b >= 0.0f && b <= 1.0f);
			assert(a >= 0.0f && a <= 1.0f);
		}
	}
public:
	T r;
	T g;
	T b;
	T a;
};

using Color = ColorT<unsigned char>;
using Colorf = ColorT<float>;