#pragma once
#include "IBorder.h"
#include <list>

class Border : IBorder<double>
{
public:
	void saveBorderCordinates(double& xCoordinate, double& yCoordinate) {
		Vec2<double> coordinatesPolyline(xCoordinate, yCoordinate);
		polylines.push_back(coordinatesPolyline);
	}

	virtual int getCount() const {
		return polylines.size();
	}
	virtual const Vec2<double>& operator[](int index) const {
		return *(std::next(polylines.begin(), index));
	}
private:
	std::list<Vec2<double>> polylines;

};

