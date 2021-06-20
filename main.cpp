#include "Mapper.h"
#include "IMapper.h"
#include "Vec2.h"
#include "IBorder.h"

#include<iostream>
#include<vector>

int main() {		//this main method is just so i can check if the logic works correctly
					
	Mapper<float> mapper;
	float array[18][14] = { 
{0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0},
{0,0.1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0.1,0.1,0},
{0,0.1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0.1,0},
{0,0.1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0.1,0},
{0,0.1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0.1,0},
{0,0.1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0.1,0},
{0,0.1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0.1,0},
{0,0.1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0.1,0},
{0,0.1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0.1,0},
{0,0.1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0.1,0},
{0,0.1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0.1,0},
{0,0.1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0.1,0},
{0,0.1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0.1,0},
{0,0.1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0.1,0},
{0,0.1,0.1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0.1,0},
{0,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0} };

	unsigned int realPositionX = 7;
	unsigned int realPositionY = 4;

	bool shouldMap = true;

	realPositionX++;	//since we always start moving right we need the sensors right from us from the start position
	std::cout.precision(2);
	std::cout << std::fixed << "Moving path:		Borders coordintes: \n";	//just for some help
	while (shouldMap) {
		
		float aheadSensor = array[realPositionY - 1][realPositionX];		//taking the sensors value
		float leftSensor = array[realPositionY][realPositionX - 1];
		float downSensor = array[realPositionY + 1][realPositionX];
		float rightSensor = array[realPositionY][realPositionX + 1];

		float arrayPosition[4] = {aheadSensor, leftSensor, downSensor, rightSensor};
		
		std::cout << "\nX:"<< mapper.getVelocity().x << "   Y:" << mapper.getVelocity().y << "	";

		int integrateResult = mapper.integrate(0.1f, arrayPosition);

		Vec2<float> velocity = mapper.getVelocity();

		bool ifRight = (velocity.x == 1 && velocity.y == 0);	//helping bools telling us where we are going atm.
		bool ifLeft = (velocity.x == -1 && velocity.y == 0);
		bool ifDown = (velocity.x == 0 && velocity.y == -1);
		bool ifUp = (velocity.x == 0 && velocity.y == 1);

		bool ifUpRight = (velocity.x == 1 && velocity.y == 1);
		bool ifUpLeft = (velocity.x == -1 && velocity.y == 1);
		bool ifDownRight = (velocity.x == 1 && velocity.y == -1);
		bool ifDownLeft = (velocity.x == -1 && velocity.y == -1);

		if (ifRight)		//depending on where we go, we change position in the helping array we build
		{
			realPositionX++;
		}
		else if (ifLeft)
		{
			realPositionX--;
		}
		else if (ifUpRight)
		{
			realPositionX++;
			realPositionY--;
		}
		else if (ifUpLeft)
		{
			realPositionX--;
			realPositionY--;
		}
		else if (ifDownLeft)
		{
			realPositionX--;
			realPositionY++;
		}
		else if (ifDownRight)
		{
			realPositionX++;
			realPositionY++;
		}
		else if (ifDown)
		{
			realPositionY++;
		}
		else if (ifUp)
		{
			realPositionY--;
		}


		if (integrateResult == 0) {	//will end the loop if we found the same stating border point or if it's really close 
			shouldMap = false;
		}
	}

	//std::cout.precision(2);
	//for (int k = 0; k < mapper.getBorderSize(); k++ ) {		//printing all the border points we found
	//	std::cout << "X: " << std::fixed << mapper[k].x << "  Y:  " << mapper[k].y << '\n';
	//}
	return 0;
}