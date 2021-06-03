#include "IMapper.h"
#include "Vec2.h"
#include "IBorder.h"
#include<iostream>

class Mapper : IMapper<double> //using doubles for better accuracy for the coordinate system 
{
public:

	Mapper() : velocity(1, 0) //to set the initial velocity 
	{

	}


	const Vec2<double>& getPosition() const {
		return position;
	}


	const Vec2<double>& getVelocity() const {
		return velocity;
	}
	const IBorder<double>& getBorder() const {

	}
	int integrate(double dt, const double* sensor) {
		return 1;


	
		if ()//we completed the map or there is some error 
		{
			return 0;
		}
	}


private:
	Vec2<double> position;	//the base constructor of Vec2 sets the X and Y cordinates to 0

	Vec2<double> velocity;	

};

int main() {

	Mapper obj;

	double sensor(0);
	for (unsigned int i = 0; obj.integrate( i, sensor) != 0 && std::cin.fail(); i++) {			//i is basically simulating a time and since there is no negative time - using unsigned int 
		std::cin >> sensor;	//simulating a censor inputs
	}




	//obj.integrate();


	

	return 0;
}