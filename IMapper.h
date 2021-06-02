#pragma once
#include "IBorder.h"

template<class T>
struct IMapper
{
	virtual const Vec2<T>& getPosition() const = 0;
	virtual const Vec2<T>& getVelocity() const = 0;
	virtual const IBorder<T>& getBorder() const = 0;
	virtual int integrate(T dt, const T* sensor) = 0;
};
