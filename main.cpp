#include "Mapper.h"
#include "IMapper.h"
#include "Vec2.h"
#include "IBorder.h"

#include<iostream>
#include<vector>

int main() {		//this main method is just so i can check if the logic works correctly
					
	Mapper<double> mapper;
	double array[16][12] = { 
{1,1,1,1,1,1,1,1,1,1,1,1},
{1,-1,-1,-1,-1,-1,-1,-1,1,-1,-1,1},
{1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1},
{1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1},
{1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1},
{1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1},
{1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1},
{1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1},
{1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1},
{1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1},
{1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1},
{1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1},
{1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1},
{1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1},
{1,-1,-1,-1,-1,-1,-1,-1,1,-1,-1,1},
{1,1,1,1,1,1,1,1,1,1,1,1}};

	unsigned int realPositionX = 8;
	unsigned int realPositionY = 3;

	bool shouldMap = true;

	realPositionX++;
	std::cout << "Moving path: \n";
	while (shouldMap) {
		
		double aheadSensor = array[realPositionY - 1][realPositionX];
		double leftSensor = array[realPositionY][realPositionX - 1];
		double downSensor = array[realPositionY + 1][realPositionX];
		double rightSensor = array[realPositionY][realPositionX + 1];

		double arrayPosition[4] = {aheadSensor, leftSensor, downSensor, rightSensor};
		
		std::cout << "X:"<< mapper.getVelocity().x << "   Y:" << mapper.getVelocity().y << '\n';

		int integrateResult = mapper.integrate(0.9, arrayPosition);

		Vec2<double> velocity = mapper.getVelocity();
		bool ifRight = (velocity.x == 1 && velocity.y == 0);	//helping bools telling us where we are going atm.
		bool ifLeft = (velocity.x == -1 && velocity.y == 0);
		bool ifDown = (velocity.x == 0 && velocity.y == -1);
		bool ifUp = (velocity.x == 0 && velocity.y == 1);

		if (ifRight)
		{
			realPositionX++;
		}
		else if (ifLeft)
		{
			realPositionX--;
		}
		else if (ifDown)
		{
			realPositionY++;
		}
		else if (ifUp)
		{
			realPositionY--;
		}


		if (integrateResult == 0) {
			shouldMap = false;
		}
	}
	std::cout << '\n' << "Borders found : \n";
	std::cout.precision(2);
	for (int k = 0; k < (mapper.getBorder()).getCount(); k++ ) {
		std::cout << "X: " << std::fixed << ((mapper.getBorder())[k]).x << "  Y:  " << ((mapper.getBorder())[k]).y << '\n';
	}
	return 0;
}