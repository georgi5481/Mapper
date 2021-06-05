#include "IMapper.h"
#include "Vec2.h"
#include "IBorder.h"
#include "Border.h"
#include<iostream>

template<class T>
class Mapper : public IMapper<T> {
public:
	Mapper() : velocity(1, 0)	//sets the initial velocity
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
	int integrate(T dt, const T* sensor) {
		//write logic for searching

		position.x += (velocity.x * dt);	//calculate the postion at the moment
		position.y += (velocity.y * dt);

		for (unsigned int i = 0; i <= 3; i++) {

			T sensorValue = (*(sensor + i));

			if (sensorValue >= 0 && sensorValue <= 1) {	//check if there is a sensor value

				Vec2<T> foundBorderCoordinates;

				if (i % 2 == 1) {	//picks the left or right sensor value from the array
										

					if (velocity.x == 1 || velocity.x == -1) {	//check which side we were going  left or right
						foundBorderCoordinates.x += (sensorValue + position.x);
					}
					else {
						foundBorderCoordinates.y += (sensorValue + position.y);
					}
				}
				else if (i % 2 == 0) {	//pick ahead or astern sensor value
					if ((velocity.y == 1 || velocity.y == -1)) {	//checks  which side we were going
						foundBorderCoordinates.y += (sensorValue + position.y);
					}
					else {
						foundBorderCoordinates.x += (sensorValue + position.x);
					}
				
				}
				else {
					throw "There has been an error. Velocity out of range";
				}

				border.saveBorderCordinates(foundBorderCoordinates);

			}
			else {	//if there isn't an input sensor value

			}
		}

			return 1;

			/*if ()//we completed the map or there is some error
				{
					return 0;
				}
			}*/
		
	}
private:
	Vec2<T> position;	//the base constructor of Vec2 sets the X and Y cordinates to 0
	Vec2<T> velocity;	//the base constructor of this class Mapper will set the initial velocity to (1, 0)
	Border<T> border;
};


int main() {
	Mapper<double> gosho;
	double matrix[4] = { -1, -1, 0.5, -1 };
	const double* pointerMatrix = matrix;
	for (double i = 0.1; i < 0.9 ; (i+0.1)) {
		gosho.integrate(i, pointerMatrix);
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

