#pragma once
#include "IMapper.h"
#include "Vec2.h"
#include "IBorder.h"

#include<iostream>
#include<vector>



template<class T>
class Border : public IBorder<T>	//first implementing the Border class 
{
public:
	Border() {}

	int checkIfLastBorder() {
		if (polylines.size() > 1) {
			bool closeX = static_cast<T>(polylines.begin()->x - polylines.rbegin()->x) < static_cast<T>(0.01) &&
							static_cast<T>(polylines.begin()->x - polylines.rbegin()->x) > static_cast<T>(-0.01);

			bool closeY = static_cast<T>(polylines.begin()->y - polylines.rbegin()->y) < static_cast < T>(0.01) &&
							static_cast<T>(polylines.begin()->y - polylines.rbegin()->y) > static_cast<T>(-0.01);

			if (closeX && closeY)
			{			//if the container isn't empty and the first and last elements are the same or really close in the coordinate system
				return 0;
			}
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
		return polylines[index];
	}
private:
	std::vector<Vec2<T>> polylines;

};

template<class T>
class Mapper : public IMapper<T> {

public:
	

	Mapper() : velocity(1, 0), right(1, 0), upRight(1,1), up(0, 1), upLeft(-1,1), left(-1, 0), downLeft(-1,-1), down(0, -1), downRight(1,-1)
	{	//sets the initial velocity and the directions

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
	const Vec2<T>& operator[](int index) const {
		return border[index];
	}
	const int getBorderSize() {
		return border.getCount();
	}
	

	int integrate(T dt, const T* sensor) {

		position.x += (velocity.x * dt);	//calculates the postion at the moment
		position.y += (velocity.y * dt);

		T ahead = *sensor;
		T leftward = (*(sensor + 1));		//getting out the 4 values from the input array
		T astern = (*(sensor +  2));
		T rightward = (*(sensor + 3));

		velocity = whereToGo(ahead, leftward, astern, rightward, dt);	//pick where to go next

		Vec2<T> borderPosition = position;	//since it isn't good to return a reference from a method,
											//i'm declaring the object here not in the method generatePositionn()
	
		if (rightward >= 0 && rightward <= 1) { //saves every coordinate if a sensor has a positive value between 0 and 1
			border.saveBorderCordinates(generatePosition(borderPosition, rightward, static_cast <T>(0)));	
		//	std::cout << "		right X: " << borderPosition.x << "  Y:" << borderPosition.y;	
		}
		if (ahead >= 0 && ahead <= 1) {
			border.saveBorderCordinates(generatePosition(borderPosition, static_cast<T>(0), ahead));
		//	std::cout <<"		up X: " << borderPosition.x << "  Y:" << borderPosition.y;			//prints the found border coordinates
		}
		if (leftward >= 0 && leftward <= 1) {
			border.saveBorderCordinates(generatePosition(borderPosition, -leftward, static_cast<T>(0)));
		//	std::cout << "		left X: " << borderPosition.x << "  Y:" << borderPosition.y;
		}
		if (astern >= 0 && astern <= 1) {
			border.saveBorderCordinates(generatePosition(borderPosition, static_cast<T>(0), -astern));
		//	std::cout << "		down X: " << borderPosition.x << "  Y:" << borderPosition.y;
		}



		if (ahead >= 0 && leftward >= 0 && astern >= 0 && rightward >= 0)	//in case the four sensors recieve a value
		{
			return 0;
		}
		else {
			return border.checkIfLastBorder();		//check if it's the same position as the first one
		}
	}



 private:

	 Vec2<T>& generatePosition(Vec2<T>& borderPosition, T xSensor, T ySensor) {

		 borderPosition = position; //we need this otherwise if we get 2 or more border points at the same time, we won't get the right calculations

		 borderPosition.x += xSensor;
		 borderPosition.y += ySensor;

		 return borderPosition;
	 }

	 Vec2<T> whereToGo(T& aheadSensor, T& leftSensor, T& asternSensor, T& rightSensor, T& dt) {

		 bool ifRight = (velocity.x == right.x && velocity.y == right.y);	//helping bools telling us where we are going atm.
		 bool ifLeft = (velocity.x == left.x && velocity.y == left.y);
		 bool ifDown = (velocity.x == down.x && velocity.y == down.y);
		 bool ifUp = (velocity.x == up.x && velocity.y == up.y);
		 bool ifUpRight = (velocity.x == upRight.x && velocity.y == upRight.y);
		 bool ifUpLeft = (velocity.x == upLeft.x && velocity.y == upLeft.y);
		 bool ifDownLeft = (velocity.x == downLeft.x && velocity.y == downLeft.y);
		 bool ifDownRight = (velocity.x == downRight.x && velocity.y == downRight.y);

		 bool checkDiagonalsRightX = velocity.x != 0 && rightSensor >= 0 && aheadSensor < 0 && (velocity.x * dt) < rightSensor;
		 bool checkDiagonalsLeftX = velocity.x != 0 && leftSensor >= 0 && asternSensor < 0 && (velocity.x * dt) < leftSensor;

		 if (ifRight || ifUp || ifUpRight || ifUpLeft) {	//if we move right or up it is the same logic exept in 1 condition below
			 if (rightSensor >= 0) {
				 if (aheadSensor >= 0) {
					 if (leftSensor >= 0) {
						 velocity = down;
					 }
					 else if (checkDiagonalsLeftX) {
						 velocity = upLeft;
					 }
					 else {
						 velocity = left;
					 }
				 }
				 else if (checkDiagonalsRightX) {
					 velocity = upRight;
				 }
				 else {
					 velocity = up;
				 }
			 }
			 else {
				 if (asternSensor < 0 && border.getCount() > 1 && ifRight) {
					 velocity = down;
				 }
				 else {
					 velocity = right;
				 }
			 }
		 }
		 else if (ifLeft || ifDown || ifDownRight || ifDownLeft) { //if we move left or down we follow the same logic exept in 1 condition
			 if (leftSensor >= 0) {
				 if (asternSensor >= 0) {
					 if (rightSensor >= 0) {
						 velocity = up;
					 }
					 else if (checkDiagonalsRightX) {
						 velocity = downRight;
					 }
					 else {
						 velocity = right;
					 }
				 }
				 else if (checkDiagonalsLeftX) {
					 velocity = downLeft;
				 }
				 else {
					 velocity = down;
				 }
			 }
			 else {
				 if (aheadSensor < 0 && ifLeft) {
					 velocity = up;
				 }
				 else {
					 velocity = left;
				 }
			 }
		 }
		 return velocity;
	 }

private:

	Vec2<T> position;	//the base constructor of Vec2 sets the X and Y cordinates to 0
	Vec2<T> velocity;	//the base constructor of this class Mapper will set the initial velocity to (1, 0)

	Vec2<T> right;	
	Vec2<T> upRight;
	Vec2<T> up;		//the eight paths we can go 
	Vec2<T> upLeft;	//(right = 1,0  ; upRight = 1,1  ;  up = 0,1  ;  upLeft = -1,1;  left = -1,0  ;  downLeft = -1,-1  ;  downRight = 1,-1  down = 0,-1)
	Vec2<T> left;
	Vec2<T> downLeft;
	Vec2<T> down;
	Vec2<T> downRight;
	
	Border<T> border;	//where we save found borders
};



