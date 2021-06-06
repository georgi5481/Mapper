#pragma once
#include "IBorder.h"
#include <list>
template<class T>
class Border : public IBorder<T>
{
public:
	Border(){}

	int checkIfLastBorder() {
		if (polylines.size() > 1 && (polylines.begin()->x == polylines.rbegin()->x && polylines.begin()->y == polylines.rbegin()->y)) 
		{			//if the container ins't empty and the pirst and last elements are the same in the coordinate system
			return 0;
		}
		return 1;
	}

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

