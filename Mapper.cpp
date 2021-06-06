#include "IMapper.h"
#include "Vec2.h"
#include "IBorder.h"
//#include "Border.h"

#include<iostream>
#include <list>
template<class T>
class Border : public IBorder<T>
{
public:
	Border() {}

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
	 Vec2<T>& generatePosition(Vec2<T>& borderPosition, T xSensor, T ySensor) {
		borderPosition.x += xSensor;
		borderPosition.y += ySensor;

		return borderPosition;
	}

	Vec2<T> whereToGo(T& aheadSensor, T& leftSensor, T& asternSensor, T& rightSensor) {

		bool ifRight = (velocity.x == right.x && velocity.y == right.y);	//helping bools telling us where we are going atm.
		bool ifLeft = (velocity.x == left.x && velocity.y == left.y);
		bool ifDown = (velocity.x == down.x && velocity.y == down.y);
		bool ifUp = (velocity.x == up.x && velocity.y == up.y);

		if (ifRight) {	//if we move right
			if (rightSensor >= 0) {
				if (aheadSensor >= 0) {
					if (leftSensor >= 0) {
						velocity = down;
					}
					else {
						velocity = left;
					}
				}
				else {
					velocity = up;
				}
			}
			else {
				if ( asternSensor < 0  && border.getCount() > 1) {
					velocity = down;
				}
				else {
					velocity = right;
				}
			}
		}
		else if (ifUp) { //if we move up
			if (rightSensor >= 0) {
				if (aheadSensor >= 0) {
					if (leftSensor >= 0) {
						velocity = down;
					}
					else {
						velocity = left;
					}
				}
				else {
					velocity = up;
				}
			}
			else {
				velocity = right;
			}
		}
		else if (ifDown) {	//if we move down
			if (leftSensor >= 0) {
				if (asternSensor >= 0) {
					if (rightSensor >= 0) {
						velocity = up;
					}
					else {
						velocity = right;
					}
				}
				else {
					velocity = down;
				}
			}
			else {
				velocity = left;
			}
		}
	
		else if(ifLeft){ //if we move left
			if (leftSensor >= 0) {
				if (asternSensor >= 0) {
					if (rightSensor >= 0) {
						velocity = up;
						}
					else {
						velocity = right;
					}
				}
				else {
					velocity = down;
				}
			}
			else {
				if (aheadSensor >= 0) {
					velocity = left;
				}
				else {
					velocity = up;
				}
			}
		}
		return velocity;
	}


	int integrate(T dt, const T* sensor) {

		position.x += (velocity.x * dt);	//calculate the postion at the moment
		position.y += (velocity.y * dt);

		T ahead = *sensor;
		T leftward = (*(sensor + 1));		//getting out the 4 values from the input array
		T astern = (*(sensor + 2));
		T rightward = (*(sensor + 3));

		velocity = whereToGo(ahead, leftward, astern, rightward);	//pick where to go next

		Vec2<T> borderPosition = position;	//since it isn't good to return a reference from a method, declaring the object here not in the method below

		if (ahead >= 0) {
			border.saveBorderCordinates(generatePosition(borderPosition, static_cast<T>(0), ahead));	//saves every coordinate if a sensor has a positive value
		}
		if (leftward >= 0) {
			border.saveBorderCordinates(generatePosition(borderPosition, -leftward, static_cast<T>(0)));
		}
		if (astern >= 0) {
			border.saveBorderCordinates(generatePosition(borderPosition, static_cast<T>(0), -astern));
		}
		if (rightward >= 0) {
			border.saveBorderCordinates(generatePosition(borderPosition, rightward, static_cast<T>(0)));
		}

		if (ahead >= 0 && leftward >= 0 && astern >= 0 && rightward >= 0)	//in case the four sensors recieve a value
		{
			return 0;
		}
		else {
			return border.checkIfLastBorder();
		}
	}
private:
	Vec2<T> position;	//the base constructor of Vec2 sets the X and Y cordinates to 0
	Vec2<T> velocity;	//the base constructor of this class Mapper will set the initial velocity to (1, 0)
	Vec2<T> right;	
	Vec2<T> up;		//the four patterns we can go
	Vec2<T> left;
	Vec2<T> down;
	Border<T> border;	//where we save the found borders
};


int main() {
	Mapper<double> gosho;
	double matrix[4] = { 1 , 1 , 1 ,1 };
	const double* pointerMatrix = matrix;
	for (double i = 0.1; i < 0.9 ; i=i+0.1) {
		std::cout << gosho.getVelocity().x << " " << gosho.getVelocity().y << '\n';

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

