#pragma once
#include "IBorder.h"
#include <list>
template<class T>
class Border : public IBorder<T>
{
public:
	Border(){}

	void saveBorderCordinates(Vec2<T>& input) {
		polylines.push_back(input);
	}

	virtual int getCount() const {
		return polylines.size();
	}
	virtual const Vec2<T>& operator[](int index) const {
		return *(std::next(polylines.begin(), index));
	}
private:
	std::list<Vec2<T>> polylines;

};

