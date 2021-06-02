#pragma once

template<class T>
struct Vec2
{
	Vec2() 
	{
		x = (T)0;
		y = (T)0; 
	}
	Vec2(const T& X, const T& Y) 
	{
		x = X;
		y = Y; 
	}
	T x;
	T y;
};
