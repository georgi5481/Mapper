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

	double aheadSensor, lefwardSensor, asternSensor, rightwardSensor;
	double xVectorVelocity(1), yVectorVelocity(0); //since the initial velocity is x=1 and y=0

	for (unsigned int i = 0; i <= 3 && std::cin.fail(); i++) {			//i is basically simulating a time and since there is no negative time - using unsigned int 
		std::cin >> aheadSensor >> lefwardSensor >> asternSensor >> rightwardSensor;	//simulating a censor inputs of 4 doubles

		if (std::cin.peek() != '\n') {
			double xVelocity(0), yVelocity(0);
			std::cin >> xVelocity >> yVelocity;	

			if ( (((xVelocity == 1 || xVelocity == -1) && yVelocity == 0) ||	//checks for correct imput for the velocity vector
				  ((yVelocity == 1 || yVelocity == -1) && xVelocity == 0) ) && !std::cin.fail())    //since we can only go 1 way with 1 m/s  
			{
				xVectorVelocity = xVelocity;
				yVectorVelocity = yVelocity;
			}
		}

	}




	//obj.integrate();


	

	return 0;
}