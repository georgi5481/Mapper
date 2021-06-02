#pragma once
#include "Vec2.h"

template<class T>
struct IBorder
{
	virtual int getCount() const = 0;
	virtual const Vec2<T>& operator[](int index) const = 0;
};
