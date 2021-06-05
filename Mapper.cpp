#include "IMapper.h"
#include "Vec2.h"
#include "IBorder.h"
#include "Border.h"
#include<iostream>

template<class T>
class Mapper : public IMapper<T> {
public:
	Mapper() : velocity(1, 0), right(1, 0), up(0, 1), left(-1, 0), down(0, -1)	//sets the initial velocity and the helping direction
	{
		
	}
	const Vec2<T>& getPosition() const {
		return position;
	}
	const Vec2<T>& getVelocity() const {

		return velocity;
	}
	const IBorder<T>& getBorder() const {

		return border;

	}
	Vec2<T> whereToGo(T ahead, T ) {


	}


	int integrate(T dt, const T* sensor) {

		position.x += (velocity.x * dt);	//calculate the postion at the moment
		position.y += (velocity.y * dt);

		T ahead = *sensor;
		T leftward = (*(sensor + 1));		//getting out the 4 values from the array
		T astern = (*(sensor + 2));
		T rightward = (*(sensor + 3));

		T sensorValue;
		bool ifRight = (velocity.x == right.x && velocity.y == right.y);
		bool ifLeft = (velocity.x == left.x && velocity.y == left.y);
		bool ifDown = (velocity.x == down.x && velocity.y == down.y);
		bool ifUp = (velocity.x == up.x && velocity.y == up.y);

		if (ifRight) {
			sensorValue = rightward;
		}
		else if (ifLeft) {
			sensorValue = ahead;
		}
		else if (ifDown) {
			sensorValue = leftward;
		}
		else if (ifUp) {
			sensorValue = astern;
		}
		else {
			throw "There has been an error. Velocity out of range";
		}

			if (sensorValue >= 0 && sensorValue <= 1) {	//check if the sensor value is in range
			
				Vec2<T> foundBorderCoordinates = position;
				
					if (ifRight) {	//check which side we were going right, left, up or down
						foundBorderCoordinates.x += sensorValue;
						velocity = up;
					}
					else if(ifLeft)
					{
						foundBorderCoordinates.x -= sensorValue ;
						velocity = down;
					}
					if (ifUp) 
					{
						foundBorderCoordinates.y +=sensorValue;
						velocity = left;
					}
					else if (ifDown) 
					{
						foundBorderCoordinates.y -= sensorValue;
						velocity = right;
					}
					border.saveBorderCordinates(foundBorderCoordinates);
					
				}

				

			previousVelocity = velocity;

			return 1;
		
	}
private:
	Vec2<T> position;	//the base constructor of Vec2 sets the X and Y cordinates to 0
	Vec2<T> velocity;	//the base constructor of this class Mapper will set the initial velocity to (1, 0)
	Vec2<T> previousVelocity; //will save the last path used
	Vec2<T> right;	
	Vec2<T> up;
	Vec2<T> left;
	Vec2<T> down;
	Vec2<T> pathVelocity[4] = { right, up, left, down };
	Border<T> border;
};


int main() {
	Mapper<double> gosho;
	double matrix[4] = { -1, -1, -1, 0.3 };
	const double* pointerMatrix = matrix;
	for (double i = 0.1; i < 0.3 ; i=i+0.1) {
		gosho.integrate(i, matrix);
	}
	return 0;
}



	/*

	class Mapper : IMapper<double> //using doubles for better accuracy for the coordinate system
	{
	public:

		Mapper() : velocity(1, 0)	//sets the initial velocity
		{
		}

		const Vec2<double>& getPosition() const {
			return position;
		}

		const Vec2<double>& getVelocity() const {

			return iborder.getCount();
		}
		const IBorder<double>& getBorder() const {
			return iborder.getCount();
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
		Border iborder;
	};


	int main() {

		Mapper mapper;

		mapper.getVelocity();

		double aheadSensor, lefwardSensor, asternSensor, rightwardSensor;
		double testArea[4][4] = { {-1 , -1, -1, -1}, {-1 , -1, 1, -1},
								  {-1 , -1, -1, -1}, {-1 , 1, -1, -1}};

		double xVectorVelocity(1), yVectorVelocity(0); //since the initial velocity is x=1 and y=0

		for (unsigned int i = 0; i <= 3; i++) {

			mapper.integrate(0.5 , );

		}

		for (unsigned int i = 0; i <= 3 && std::cin.fail(); i++) {			//i is basically simulating a time and since there is no negative time - using unsigned int
			std::cin >> aheadSensor >> lefwardSensor >> asternSensor >> rightwardSensor;	//simulating a censor inputs of 4 doubles

			if (std::cin.peek() != '\n') {
				double xVelocity, yVelocity;
				std::cin >> xVelocity >> yVelocity;

				if ( (((xVelocity == 1 || xVelocity == -1) && yVelocity == 0) ||	//checks for correct imput for the velocity vector
					  ((yVelocity == 1 || yVelocity == -1) && xVelocity == 0) ) && !std::cin.fail())    //since we can only go 1 way with 1 m/s
				{
					xVectorVelocity = xVelocity;
					yVectorVelocity = yVelocity; //changing the velocity vector
				}

			}

		}*/

